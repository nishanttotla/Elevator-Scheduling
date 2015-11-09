#include <vector>

struct ElevatorState {
  int currentFloor;
  int destination; // -1 = no requests
};

struct PickupRequest {
  int requestTime; // timestamp at which request arrived
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

    void elevatorStep(int id); //time step for a single elevator

    virtual void schedule(); // main scheduling function
  public:
    ElevatorManager(int count, int floors); // initialize with number of elevators
    std::vector<ElevatorState> status(); // vector of elevator statuses indexed by id
    void update(int id, ElevatorState s); // update elevator state
    virtual void pickup(int floor, int direction); // 0 = down, 1 = up
    void step(); // time step

    void printState(); // prints current state
};