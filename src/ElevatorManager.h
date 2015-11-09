#include <vector>

struct ElevatorState {
  int currentFloor;
  int destination; // -1 = no requests
  int doorStatus; // 0 = closed, 1 = open
};

struct PickupRequest {
  int floor;
  int direction; // 0 = down, 1 = up
};

class ElevatorManager {
  protected:
    int elevatorCount; // number of elevators, ids 0 to elevatorCount-1
    int timeStep; // time elapsed in the simulation
    int floorCount; // number of floors in the building, indexed 0 to floorCount-1
    std::vector<ElevatorState> currentState; // full state of all elevators
    std::vector<PickupRequest> requests; // all unhandled requests
    // TODO : need basic data structures to keep state, scheduling will add it's own stuff

    void elevatorStep(); //time step for a single elevator
  public:
    ElevatorManager(int count, int floors); // initialize with number of elevators
    std::vector<ElevatorState> status(); // vector of elevator statuses indexed by id
    void update(int id, ElevatorState s); // update elevator state
    void pickup(int floor, int direction); // 0 = down, 1 = up
    void step(); // time step

    void printState(); // prints current state
};