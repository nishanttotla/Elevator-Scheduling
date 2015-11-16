#include "ElevatorManager.h"
#include <queue>

/* This class extends the elevator manager with a simple FCFS scheduler */

struct PickupRequest {
  int requestTime; // timestamp at which request arrived
  int floor;
  int direction; // 0 = down, 1 = up
};

class FCFS : public ElevatorManager {
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