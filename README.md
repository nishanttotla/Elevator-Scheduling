# Elevator-Scheduling

## Assumptions
The entire simulation runs on discrete time steps. Requests come in synchronously at each step, and scheduling is performed at each step too. Requests can be pickup requests or dropoff requests. The following flow is assumed
  1. Take step
  2. Get new pickup requests
  3. Get new dropoff requests
  4. Call scheduler to update schedule

This is super simplified, but allows for simple description of the scheduling algorithm.

## Code Description
All source files are in the `src` directory. Here's a brief description of contents
  - `ElevatorManager.h` and `ElevatorManager.cpp` : These contain the basic elevator interface that simulates the movement of the elevator. It updates the state based on the current state. A scheduler can be added by providing concrete definitions of the virtual functions in the `ElevatorManager` class.
  - `FCFS.h` and `FCFS.cpp` : This is a very naive FCFS scheduler, meant only to test out the elevator interface, and isn't very useful.
  - `BetterFCFS.h` and `BetterFCFS.cpp` : This is the scheduling algorithm described below. The implementation closely follows the description. It isn't the most optimal implementation, but should work for a reasonable number of elevators and floors.

## Algorithm
"Keep moving in one direction until possible, then reverse direction"
(list of destinations to go to is maintained for each elevator, algorithms executes at each step)

- For each elevator
    * if elevator has a direction
        * add all dropoffs in that direction to the list of destinations
        * if there are pickup requests for same direction, for floors in same direction,
            add them to list of destinations
        * if destination list is still empty, then reverse direction and repeat above steps
    * if elevator doesn't have a direction
        * if elevator has pending dropoffs, set direction to that of any one dropoff, and do above step

  > at this stage, each elevator either has a direction and some destinations,
  or a direction with no destinations, or no direction (hence no destinations ).
  Elevators in the last two cases are 'available' to schedule more pickup requests.


- For each 'available' elevator
    * pick a direction. Find the furthest request existing in that direction, set elevator
        direction to go to that floor. Then also add all pickup requests 'in that
        direction' to the destination list, as above. Try with the other direction
        if there's nothing in the first direction that was tried
    * if no requests are left at all, reset elevator direction

- For each elevator
    * update destination to closest floor in direction of movement that's also in its list of destinations

  > note that this algorithm does not perform load balancing, and current floor is counted for both directions.
  
## Execution Instructions
This code was built with the following version of `g++`
```
Configured with: --prefix=/Applications/Xcode.app/Contents/Developer/usr --with-gxx-include-dir=/usr/include/c++/4.2.1
Apple LLVM version 7.0.0 (clang-700.1.76)
Target: x86_64-apple-darwin14.5.0
Thread model: posix
```
But it should work with most other new versions before `C++11`. Some future work involves cleaning up the build and providing a simple Makefile. To build the code, run
`g++ main.cpp ElevatorManager.cpp BetterFCFS.cpp -o elevSched`
To execute, run
`./elevSched`

The current version comes with a sample with 2 elevators and 10 floors. To run with a different example, edit `main.cpp` as follows:
```
BetterFCFS em(elevators, floors);

while(1) {
  em.step();
  getPickupRequests(em); // can be implemented separately to call em.pickup
  getDropoffRequests(em); // can be implemented separately to call em.dropoff
  em.schedule()
}
```

## Limitations
The scheduling algorithm was designed in a short time frame, and has a lot of rough edges. In particular, it contains a lot of linear searches that can be optimized, but weren't deemed necessary for a first-cut version.
Also missing is a good front-end and analysis framework. Currently `main.cpp` must be changed to add input, but an additional class can easily be added as a front-end. In terms of analysis, there are several interesting questions to ask about the performance of the algorithm. These questions are listed below, but their implementations are missing.

## Analysis
To judge performance of the algorithm and to compare with naive FCFS, the following would be interesting questions
