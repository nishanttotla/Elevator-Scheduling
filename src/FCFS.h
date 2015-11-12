#include "ElevatorManager.h"

/* This class extends the elevator manager with a simple FCFS scheduler */

class FCFS : public ElevatorManager {
  private:
    // some queue data structure to store pickup requests
  public:
    FCFS(int count, int floors);
    void pickup();
    void dropoff();
    void schedule();
};