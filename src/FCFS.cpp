#include "FCFS.h"
#include "assert.h"
#include <iostream>

FCFS::FCFS(int count, int floors) : ElevatorManager(count, floors) {

}

void FCFS::pickup(int floor, int direction) {
  PickupRequest pr;
  pr.requestTime = timeStep;
  pr.floor = floor;
  pr.direction = direction;

  pickupRequests.push_back(pr);
}

// store dropoff request when it comes
void FCFS::dropoff(int id, int floor) {
  ElevatorState st = status()[id];
  st.dropoffRequests.insert(floor);
  update(id, st);
}

void FCFS::schedule() {

}

void FCFS::printRequests() {
  for(std::deque<PickupRequest>::iterator it = pickupRequests.begin(); it != pickupRequests.end(); ++it) {
    printf("%d %d %d\n", it->requestTime, it->floor, it->direction);
  }
}