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

Examine user limits:

```bash
$ ulimit -a
core file size          (blocks, -c) unlimited
data seg size           (kbytes, -d) unlimited
scheduling priority             (-e) 0
file size               (blocks, -f) unlimited
pending signals                 (-i) 7816
max locked memory       (kbytes, -l) 16384
max memory size         (kbytes, -m) unlimited
open files                      (-n) 1024
pipe size            (512 bytes, -p) 8
POSIX message queues     (bytes, -q) 819200
real-time priority              (-r) 0
stack size              (kbytes, -s) 8192
cpu time               (seconds, -t) unlimited
max user processes              (-u) 7816
virtual memory          (kbytes, -v) unlimited
file locks                      (-x) unlimited
```
