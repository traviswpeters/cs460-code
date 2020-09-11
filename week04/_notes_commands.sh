#  Notes on command line tools.

####################################################################################################

# list open files
lsof
lsof -u vagrant
lsof -p pid
lsof +D /usr/
lsof +D /lib/
lsof /lib/x86_64-linux-gnu/ld-2.27.so

####################################################################################################

# strace picks up right after fork() --> should start at 'exec()'
strace cat /dev/null # syscall trace; notice open/read
strace -c cat /dev/null # summary of syscalls
strace cat not_a_real_file

strace ./mystery1 what does this do ?
strace -c ./mystery1 what does this do ?

ltrace # similar to strace; for tracing library calls

####################################################################################################

ps m # enable thread info in ps
ps m -o pid,tid,command # custom format that shows thread ID

####################################################################################################

top
top -p pid
htop # way better than top!

####################################################################################################

time ls # use shell's implementation of 'time'
/usr/bin/time ls # use kernel's implementation of 'time'

####################################################################################################
