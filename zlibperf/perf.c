// Originally from http://www.w3.org/config/deflate.c
// - Added time measurement
// - Added Win32 compatibility
// - Removed output of compressed data to stdout
// - Requires C11

#include <zlib.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
// for GetTickCount
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef _MSC_VER
#pragma comment(lib, "zlib1.lib")
#endif

#define DEFAULT_BUFFER_SIZE	32*1024
#define DEFAULT_COMPRESSION	Z_DEFAULT_COMPRESSION;

#define MAX(a,b) ((a) >= (b) ? (a) : (b))
#define MIN(a,b) ((a) <= (b) ? (a) : (b))

#define ZTIME_USEC_PER_SEC 1000000
#define ZTIME_MSEC_PER_SEC 1000

#define MEGABYTE (1024*1024)

/* ztime_t represents usec */
typedef uint64_t ztime_t;

unsigned int buffer_size = DEFAULT_BUFFER_SIZE;
unsigned int compression_level = DEFAULT_COMPRESSION;
bool verify_output = false;
bool gzip_header = false;
bool csv_output = false;

static void ztime(ztime_t *ztimep)
{
#ifdef WIN32
	*ztimep = GetTickCount() * 1000;
#else
	struct timeval tv;

	gettimeofday(&tv, NULL);

	*ztimep = ((uint64_t) tv.tv_sec * ZTIME_USEC_PER_SEC) + tv.tv_usec;
#endif
}

void HelpScreen (const char *progname)
{
    fprintf(stderr, "\nDeflates using zlib\n");
    fprintf(stderr, "Usage: %s file\n", progname ? progname : "zlibperf");
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "\t-b\tBuffer size (default 32K). This has no effect on compression result\n");
    fprintf(stderr, "\t-c\tCompression level [1..9] where 1 is compress faster and 9 is compress better (default 6)\n");
	fprintf(stderr, "\t-v\tVerify output by decompressing it\n");
	fprintf(stderr, "\t-gzip\tUse gzip header\n");
	fprintf(stderr, "\t-csv\tCSV output\n");
    fprintf(stderr, "\t-h\tHelp - this help screen\n");
}

uint32_t deflateTest(char* input_file, unsigned int compression_level, unsigned int buffer_size, FILE* fout)
{
	FILE * fin;
	char *input_buffer = NULL;
	char *output_buffer = NULL;
	int status;
	int count;
	ztime_t start;
	ztime_t stop;
	z_stream z = { 0 };

	errno_t error = fopen_s(&fin, input_file, "rb");
	if (error != 0) {
		fprintf(stderr, "failed to open file\n");
		exit(-1);
	}

	if ((input_buffer = (char *)calloc(1, buffer_size)) == NULL ||
		(output_buffer = (char *)calloc(1, buffer_size)) == NULL) {
		fprintf(stderr, "Not enough memory\n");
		exit(-1);
	}

	if (gzip_header) {
		// for gz header (crc32 instead of adler), MAX_WBITS+16
		deflateInit2(&z, compression_level, Z_DEFLATED, MAX_WBITS + 16, 9/*MAX_MEM_LEVEL*/, Z_DEFAULT_STRATEGY);
	}
	else {
		// zlib header
		deflateInit(&z, compression_level);
	}
	ztime(&start);

	z.avail_in = 0;
	z.next_out = output_buffer;
	z.avail_out = buffer_size;
	for (; ; ) {
		if (z.avail_in == 0) {
			z.next_in = input_buffer;
			z.avail_in = (uint32_t)fread(input_buffer, 1, buffer_size, fin);
		}
		if (z.avail_in == 0) {
			status = deflate(&z, Z_FINISH);
			if (fout != NULL) {
				count = buffer_size - z.avail_out;
				if (count) fwrite(output_buffer, 1, count, fout);
			}
			break;
		}
		status = deflate(&z, Z_NO_FLUSH);
		if (fout != NULL) {
			count = buffer_size - z.avail_out;
			if (count) fwrite(output_buffer, 1, count, fout);
		}
		z.next_out = output_buffer;
		z.avail_out = buffer_size;
	}

	ztime(&stop);
	uint32_t timeInMs = (uint32_t)((stop - start) / ZTIME_MSEC_PER_SEC);

	if (csv_output) {
		fprintf(stdout, "%lu, %lu, %.2f, %u, %u, 0x%x, %u, %u\n",
			z.total_in, z.total_out,
			z.total_in == 0 ? 0.0 :
			(double)z.total_out / z.total_in,
			compression_level,
			buffer_size,
			z.adler,
			timeInMs,
			(uint32_t)(((z.total_in / timeInMs) * 1000) / MEGABYTE)
		);
	} else {
		fprintf(stdout, "Compressing data: raw data %lu, compressed %lu, factor %.2f, compression level %u, buffer size %u, checksum 0x%x, time %ums, rate %u MB/s\n",
			z.total_in, z.total_out,
			z.total_in == 0 ? 0.0 :
			(double)z.total_out / z.total_in,
			compression_level,
			buffer_size,
			z.adler,
			timeInMs,
			(uint32_t)(((z.total_in / timeInMs) * 1000) / MEGABYTE)
		);
	}
	deflateEnd(&z);
	//fflush(stdout);

	if (input_buffer) free(input_buffer);
	if (output_buffer) free(output_buffer);

	fclose(fin);
	return z.adler;
}

// returns checksum
uint32_t inflateTest(FILE * fin, unsigned int buffer_size)
{
	char *input_buffer = NULL;
	char *output_buffer = NULL;
	int status;
	ztime_t start;
	ztime_t stop;
	z_stream z = { 0 };

	if ((input_buffer = (char *)calloc(1, buffer_size)) == NULL ||
		(output_buffer = (char *)calloc(1, buffer_size)) == NULL) {
		fprintf(stderr, "Not enough memory\n");
		exit(-1);
	}

	if (gzip_header) {
		inflateInit2(&z, MAX_WBITS + 16);
	}
	else {
		inflateInit(&z);
	}
	ztime(&start);

	z.avail_in = 0;
	z.next_out = output_buffer;
	z.avail_out = buffer_size;
	for (; ; ) {
		if (z.avail_in == 0) {
			z.next_in = input_buffer;
			z.avail_in = (uint32_t)fread(input_buffer, 1, buffer_size, fin);
		}
		if (z.avail_in == 0) {
			break;
		}
		status = inflate(&z, Z_NO_FLUSH);
		if (status < 0)
		{
			fprintf(stderr, "inflate error %d\n", status);
			exit(-1);
		}
		else if (status == Z_STREAM_END)
		{
			break;
		}
		z.next_out = output_buffer;
		z.avail_out = buffer_size;
	}

	ztime(&stop);
	uint32_t timeInMs = (uint32_t)((stop - start) / ZTIME_MSEC_PER_SEC);

	if (csv_output) {
		fprintf(stdout, "%lu, %lu, %.2f, 0x%x, %ums, %u\n",
			z.total_in, z.total_out,
			z.total_in == 0 ? 0.0 :
			(double)z.total_out / z.total_in,
			z.adler,
			timeInMs,
			(uint32_t)(((z.total_out / timeInMs) * 1000) / MEGABYTE)
		);
	}
	else {
		fprintf(stdout, "Decompressing data: raw data %lu, decompressed %lu, factor %.2f, checksum 0x%x, time %ums, rate %u MB/s\n",
			z.total_in, z.total_out,
			z.total_in == 0 ? 0.0 :
			(double)z.total_out / z.total_in,
			z.adler,
			timeInMs,
			(uint32_t)(((z.total_out / timeInMs) * 1000) / MEGABYTE)
		);
	}
	inflateEnd(&z);
	//fflush(stdout);

	if (input_buffer) free(input_buffer);
	if (output_buffer) free(output_buffer);

	return z.adler;
}

int main (int argc, char ** argv)
{
    int arg;
	FILE *fout = NULL;
	uint32_t checksum;

	if(argc < 2) {
		HelpScreen(*argv);
		exit(-1);
	}

    /* Scan command line for parameters */
    for (arg=2; arg<argc; arg++) {
	
		if (*argv[arg] == '-') {

			/* Buffer size */
			if (!strcmp(argv[arg], "-b")) {
				buffer_size = (arg + 1 < argc && *argv[arg + 1] != '-') ?
					atoi(argv[++arg]) : DEFAULT_BUFFER_SIZE;
				buffer_size = MAX(buffer_size, 256);

				/* Compression rate */
			}
			else if (!strcmp(argv[arg], "-c")) {
				compression_level = (arg + 1 < argc && *argv[arg + 1] != '-') ?
					atoi(argv[++arg]) : DEFAULT_COMPRESSION;
				compression_level = MAX(compression_level, Z_BEST_SPEED);
				compression_level = MIN(compression_level, Z_BEST_COMPRESSION);

				/* Print the help screen and exit */
			}
			else if (!strcmp(argv[arg], "-v")) {
				verify_output = true;

			}
			else if (!strcmp(argv[arg], "-gzip")) {
				gzip_header = true;

			}
			else if (!strcmp(argv[arg], "-csv")) {
				csv_output = true;

			}
			else if (!strcmp(argv[arg], "-h")) {
				HelpScreen(*argv);
				exit(0);

			}
			else {
				HelpScreen(*argv);
				exit(-1);
			}
		}
		else {
			HelpScreen(*argv);
			exit(-1);
		}
	}

	if (verify_output) {
		errno_t error = tmpfile_s(&fout);
		if (error != 0) {
			fprintf(stderr, "failed to create temp file\n");
			exit(-1);
		}
	}

	checksum = deflateTest(argv[1], compression_level, buffer_size, fout);

	if (verify_output) {
		uint32_t checksum2;
		int error = fseek(fout, 0, SEEK_SET);
		if (error != 0) {
			fprintf(stderr, "seek failed\n");
			exit(-1);
		}
		checksum2 = inflateTest(fout, buffer_size);
		if (checksum != checksum) {
			fprintf(stderr, "verification failed\n");
			exit(-1);
		}
	}

	if (fout) fclose(fout);

    return 0;
}
