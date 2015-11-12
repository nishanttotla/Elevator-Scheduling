#include "ElevatorManager.h"
#include <queue>

/* This class extends the elevator manager with a simple FCFS scheduler */

class FCFS : public ElevatorManager {
  private:
    // queue to store pickup requests
    std::deque<PickupRequest> pickupRequests;
  public:
    FCFS(int count, int floors);
    void pickup(int floor, int direction);
    void dropoff(int id, int floor);
    void schedule();
    void printRequests(); // for debugging
};