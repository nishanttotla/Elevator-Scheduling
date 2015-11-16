#include "ElevatorManager.h"
#include <queue>

/* This class extends the elevator manager with a simple FCFS scheduler */

/* Algorithm
(assumes a list of destinations to go to has been maintained, algorithms executes at each step)
- For each elevator
    > if elevator has a direction, then add all dropoffs in that direction to the list of destinations
    > it elevator doesn't have a direction, but has pending dropoffs, then pick a direction and add dropoffs in that direction to list of destinations
[at this stage, each elevator has a direction, or no destination at all]
- For each pickup request
    > add it to the list of destinations for an elevator that has an empty list, or is moving in the direction of the requested floor, with the requested direction being the same
- For each elevator
    > update destination to closest floor in the direction of movement
*/

struct ExtendedElevatorState {
    std::set<int> destinations;
};

class BetterFCFS : public ElevatorManager {
  private:
    // extended state information
    std::vector<ExtendedElevatorState> extendedState; // extended state for all elevators
    // queue to store pickup requests
    std::deque<PickupRequest> pickupRequests;
  public:
    FCFS(int count, int floors);
    void pickup(int floor, int direction);
    void dropoff(int id, int floor);
    void schedule();
    void printRequests(); // for debugging
};