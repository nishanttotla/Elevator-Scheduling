#include "ElevatorManager.h"

/* This class extends the elevator manager with a simple FCFS scheduler */

/* Algorithm
(assumes a list of destinations to go to has been maintained, algorithms executes at each step)
- For each elevator
    > if elevator has a direction, then add all dropoffs in that direction to the list of destinations
    > it elevator doesn't have a direction, but has pending dropoffs, then pick a direction and add dropoffs in that direction to list of destinations
[at this stage, each elevator has a direction, or no destination at all]
- For each pickup request
    > add it to the list of destinations for an elevator that is moving in the direction of the requested floor, with the requested direction being the same
    > if not found, add it to the list of destionation for an elevator that has an empty list
    [no load balancing happening here]
- For each elevator
    > update destination to closest floor in the direction of movement
*/

struct ExtendedElevatorState {
    std::set<int> destinations;
};

// struct used to check if a given floor has up/down requests
struct FloorRequest {
    bool up;
    int upTimestamp; // timestamp for oldest up request, only counts if up == true
    bool upAssigned; // has up request for floor been assigned (pending) to some elevator? (makes sense if up == false)
    bool down;
    int downTimestamp; // timestamp for oldest down request, only counts if down == true
    bool downAssigned; // has down request for floor been assigned (pending) to some elevator? (makes sense if down == false)
};

class BetterFCFS : public ElevatorManager {
  private:
    // extended state information
    std::vector<ExtendedElevatorState> extendedState; // extended state for all elevators
    // queue to store pickup requests
    std::vector<FloorRequest> pickupRequests;
  public:
    BetterFCFS(int count, int floors);
    void pickup(int floor, int direction);
    void dropoff(int id, int floor);
    void schedule();
    void printRequests(); // for debugging
};