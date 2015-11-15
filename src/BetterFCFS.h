#include "ElevatorManager.h"
#include <queue>

/* This class extends the elevator manager with a simple FCFS scheduler */

/* Algorithm
(assumes a list of destinations to go to has been maintained, algorithms executes at each step)
- For each elevator
    > if elevator has a direction, then add all dropoffs in that direction to the list of destinations
    > it elevator doesn't have a direction, but has pending dropoffs, then pick a direction and add dropoffs in that direction to list of destinations
[at this stage, each elevator has a direction, or no requests at all]
- For each pickup request
    > add it to the list of destinations for an elevator that has an empty list, or is movinng in the direction of the requested floor
- For each elevator
    > update destination to closest floor in the direction of movement
*/

class BetterFCFS : public ElevatorManager {
  private:
    // queue to store pickup requests
    std::deque<PickupRequest> pickupRequests;
    int findClosestDropoff(ElevatorState st); // assumes non-empty dropoff list
    int findClosestElevator(std::set<int> available, int floor); // assumes at least one free elevator, returns id
  public:
    FCFS(int count, int floors);
    void pickup(int floor, int direction);
    void dropoff(int id, int floor);
    void schedule();
    void printRequests(); // for debugging
};