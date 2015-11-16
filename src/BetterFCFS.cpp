#include "BetterFCFS.h"
#include "assert.h"
#include <iostream>
#include <cmath>

BetterFCFS::BetterFCFS(int count, int floors) : ElevatorManager(count, floors) {
  // initialize extended elevator state
  for(int i=0; i<count; i++) {
    ExtendedElevatorState newState;
    extendedState.push_back(newState);
  }

  // initialize data structure for pickup requests
  for(int i=0; i<floors; i++) {
    FloorRequest fr;
    fr.up = false; fr.upTimestamp = 0;
    fr.down = false; fr.downTimestamp = 0;
    pickupRequests.push_back(fr);
  }
}

void BetterFCFS::pickup(int floor, int direction) {

}

// store dropoff request when it comes
void BetterFCFS::dropoff(int id, int floor) {

}

void BetterFCFS::schedule() {

}

void BetterFCFS::printRequests() {

}