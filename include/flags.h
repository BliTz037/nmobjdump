#ifndef __BFD_H_SEEN__
#define __BFD_H_SEEN__

#define BFD_NO_FLAGS 0x00
#define HAS_RELOC 0x01
#define EXEC_P 0x02

/* BFD has line number information (basically used for F_LNNO in a
   COFF header).  */
#define HAS_LINENO 0x04

/* BFD has debugging information.  */
#define HAS_DEBUG 0x08
#define HAS_SYMS 0x10

/* BFD has local symbols (basically used for F_LSYMS in a COFF
   header).  */
#define HAS_LOCALS 0x20
#define DYNAMIC 0x40

/* Text section is write protected (if D_PAGED is not set, this is
   like an a.out NMAGIC file) (the linker sets this by default, but
   clears it for -r or -N).  */
#define WP_TEXT 0x80
#define D_PAGED 0x100

#endif
