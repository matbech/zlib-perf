https://github.com/madler/zlib
with the asm from the contrib\masmx64 folder

compiler defines:
UNALIGNED_OK
ZLIB_CONST
ASMV
ASMINF

compiler options:
/O2 /GL

linker options:
/LTCG


IMPORTANT:
the asm implementation (gvmat64.asm) from the zlib contrib folder contains a bug:
The longest_match function accesses memory beyond the window boundary (deflate_state->window)
Do not use it.