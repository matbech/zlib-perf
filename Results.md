CPU: [Intel Core i7 8770](https://ark.intel.com/products/126686/Intel-Core-i7-8700-Processor-12M-Cache-up-to-4_60-GHz)  
Compiler: MSVC 19.14.26433.0 (VS 15.7)

File: silesia\mozilla  
Size: 51220480 bytes

Compression Level: 6

|                | Arch | Compressed size | Time (ms) | Compression rate (MB/s) |
| -------------- | -----| ---------------:| ---------:| -----------------------:|
| zlib ori       | x86  | 19089124        | 1813      | 26 |
| zlib ori - asm | x86  | 19089124        | 1703      | 28 |
| zlib-ng        | x86  | 19375674        | 1578      | 30 |
| matbech/zlib   | x86  | 19077704        | 1234      | 39 |
| fast_zlib      | x86  | 19067949        | 1516      | 32 |
|                |      |                 |           |    |
| zlib ori       | x64  | 19089124        | 1734      | 28 |
| zlib ori - asm | x64  | 19089124        | 1641      | 29 |
| zlib-ng        | x64  | *               |           |    |
| matbech/zlib   | x64  | 19077704        | 1110      | 44 |
| fast_zlib      | x64  | 19067949        | 1437      | 33 |


File: silesia\webster  
Size: 41458703 bytes

Compression Level: 6

|                | Arch | Compressed size | Time (ms) | Compression rate (MB/s) |
| -------------- | -----| ---------------:| ---------:| -----------------------:|
| zlib ori       | x86  | 12213947        | 1359      | 29 |
| zlib ori - asm | x86  | 12213947        | 1297      | 30 |
| zlib-ng        | x86  | 12584263        | 1125      | 35 |
| matbech/zlib   | x86  | 12208641        | 1172      | 33 |
| fast_zlib      | x86  | 12138966        | 1203      | 32 |
|                |      |                 |           |    |
| zlib ori       | x64  | 12213947        | 1313      | 30 |
| zlib ori - asm | x64  | 12213947        | 1250      | 31 |
| zlib-ng        | x64  | *               |           |    |
| matbech/zlib   | x64  | 12208641        | 1062      | 37 |
| fast_zlib      | x64  | 12138966        | 1141      | 34 |


* broken. bug in deflate
