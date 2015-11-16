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

void BetterFCFS::addPickupRequestsForDirection(int id, int direction) {
  ElevatorState st = status()[id];
  for(int i=0; i<floorCount; i++) {
    if(direction == 1 && i>=st.currentFloor && pickupRequests[i].up) {
      extendedState[id].destinations.insert(i);
      pickupRequests[i].up = false;
      pickupRequests[i].upAssigned = true;
    } else if(direction == 0 && i<=st.currentFloor && pickupRequests[i].down) {
      extendedState[id].destinations.insert(i);
      pickupRequests[i].down = false;
      pickupRequests[i].downAssigned = true;
    }
  }
}

void BetterFCFS::addDropoffRequestsForDirection(int id, int direction) {
  ElevatorState st = status()[id];
  // careful! iterating over set while deleting
  for(std::set<int>::iterator it = st.dropoffRequests.begin(); it != st.dropoffRequests.end();) {
    if((direction == 1 && *it >= st.currentFloor) || (direction == 0 && *it <= st.currentFloor)) {
      extendedState[id].destinations.insert(*it);
      st.dropoffRequests.erase(it++);
    } else {
      ++it;
    }
  }
  update(id, st);
}

void BetterFCFS::updateDestinations() {

}

int BetterFCFS::reverseDirection(int dir) {
  if(dir == 0) return 1;
  else if(dir == 1) return 0;
  else return -1;
}

// function also adds request to destination list if found
int BetterFCFS::findFurthestRequestedFloorInDirection(int id, int floor, int direction) {
  if(direction == 1) {

  } else if(direction == 0) {

  }
  return -1;
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
  std::vector<int> available; // available elevators

  ////// scheduling algorithm start //////
  for(int i=0; i<elevatorCount; i++) {
    // first update some data structures to indicate that this floor has been served
    if(extendedState[i].destinations.find(st[i].currentFloor) != extendedState[i].destinations.end()) {
      extendedState[i].destinations.erase(st[i].currentFloor);
      pickupRequests[st[i].currentFloor].upAssigned = false;
      pickupRequests[st[i].currentFloor].downAssigned = false;
    }

    int curDir = extendedState[i].direction;
    if(curDir != -1) {
      addDropoffRequestsForDirection(i, curDir);
      addPickupRequestsForDirection(i, curDir);

      if(extendedState[i].destinations.empty()) {
        curDir = reverseDirection(curDir);
        extendedState[i].direction = curDir;

        addDropoffRequestsForDirection(i, curDir);
        addPickupRequestsForDirection(i, curDir);
      }

      if(extendedState[i].destinations.empty()) {
        available.push_back(i);
      }
    } else {
      available.push_back(i);
    }
  }

  for(int i=0; i<available.size(); i++) {
    int curDir = 0; // default down, but is a parameter and can be adjusted
    int furthest = findFurthestRequestedFloorInDirection(st[available[i]].currentFloor, curDir);

    if(furthest == -1) {
      curDir = reverseDirection(curDir);
      extendedState[available[i]].direction = curDir;
      furthest = findFurthestRequestedFloorInDirection(available[i], st[available[i]].currentFloor, curDir);
      if(furthest == -1) {
        extendedState[i].direction = -1;
      } else {
        addPickupRequestsForDirection(available[i], curDir);
      }
    } else {
      addPickupRequestsForDirection(available[i], curDir);
    }
  }

  updateDestinations();
}
