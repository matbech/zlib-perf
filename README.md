zlib-perf - zlib performance test (compression only)

Tested with
-----------
Microsoft Visual Studio 2017

Compile zlibperf
----------------
Precompiled binaries are provided. To use them the Visual C++ Redistributable for Visual Studio 2017 is required:
https://www.microsoft.com/en-us/download/details.aspx?id=48145

To compile zlib-perf:
- Open zlibperf/zlibperf.sln
- In the project settings, VC++ Directories, Library Directories, change the path to the zlib1.lib

Run the tests
-------------
- Download the silesia corpus and extract it to the silesia folder
  Info page: http://sun.aei.polsl.pl/~sdeor/index.php?page=silesia
  Direct link to zip: http://sun.aei.polsl.pl/~sdeor/corpus/silesia.zip
- If you want to test your own zlib1.dll, copy it into the "/zlib dev/x86" or "/zlib dev/x64" folder
- Run the run.cmd in the project directory /zlibperf

Results
-------
Results:
[Intel Core i7 8770](Results.md)