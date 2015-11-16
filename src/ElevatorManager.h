#ifndef ELEVATOR_INTERFACE
#define ELEVATOR_INTERFACE

#include <vector>
#include <set>

struct ElevatorState {
  int currentFloor;
  int destination; // -1 = idle
  std::set<int> dropoffRequests; // dropoffs requested by passengers within elevator
};

class ElevatorManager {
  protected:
    int elevatorCount; // number of elevators, ids 0 to elevatorCount-1
    int timeStep; // time elapsed in the simulation
    int floorCount; // number of floors in the building, indexed 0 to floorCount-1
    std::vector<ElevatorState> currentState; // full state of all elevators
    // TODO : need basic data structures to keep state, scheduling will add it's own stuff

    void elevatorStep(int id); //time step for a single elevator

    virtual void schedule(); // main scheduling function
  public:
    ElevatorManager(int count, int floors); // initialize with number of elevators
    std::vector<ElevatorState> status(); // vector of elevator statuses indexed by id
    void update(int id, ElevatorState s); // update elevator state
    virtual void pickup(int floor, int direction); // 0 = down, 1 = up
    virtual void dropoff(int id, int floor); // request to dropoff when passenger is inside
    void step(); // time step

    void printState(); // prints current state
};

#endif