#!/bin/bash
p="/usr/lib/gcc/x86_64-redhat-linux/9/32"
c="/usr/libexec/gcc/x86_64-redhat-linux/9"
if [ $# == 4 ] 
then
    $c/collect2 --build-id -m elf_i386 --hash-style=gnu -static -o $1 -u exit -u __brk -u __sbrk -u __mmap -u __default_morecore /usr/lib/crt1.o /usr/lib/crti.o $p/crtbeginT.o -L $2/lib -L$p -L/lib/ -L/usr/lib -T $2/etc/user.x  $3 $4 -lyuser  --start-group -lgcc -lgcc_eh  --end-group $p/crtend.o /usr/lib/crtn.o
else if [ $# == 3 ] 
then
    $c/collect2 --build-id -m elf_i386 --hash-style=gnu -static -o $1 -u exit -u __brk -u __sbrk -u __mmap -u __default_morecore /usr/lib/crt1.o /usr/lib/crti.o $p/crtbeginT.o -L $2/lib -L$p -L/lib/ -L/usr/lib -T $2/etc/user.x  $3 -lyuser  --start-group -lgcc -lgcc_eh  --end-group $p/crtend.o /usr/lib/crtn.o
else
    echo "yuserbuild <executable name> <yalnix path> <objname>"
fi
fi
