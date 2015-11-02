CPU: [Intel Core i7 3770](http://ark.intel.com/products/65719/Intel-Core-i7-3770-Processor-8M-Cache-up-to-3_90-GHz)  
Compiler: MSVC14

File: silesia\mozilla  
Size: 51220480 bytes

Compression Level: 6

|                | Arch | Compressed size | Time (ms) | Compression rate (MB/s) |
| -------------- | -----| ---------------:| ---------:| -----------------------:|
| zlib ori       | x86  | 19089124        | 2313      | 21 |
| zlib ori - asm | x86  | 19089124        | 2156      | 22 |
| matbech/zlib   | x86  | 19077704        | 1625      | 30 |
| zlib ori       | x64  | 19089124        | 2094      | 23 |
| zlib ori - asm | x64  | 19089124        | 2000      | 24 |
| matbech/zlib   | x64  | 19077704        | 1406      | 34 |


File: silesia\webster  
Size: 41458703 bytes

Compression Level: 6

|                | Arch | Compressed size | Time (ms) | Compression rate (MB/s) |
| -------------- | -----| ---------------:| ---------:| -----------------------:|
| zlib ori       | x86  | 12213947        | 1781      | 22 |
| zlib ori - asm | x86  | 12213947        | 1594      | 24 |
| matbech/zlib   | x86  | 12208641        | 1500      | 26 |
| zlib ori       | x64  | 12213947        | 1594      | 23 |
| zlib ori - asm | x64  | 12213947        | 1515      | 24 |
| matbech/zlib   | x64  | 12208641        | 1329      | 34 |

