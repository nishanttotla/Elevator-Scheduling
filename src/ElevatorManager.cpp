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
    newState.doorStatus = 0;

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
  PickupRequest pr;
  pr.floor = floor;
  pr.direction = direction;
  requests.push_back(pr);
}

// runs a step of the simulation for a single elevator, using information about the current state
void ElevatorManager::elevatorStep() {

}

// runs a step of the simulation for all elevators, using information about the current state
void ElevatorManager::step() {

}

// prints state of all elevators
void ElevatorManager::printState() {
  for(int i=0; i<currentState.size(); i++) {
    printf("%d %d %d\n", currentState[i].currentFloor, currentState[i].destination, currentState[i].doorStatus);
  }
}