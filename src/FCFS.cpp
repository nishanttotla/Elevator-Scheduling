#include "FCFS.h"
#include "assert.h"
#include <iostream>
#include <cmath>

FCFS::FCFS(int count, int floors) : ElevatorManager(count, floors) {

}

int FCFS::findClosestDropoff(ElevatorState st) {
  int minGap = floorCount;
  int dropoff = -1;
  for(std::set<int>::iterator it = st.dropoffRequests.begin(); it != st.dropoffRequests.end(); ++it) {
    if(abs(st.currentFloor - *it) < minGap) {
      minGap = abs(st.currentFloor - *it) < minGap;
      dropoff = *it;
    }
  }

  return dropoff;
}

int FCFS::findClosestElevator(std::set<int> available, int floor) {
  std::vector<ElevatorState> st = status();

  std::set<int>::iterator it = available.begin();
  int closest = *it;
  int minGap = abs(floor - st[*it].currentFloor);

  for(it = available.begin(); it != available.end(); ++it) {
    if(abs(floor - st[*it].currentFloor) < minGap) {
      minGap = abs(floor - st[*it].currentFloor);
      closest = *it;
    }
  }
  return closest;
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
  // elevators with destination = -1 are free for scheduling
  // if destination = -1 and there are no dropoff requests, then satisfy a pickup request
  // otherwise satisfy a dropoff request
  // if none of these, then do nothing
  std::vector<ElevatorState> st = status();
  std::set<int> available;

  for(int i=0; i<st.size(); i++) {
    if(st[i].destination == -1) {
      if(st[i].dropoffRequests.size() > 0) { // find closest dropoff request and go there
        st[i].destination = findClosestDropoff(st[i]);
        update(i, st[i]);
      } else { // add elevator to set of available ones
        available.insert(i);
      }
    }
  }

  // TODO : if current floor is requested, need to delete it from pickupRequests

  // assign available elevators to handle pickup requests
  std::deque<PickupRequest>::iterator it = pickupRequests.begin();
  while(it != pickupRequests.end() && available.size() > 0) {
    int closestId = findClosestElevator(available, it->floor);

    available.erase(closestId);
    st[closestId].destination = it->floor;
    update(closestId, st[closestId]);

    pickupRequests.pop_front();
    it = pickupRequests.begin();
  }
}

void FCFS::printRequests() {
  for(std::deque<PickupRequest>::iterator it = pickupRequests.begin(); it != pickupRequests.end(); ++it) {
    printf("%d %d %d\n", it->requestTime, it->floor, it->direction);
  }
}