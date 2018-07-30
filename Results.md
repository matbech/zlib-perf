CPU: [Intel Core i7 8770](https://ark.intel.com/products/126686/Intel-Core-i7-8700-Processor-12M-Cache-up-to-4_60-GHz)  
Compiler: MSVC 19.14.26433.0 (VS 15.7)

File: silesia\mozilla  
Size: 51220480 bytes

Compression Level: 6

|                  | Arch | Compressed size | Time (ms) | Compression rate (MB/s) |
| ---------------- | -----| ---------------:| ---------:| -----------------------:|
| zlib ori         | x86  | 19089124        | 1813      | 26 |
| zlib ori - asm (1) | x86  | 19089124        | 1562      | 31 |
| zlib-ng          | x86  | 19375674        | 1578      | 30 |
| matbech/zlib     | x86  | 19064581        | 1234      | 47 |
| fast_zlib release 2 | x86  | 19067949        | 1516      | 32 |
| fast_zlib/master | x86  | 19068104        | 1406      | 34 |
| fast_zlib/master opt | x86  | 19068104        | 1328      | 36 |
|                  |      |                 |           |    |
| zlib ori         | x64  | 19089124        | 1718      | 28 |
| zlib ori - asm (1)  | x64  | 19089124        | 1484      | 32 |
| zlib-ng (2)         | x64  |              |           |    |
| matbech/zlib     | x64  | 19064581        | 922      | 52 |
| fast_zlib release 2 | x64  | 19067949        | 1437      | 33 |
| fast_zlib/master | x64  | 19068104        | 1281      | 38 |
| fast_zlib/master opt | x64  | 19068104        | 1172      | 41 |


File: silesia\webster  
Size: 41458703 bytes

Compression Level: 6

|                | Arch | Compressed size | Time (ms) | Compression rate (MB/s) |
| -------------- | -----| ---------------:| ---------:| -----------------------:|
| zlib ori       | x86  | 12213947        | 1359      | 29 |
| zlib ori - asm (1) | x86  | 12213947        | 1297      | 30 |
| zlib-ng        | x86  | 12584263        | 1125      | 35 |
| matbech/zlib   | x86  | 12138096        | 1032      | 38 |
| fast_zlib release 2 | x86  | 12138966        | 1203      | 32 |
| fast_zlib/master | x86  | 12138950        | 1140      | 34 |
| fast_zlib/master opt | x86  | 12138950        | 1057      | 37 |
|                |      |                 |           |    |
| zlib ori       | x64  | 12213947        | 1313      | 30 |
| zlib ori - asm (1) | x64  | 12213947        | 1250      | 31 |
| zlib-ng (2)       | x64  |                |           |    |
| matbech/zlib   | x64  | 12138096        | 907      | 43 |
| fast_zlib release 2 | x64  | 12138966        | 1141      | 34 |
| fast_zlib/master | x64  | 12138950        | 1016      | 38 |
| fast_zlib/master opt | x64  | 12138950        | 938      | 42 |

(1) for reference only. ASM implementations for deflate and inflate are broken  
(2) broken. bug in deflate