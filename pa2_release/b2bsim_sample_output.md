# Introduction

This document has notes about sample outputs from my solution.

You are free to do things however you like so long as your solution conforms to the specification for pa2.

## A note about _insufficient arguments_

My solution prints some "help" info when invoked without required arguments.

```bash
$ ./b2bsim
Usage:  ./b2bsim NUMCARS MAXCARS [VERBOSITY] [RANDSEED]

  NUMCARS      total # of cars to create for simulation
  MAXCARS      max # of cars allowed on one-way at one time
  VERBOSITY    0 (off), 1 (on)
  RANDSEED     seed for randomly generating numbers
```

## A note about _defaults_

Per the specification for pa2, `NUMCARS` and `MAXCARS` are **required** arguments;
`VERBOSITY` and `RANDSEED` are optional.

It is totally acceptable to invoke your simulation as follows:

```bash
$ ./b2bsim 10 2
```

In this case, your simulation should have _reasonable defaults_.
For instance,
- `VERBOSITY` should be disabled/off, and
- `RANDSEED` could be some hardcoded number or it could be a random number.

# Sample Output

Below I provide examples of how I invoked my solution from the command line.
Both samples are similar - the only difference is how **verbose** the output is,
which is dictated by the 3rd (optional) argument, `VERBOSITY`.

In this sample configuration:
- `NUMCARS = 10`: the simulation creates 10 threads (cars)
- `MAXCARS = 2`: the maximum number of cars allowed on the oneway at any given time is 2
- `VERBOSITY` `= 0` or `= 1`: (see below)
- `RANDSEED = 41`: fix the pseudorandom number generator seed (useful for testing)

## Example 1: Sample output for a normal run (TYPICAL OUTPUT)

```bash
$ ./b2bsim 10 2 0 41
```
**NOTE:** In this run `VERBOSITY = 0`, which only prints normal updates when the simulation changes.

```
=====================================================================================
                       Welcome to the Bridger Pass Simulator!
                    --------------------------------------------
Simulation Configuration:
  NUMCARS     = 10
  MAXCARS     = 2
  VERBOSITY   = 0
  RANDSEED    = 41
=====================================================================================

[*] Adding car 0: < Bridger [waiting: to Bozeman = 0 / to Bridger 1]
[*] flip direction: < Bridger [waiting: to Bozeman = 0 / to Bridger 1]
[0]-------------------------------------------------------------------------------------
   Direction           Waiting Cars         On Bridge        Cars Passed
  -----------         --------------       -----------      -------------
    < Bridger       0 TO_BOZEMAN->              1               (0) 0
                        <-TO_BRIDGER 0
[*] Adding car 1: > Bozeman [waiting: to Bozeman = 1 / to Bridger 0]
[*] Adding car 2: > Bozeman [waiting: to Bozeman = 2 / to Bridger 0]
[*] flip direction: > Bozeman [waiting: to Bozeman = 2 / to Bridger 0]
[1]-------------------------------------------------------------------------------------
   Direction           Waiting Cars         On Bridge        Cars Passed
  -----------         --------------       -----------      -------------
    > Bozeman       1 TO_BOZEMAN->              1               (0) 1
                        <-TO_BRIDGER 0
[2]-------------------------------------------------------------------------------------
   Direction           Waiting Cars         On Bridge        Cars Passed
  -----------         --------------       -----------      -------------
    > Bozeman       0 TO_BOZEMAN->              2               (0) 1
                        <-TO_BRIDGER 0
[*] Adding car 3: > Bozeman [waiting: to Bozeman = 1 / to Bridger 0]
[*] Adding car 4: < Bridger [waiting: to Bozeman = 1 / to Bridger 1]
[3]-------------------------------------------------------------------------------------
   Direction           Waiting Cars         On Bridge        Cars Passed
  -----------         --------------       -----------      -------------
    > Bozeman       0 TO_BOZEMAN->              2               (1) 2
                        <-TO_BRIDGER 1
[*] Adding car 5: > Bozeman [waiting: to Bozeman = 1 / to Bridger 1]
[5]-------------------------------------------------------------------------------------
   Direction           Waiting Cars         On Bridge        Cars Passed
  -----------         --------------       -----------      -------------
    > Bozeman       0 TO_BOZEMAN->              2               (2) 3
                        <-TO_BRIDGER 1
[*] Adding car 6: > Bozeman [waiting: to Bozeman = 1 / to Bridger 1]
[*] Adding car 7: > Bozeman [waiting: to Bozeman = 2 / to Bridger 1]
[7]-------------------------------------------------------------------------------------
   Direction           Waiting Cars         On Bridge        Cars Passed
  -----------         --------------       -----------      -------------
    > Bozeman       1 TO_BOZEMAN->              1               (4) 5
                        <-TO_BRIDGER 1
[*] Adding car 8: < Bridger [waiting: to Bozeman = 1 / to Bridger 2]
[6]-------------------------------------------------------------------------------------
   Direction           Waiting Cars         On Bridge        Cars Passed
  -----------         --------------       -----------      -------------
    > Bozeman       0 TO_BOZEMAN->              2               (4) 5
                        <-TO_BRIDGER 2
[*] Adding car 9: > Bozeman [waiting: to Bozeman = 1 / to Bridger 2]
[9]-------------------------------------------------------------------------------------
   Direction           Waiting Cars         On Bridge        Cars Passed
  -----------         --------------       -----------      -------------
    > Bozeman       0 TO_BOZEMAN->              2               (5) 6
                        <-TO_BRIDGER 2
[*] flip direction: < Bridger [waiting: to Bozeman = 0 / to Bridger 2]
[4]-------------------------------------------------------------------------------------
   Direction           Waiting Cars         On Bridge        Cars Passed
  -----------         --------------       -----------      -------------
    < Bridger       0 TO_BOZEMAN->              1               (0) 8
                        <-TO_BRIDGER 1
[8]-------------------------------------------------------------------------------------
   Direction           Waiting Cars         On Bridge        Cars Passed
  -----------         --------------       -----------      -------------
    < Bridger       0 TO_BOZEMAN->              2               (0) 8
                        <-TO_BRIDGER 0
[*] flip direction: > Bozeman [waiting: to Bozeman = 0 / to Bridger 0]

-----------------------------------------------------------------------------------------
Final State (before program exit):
-----------------------------------------------------------------------------------------
   Direction           Waiting Cars         On Bridge        Cars Passed
  -----------         --------------       -----------      -------------
    > Bozeman       0 TO_BOZEMAN->              0               (0) 10
                        <-TO_BRIDGER 0
```

## Example 2: Sample output for a normal run (VERBOSE OUTPUT)

```bash
$ ./b2bsim 10 2 1 41
```

**NOTE:** In this run `VERBOSITY = 1`, which prints normal updates when the simulation changes,
_as well as_ internal information about specific threads and what they are doing.
You'll likely have use this kind of output for testing/debugging.
It is nice, however, to be able to toggle the verbose output to be on/off.

```
=====================================================================================
                       Welcome to the Bridger Pass Simulator!                        
                    --------------------------------------------                     
Simulation Configuration:                                                            
  NUMCARS     = 10                                                                   
  MAXCARS     = 2                                                                   
  VERBOSITY   = 1                                                                   
  RANDSEED    = 41                                                                   
=====================================================================================

Thread 0: (arrive) arriving at oneway going < Bridger...
Thread 0: (arrive) trying to acquire lock...
[*] Adding car 0: < Bridger [waiting: to Bozeman = 0 / to Bridger 1]
[*] flip direction: < Bridger [waiting: to Bozeman = 0 / to Bridger 1]
Thread 0: (arrive) I'M IN!!!
Thread 0: (arrive) releasing the lock...
Thread 0: (arrive) signal next waiter headed < Bridger...
Thread 0: (printState) trying to acquire lock...
[0]-------------------------------------------------------------------------------------
   Direction           Waiting Cars         On Bridge        Cars Passed  
  -----------         --------------       -----------      -------------
    < Bridger       0 TO_BOZEMAN->              1               (0) 0        
                        <-TO_BRIDGER 0                                   

Thread 0: (printState) releasing the lock...
Thread 1: (arrive) arriving at oneway going > Bozeman...
Thread 1: (arrive) trying to acquire lock...
[*] Adding car 1: > Bozeman [waiting: to Bozeman = 1 / to Bridger 0]
Thread 2: (arrive) arriving at oneway going > Bozeman...
Thread 2: (arrive) trying to acquire lock...
Thread 0: (exit) trying to acquire lock...
Thread 3: (arrive) arriving at oneway going > Bozeman...
Thread 3: (arrive) trying to acquire lock...
Thread 1: (arrive) the condition is false, I'll wait (and release lock)
[*] Adding car 2: > Bozeman [waiting: to Bozeman = 2 / to Bridger 0]
Thread 2: (arrive) the condition is false, I'll wait (and release lock)
***ONE-WAY IS EMPTY!***
[*] flip direction: > Bozeman [waiting: to Bozeman = 2 / to Bridger 0]
Thread 0: (exit) releasing the lock...
======> Thread 0: exiting and leaving the oneway for good...
Thread 1: (arrive) I'm back, with the lock.  I'll test again
Thread 1: (arrive) I'M IN!!!
Thread 1: (arrive) releasing the lock...
Thread 1: (arrive) signal next waiter headed > Bozeman...
Thread 1: (printState) trying to acquire lock...
[1]-------------------------------------------------------------------------------------
   Direction           Waiting Cars         On Bridge        Cars Passed  
  -----------         --------------       -----------      -------------
    > Bozeman       1 TO_BOZEMAN->              1               (0) 1        
                        <-TO_BRIDGER 0                                   

Thread 1: (printState) releasing the lock...
Thread 2: (arrive) I'm back, with the lock.  I'll test again
Thread 2: (arrive) I'M IN!!!
Thread 2: (arrive) releasing the lock...
Thread 2: (arrive) signal next waiter headed > Bozeman...
Thread 2: (printState) trying to acquire lock...
[2]-------------------------------------------------------------------------------------
   Direction           Waiting Cars         On Bridge        Cars Passed  
  -----------         --------------       -----------      -------------
    > Bozeman       0 TO_BOZEMAN->              2               (0) 1        
                        <-TO_BRIDGER 0                                   

Thread 2: (printState) releasing the lock...
[*] Adding car 3: > Bozeman [waiting: to Bozeman = 1 / to Bridger 0]
Thread 4: (arrive) arriving at oneway going < Bridger...
Thread 4: (arrive) trying to acquire lock...
Thread 5: (arrive) arriving at oneway going < Bridger...
Thread 5: (arrive) trying to acquire lock...
Thread 6: (arrive) arriving at oneway going > Bozeman...
Thread 6: (arrive) trying to acquire lock...
Thread 7: (arrive) arriving at oneway going < Bridger...
Thread 7: (arrive) trying to acquire lock...
Thread 1: (exit) trying to acquire lock...
Thread 3: (arrive) the condition is false, I'll wait (and release lock)
[*] Adding car 4: < Bridger [waiting: to Bozeman = 1 / to Bridger 1]
Thread 8: (arrive) arriving at oneway going > Bozeman...
Thread 8: (arrive) trying to acquire lock...
Thread 2: (exit) trying to acquire lock...
Thread 9: (arrive) arriving at oneway going > Bozeman...
Thread 9: (arrive) trying to acquire lock...
Thread 4: (arrive) the condition is false, I'll wait (and release lock)
[*] Adding car 5: < Bridger [waiting: to Bozeman = 1 / to Bridger 2]
Thread 5: (arrive) the condition is false, I'll wait (and release lock)
[*] Adding car 6: > Bozeman [waiting: to Bozeman = 2 / to Bridger 2]
Thread 6: (arrive) the condition is false, I'll wait (and release lock)
[*] Adding car 7: < Bridger [waiting: to Bozeman = 2 / to Bridger 3]
Thread 7: (arrive) the condition is false, I'll wait (and release lock)
Thread 1: (exit) releasing the lock...
======> Thread 1: exiting and leaving the oneway for good...
Thread 3: (arrive) I'm back, with the lock.  I'll test again
Thread 3: (arrive) I'M IN!!!
Thread 3: (arrive) releasing the lock...
Thread 3: (arrive) signal next waiter headed > Bozeman...
Thread 3: (printState) trying to acquire lock...
[3]-------------------------------------------------------------------------------------
   Direction           Waiting Cars         On Bridge        Cars Passed  
  -----------         --------------       -----------      -------------
    > Bozeman       1 TO_BOZEMAN->              2               (1) 2        
                        <-TO_BRIDGER 3                                   

Thread 3: (printState) releasing the lock...
[*] Adding car 8: > Bozeman [waiting: to Bozeman = 2 / to Bridger 3]
Thread 8: (arrive) the condition is false, I'll wait (and release lock)
Thread 3: (exit) trying to acquire lock...
Thread 3: (exit) releasing the lock...
======> Thread 3: exiting and leaving the oneway for good...
Thread 8: (arrive) I'm back, with the lock.  I'll test again
Thread 8: (arrive) I'M IN!!!
Thread 8: (arrive) releasing the lock...
Thread 8: (arrive) signal next waiter headed > Bozeman...
Thread 8: (printState) trying to acquire lock...
[8]-------------------------------------------------------------------------------------
   Direction           Waiting Cars         On Bridge        Cars Passed  
  -----------         --------------       -----------      -------------
    > Bozeman       1 TO_BOZEMAN->              2               (2) 3        
                        <-TO_BRIDGER 3                                   

Thread 8: (printState) releasing the lock...
Thread 2: (exit) releasing the lock...
======> Thread 2: exiting and leaving the oneway for good...
Thread 6: (arrive) I'm back, with the lock.  I'll test again
Thread 6: (arrive) I'M IN!!!
Thread 6: (arrive) releasing the lock...
Thread 6: (arrive) signal next waiter headed > Bozeman...
Thread 6: (printState) trying to acquire lock...
[6]-------------------------------------------------------------------------------------
   Direction           Waiting Cars         On Bridge        Cars Passed  
  -----------         --------------       -----------      -------------
    > Bozeman       0 TO_BOZEMAN->              2               (3) 4        
                        <-TO_BRIDGER 3                                   

Thread 6: (printState) releasing the lock...
[*] Adding car 9: > Bozeman [waiting: to Bozeman = 1 / to Bridger 3]
Thread 8: (exit) trying to acquire lock...
Thread 6: (exit) trying to acquire lock...
Thread 9: (arrive) the condition is false, I'll wait (and release lock)
Thread 8: (exit) releasing the lock...
======> Thread 8: exiting and leaving the oneway for good...
***ONE-WAY IS EMPTY!***
Thread 6: (exit) releasing the lock...
======> Thread 6: exiting and leaving the oneway for good...
Thread 9: (arrive) I'm back, with the lock.  I'll test again
Thread 9: (arrive) I'M IN!!!
Thread 9: (arrive) releasing the lock...
Thread 9: (arrive) signal next waiter headed > Bozeman...
Thread 9: (printState) trying to acquire lock...
[9]-------------------------------------------------------------------------------------
   Direction           Waiting Cars         On Bridge        Cars Passed  
  -----------         --------------       -----------      -------------
    > Bozeman       0 TO_BOZEMAN->              1               (5) 6        
                        <-TO_BRIDGER 3                                   

Thread 9: (printState) releasing the lock...
Thread 9: (exit) trying to acquire lock...
***ONE-WAY IS EMPTY!***
[*] flip direction: < Bridger [waiting: to Bozeman = 0 / to Bridger 3]
Thread 9: (exit) releasing the lock...
Thread 4: (arrive) I'm back, with the lock.  I'll test again
Thread 4: (arrive) I'M IN!!!
Thread 4: (arrive) releasing the lock...
Thread 4: (arrive) signal next waiter headed < Bridger...
Thread 4: (printState) trying to acquire lock...
[4]-------------------------------------------------------------------------------------
   Direction           Waiting Cars         On Bridge        Cars Passed  
  -----------         --------------       -----------      -------------
    < Bridger       0 TO_BOZEMAN->              1               (0) 7        
                        <-TO_BRIDGER 2                                   

Thread 4: (printState) releasing the lock...
Thread 5: (arrive) I'm back, with the lock.  I'll test again
Thread 5: (arrive) I'M IN!!!
Thread 5: (arrive) releasing the lock...
Thread 5: (arrive) signal next waiter headed < Bridger...
Thread 5: (printState) trying to acquire lock...
[5]-------------------------------------------------------------------------------------
   Direction           Waiting Cars         On Bridge        Cars Passed  
  -----------         --------------       -----------      -------------
    < Bridger       0 TO_BOZEMAN->              2               (0) 7        
                        <-TO_BRIDGER 1                                   

Thread 5: (printState) releasing the lock...
Thread 7: (arrive) I'm back, with the lock.  I'll test again
Thread 7: (arrive) the condition is false, I'll wait (and release lock)
======> Thread 9: exiting and leaving the oneway for good...
Thread 5: (exit) trying to acquire lock...
Thread 5: (exit) releasing the lock...
======> Thread 5: exiting and leaving the oneway for good...
Thread 7: (arrive) I'm back, with the lock.  I'll test again
Thread 7: (arrive) I'M IN!!!
Thread 7: (arrive) releasing the lock...
Thread 7: (arrive) signal next waiter headed < Bridger...
Thread 7: (printState) trying to acquire lock...
[7]-------------------------------------------------------------------------------------
   Direction           Waiting Cars         On Bridge        Cars Passed  
  -----------         --------------       -----------      -------------
    < Bridger       0 TO_BOZEMAN->              2               (1) 8        
                        <-TO_BRIDGER 0                                   

Thread 7: (printState) releasing the lock...
Thread 7: (exit) trying to acquire lock...
Thread 7: (exit) releasing the lock...
======> Thread 7: exiting and leaving the oneway for good...
Thread 4: (exit) trying to acquire lock...
***ONE-WAY IS EMPTY!***
[*] flip direction: > Bozeman [waiting: to Bozeman = 0 / to Bridger 0]
Thread 4: (exit) releasing the lock...
======> Thread 4: exiting and leaving the oneway for good...
Thread -1: (printState) trying to acquire lock...

-----------------------------------------------------------------------------------------
Final State (before program exit):
-----------------------------------------------------------------------------------------
   Direction           Waiting Cars         On Bridge        Cars Passed  
  -----------         --------------       -----------      -------------
    > Bozeman       0 TO_BOZEMAN->              0               (0) 10        
                        <-TO_BRIDGER 0                                   

Thread -1: (printState) releasing the lock...

```
