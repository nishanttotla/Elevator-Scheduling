#include "BetterFCFS.h"
#include "assert.h"
#include <iostream>
#include <cmath>

BetterFCFS::BetterFCFS(int count, int floors) : ElevatorManager(count, floors) {
  // initialize extended elevator state
  for(int i=0; i<count; i++) {
    ExtendedElevatorState newState;
    newState.direction = -1;
    extendedState.push_back(newState);
  }

  // initialize data structure for pickup requests
  for(int i=0; i<floors; i++) {
    FloorRequest fr;
    fr.up = false; fr.upTimestamp = 0; fr.upAssigned = false;
    fr.down = false; fr.downTimestamp = 0; fr.downAssigned = false;
    pickupRequests.push_back(fr);
  }
}

void BetterFCFS::pickup(int floor, int direction) {
  FloorRequest fr = pickupRequests[floor];
  if(direction == 0) { // down request
    if(!fr.down && !fr.downAssigned) { // no down request && no elevator assigned
      fr.down = true;
      fr.downTimestamp = timeStep;
      pickupRequests[floor] = fr;
    }
  } else {
    if(!fr.up && !fr.upAssigned) { // no down request && no elevator assigned
      fr.up = true;
      fr.upTimestamp = timeStep;
      pickupRequests[floor] = fr;
    }
  }
}

// store dropoff request when it comes
void BetterFCFS::dropoff(int id, int floor) {
  ElevatorState st = status()[id];
  st.dropoffRequests.insert(floor);
  update(id, st);
}

// follows algorithm in BetterFCFS.h
void BetterFCFS::schedule() {
  std::vector<ElevatorState> st = status();
}

void BetterFCFS::printRequests() {

}