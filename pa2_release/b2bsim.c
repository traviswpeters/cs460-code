/*
 * This is the b2bsim.c starter file!
 *
 * TODO: Write a brief summary of your program here.
 *
 * Author: YOUR NAME HERE :-)
 */

// includes (add more as you need them!)
#include <pthread.h>

// typedefs/structs

// constants

// global data shared by threads (e.g., the "oneway")

// global synchronization primitives (e.g., mutexes, condition variables)

// function declarations

/**
 * TODO: Implement oneVehicle.
 *
 * This is the main function of a car.
 *
 * 1. It simulates a car driving up to one side of the one-way.
 *    The car waits until it is okay to pass.
 *    => arriveOneWay()
 *
 * 2. Once it is safe to pass, the car proceeds onto the oneway and prints the current state of the simulation.
 *    (It is nice to simulate some time passing here - perhaps with a small "sleep" - cars take time to drive!)
 *    => onOneWay()
 *
 * 3. Finally, the thread (car) exits the one-way and finishes.
 *    => exitOneWay()
 */
// WRITE CODE HERE. (DELETE THIS COMMENT)

// ////////////////////////////////////////////////////////////////////////// //
//                                   Main                                     //
// ////////////////////////////////////////////////////////////////////////// //

int main(int argc, char* argv[]) {

    // TODO: handle input arguments (print help statement if needed)

    // TODO: initializations for simulation

    // TODO: main loop that drives the simulation
    // In each iteration of the loop...
    //   - initalize/update any info for keeping track of threads (cars)
    //   - create a thread (car) that starts running "oneVehicle"

    // TODO: wait for car threads to finish & cleanup.

    // TODO: display final state of your oneway simulation before exiting.

    return 0;
}
