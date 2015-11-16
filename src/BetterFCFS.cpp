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

// if direction != -1, then destination list must be non-empty
void BetterFCFS::updateDestinations() {
  std::vector<ElevatorState> st = status();
  for(int i=0; i<elevatorCount; i++) {
    if(extendedState[i].direction == 1) {
      int min = floorCount;
      for(std::set<int>::iterator it=extendedState[i].destinations.begin(); it!=extendedState[i].destinations.end(); ++it) {
        if(*it < min) min = *it;
      }
      st[i].destination = min;
      update(i, st[i]);
    } else if(extendedState[i].direction == 0) {
      int max = -1;
      for(std::set<int>::iterator it=extendedState[i].destinations.begin(); it!=extendedState[i].destinations.end(); ++it) {
        if(*it > max) max = *it;
      }
      st[i].destination = max;
      update(i, st[i]);
    }
  }
}

int BetterFCFS::reverseDirection(int dir) {
  if(dir == 0) return 1;
  else if(dir == 1) return 0;
  else return -1;
}

// function also adds request to destination list if found
int BetterFCFS::findFurthestRequestedFloorInDirection(int id, int floor, int direction) {
  if(direction == 1) {
    int max = -1;
    for(int i=floor; i<floorCount; i++) {
      if(pickupRequests[i].up || pickupRequests[i].down) max = i;
    }
    if(max > -1) {
      extendedState[id].destinations.insert(max);
      if(pickupRequests[max].up) {
        pickupRequests[max].up = false;
        pickupRequests[max].upAssigned = true;
      } else {
        pickupRequests[max].down = false;
        pickupRequests[max].downAssigned = true;
      }
      return max;
    }
  } else if(direction == 0) {
    int min = floorCount;
    for(int i=floor; i>=0; i--) {
      if(pickupRequests[i].up || pickupRequests[i].down) min = i;
    }
    if(min < floorCount) {
      extendedState[id].destinations.insert(min);
      if(pickupRequests[min].down) {
        pickupRequests[min].down = false;
        pickupRequests[min].downAssigned = true;
      } else {
        pickupRequests[min].up = false;
        pickupRequests[min].upAssigned = true;
      }
      return min;
    }
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
      if(st[i].dropoffRequests.empty()) {
        available.push_back(i);
      } else {
        std::set<int>::iterator it = st[i].dropoffRequests.begin();
        if(*it >= st[i].currentFloor) {
          curDir = 1;
          extendedState[i].direction = curDir;
        }
        else {
          curDir = 0;
          extendedState[i].direction = curDir;
        }
        addDropoffRequestsForDirection(i, curDir);
      }
    }
  }

  for(int i=0; i<available.size(); i++) {
    int curDir = 0; // default down, but is a parameter and can be adjusted
    int furthest = findFurthestRequestedFloorInDirection(available[i], st[available[i]].currentFloor, curDir);

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

void BetterFCFS::printExtendedState() {
  printf("Extended state\n");
  for(int i=0; i<extendedState.size(); i++) {
    printf("%d %d\n", extendedState[i].direction, extendedState[i].destinations.size());
  }
  printf("------------------\n");
}
