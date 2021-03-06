#include "ElevatorManager.h"
#include "assert.h"
#include <iostream>

// initializes elevator manager state, all elevators on floor 0
ElevatorManager::ElevatorManager(int count, int floors) {
  assert(count > 0 && floors > 0);
  elevatorCount = count;
  timeStep = 0;
  floorCount = floors;

  // initialize elevator states
  for(int i=0; i<elevatorCount; i++) {
    ElevatorState newState;
    newState.currentFloor = 0;
    newState.destination = -1;

    currentState.push_back(newState);
  }
}

// returns full current status of all elevators
std::vector<ElevatorState> ElevatorManager::status() {
  return currentState;
}

// updates elevator status
void ElevatorManager::update(int id, ElevatorState s) {
  currentState[id] = s;
}

// adds pickup request
void ElevatorManager::pickup(int floor, int direction) {
  // do nothing unless a scheduler is defined
}

// adds dropoff request
void ElevatorManager::dropoff(int floor, int direction) {
  // do nothing unless a scheduler is defined
}

// runs a step of the simulation for a single elevator, using information about the current state
// it takes a time step to open/close door on a given floor
void ElevatorManager::elevatorStep(int id) {
  ElevatorState st = currentState[id];
  if(st.destination == -1) return; // elevator not assigned any task

  if(st.destination > st.currentFloor) { // move up one floor
    st.currentFloor++;
  } else if(st.destination < st.currentFloor) { // move down one floor
    st.currentFloor--;
  } else { // at destination
    // if just reached destination, elevator resets destionation and stays for a time step
    // scheduler can reassign a destination to this elevator now
    st.destination = -1;
    // delete dropoff request if one existed for this floor
    if(st.dropoffRequests.find(st.currentFloor) != st.dropoffRequests.end()) {
      st.dropoffRequests.erase(st.currentFloor);
    }
  }
  currentState[id] = st;
}

// runs a step of the simulation for all elevators, using information about the current state
void ElevatorManager::step() {
  for(int i=0; i<currentState.size(); i++) {
    elevatorStep(i);
  }
  timeStep++;
  printState();
}

// prints state of all elevators
void ElevatorManager::printState() {
  printf("Timesteps done: %d\n", timeStep);
  for(int i=0; i<currentState.size(); i++) {
    printf("%d %d %d\n", currentState[i].currentFloor, currentState[i].destination, currentState[i].dropoffRequests.size());
  }
  printf("---------\n");
}

void ElevatorManager::schedule() {
  // do nothing
}