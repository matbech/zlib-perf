master branch from  
https://github.com/gildor2/fast_zlib/  
using Sources\match.h  

with the following additional optimizations:  
- adler32  
- fill_window_sse  
- longest_match: compare match using _tzcnt_u32  
