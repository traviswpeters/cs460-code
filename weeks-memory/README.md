Some definitions adapted from Yalnix.

See `yalnix-framework/include/hardware.h`:

```c
// [pagenum][offset]
//    2^19    2^13

#define PAGESIZE	0x2000		   // 8K = 0000 0000 0000 0000 0010 0000 0000 0000
#define PAGEOFFSET	(PAGESIZE-1)   //    = 0000 0000 0000 0000 0001 1111 1111 1111
#define PAGEMASK	(~PAGEOFFSET)  //    = 1111 1111 1111 1111 1110 0000 0000 0000
#define PAGESHIFT	13
```
