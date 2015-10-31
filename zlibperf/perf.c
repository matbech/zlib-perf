// Originally from http://www.w3.org/config/deflate.c
// - Added time measurement
// - Added Win32 compatibility
// - Removed output of compressed data to stdout

#include "stdlib.h"
#include "stdio.h"
#include "zlib.h"
#include <stdint.h>

#ifdef WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef _MSC_VER
#pragma comment(lib, "zlib1.lib")
#endif

z_stream z;

#define DEFAULT_BUFFER_SIZE	32*1024
#define DEFAULT_COMPRESSION	Z_DEFAULT_COMPRESSION;

#define MAX(a,b) ((a) >= (b) ? (a) : (b))
#define MIN(a,b) ((a) <= (b) ? (a) : (b))

#define ZTIME_USEC_PER_SEC 1000000
#define ZTIME_MSEC_PER_SEC 1000

/* ztime_t represents usec */
typedef uint64_t ztime_t;

char *input_buffer 	= NULL;
char *output_buffer 	= NULL;
int  buffer_size 	= DEFAULT_BUFFER_SIZE;
int  compression_rate	= DEFAULT_COMPRESSION;

FILE * fin;

ztime_t start;
ztime_t stop;

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
    fprintf(stderr, "\t-c\tCompression rate [1..9] where 1 is compress faster and 9 is compress better (default 6)\n");
    fprintf(stderr, "\t-h\tHelp - this help screen\n");
}

int main (int argc, char ** argv)
{
    int arg;
    int status;
//    int count;

	if(argc < 2) {
		HelpScreen(*argv);
		exit(-1);
	}

    /* Scan command line for parameters */
    for (arg=2; arg<argc; arg++) {
	
	if (*argv[arg] == '-') {
    
	    /* Buffer size */
	    if (!strcmp(argv[arg], "-b")) {
		buffer_size = (arg+1 < argc && *argv[arg+1] != '-') ?
		    atoi(argv[++arg]) : DEFAULT_BUFFER_SIZE;
		buffer_size = MAX(buffer_size, 256);

	    /* Compression rate */
	    } else if (!strcmp(argv[arg], "-c")) {
		compression_rate = (arg+1 < argc && *argv[arg+1] != '-') ?
		    atoi(argv[++arg]) : DEFAULT_COMPRESSION;
		compression_rate = MAX(compression_rate, Z_BEST_SPEED);
		compression_rate = MIN(compression_rate, Z_BEST_COMPRESSION);

	    /* Print the help screen and exit */
	    } else if (!strcmp(argv[arg], "-h")) {
		HelpScreen(*argv);
		exit(0);

	    } else {
		HelpScreen(*argv);
		exit(-1);
	    }
	} else {
	    HelpScreen(*argv);
	    exit(-1);
	}
    }

#ifdef _MSC_VER
	fopen_s(&fin, argv[1], "rb");
#else
	fin = fopen(argv[1], "rb");
#endif
	if (!fin) {
		fprintf(stderr, "failed to open file\n");
		exit(-1);
	}

    if ((input_buffer = (char *) calloc(1, buffer_size)) == NULL ||
	(output_buffer = (char *) calloc(1, buffer_size)) == NULL) {
	fprintf(stderr, "Not enough memory\n");
	exit(-1);
    }

    deflateInit(&z, compression_rate);

	ztime(&start);

    z.avail_in = 0;
    z.next_out = output_buffer;
    z.avail_out = buffer_size;
    for ( ; ; ) {
        if ( z.avail_in == 0 ) {
            z.next_in = input_buffer;
            z.avail_in = (uint32_t)fread( input_buffer, 1, buffer_size, fin );
        }
	if ( z.avail_in == 0 ) {
	    status = deflate( &z, Z_FINISH );
	    //count = buffer_size - z.avail_out;
	    //if ( count ) fwrite( output_buffer, 1, count, fout );
	    break;
	}
        status = deflate( &z, Z_NO_FLUSH );
        //count = buffer_size - z.avail_out;
        //if ( count ) fwrite( output_buffer, 1, count, fout );
        z.next_out = output_buffer;
        z.avail_out = buffer_size;
    }

	ztime(&stop);

    fprintf(stdout, "Compressing data: raw data %lu, compressed %lu, factor %.2f, compression level (default = -1) %d, buffer size %d, time %ums\n",
	    z.total_in, z.total_out,
	    z.total_in == 0 ? 0.0 :
	    (double)z.total_out / z.total_in,
	    compression_rate,
	    buffer_size,
		(uint32_t)((stop - start) / ZTIME_MSEC_PER_SEC));
    deflateEnd(&z);
    //fflush(stdout);

    if (input_buffer) free(input_buffer);
    if (output_buffer) free(output_buffer);
    return 0;
}
