#include "ElevatorManager.h"

/* This class extends the elevator manager with a simple FCFS scheduler */

struct ExtendedElevatorState {
    int direction; // -1 = none, 0 = down, 1 = up
    std::set<int> destinations;
};

// struct used to check if a given floor has up/down requests
struct FloorRequest {
    bool up;
    int upTimestamp; // timestamp for oldest up request, only counts if up == true
    bool upAssigned; // has up request for floor been assigned (pending) to some elevator? (makes sense if up == false)
    bool down;
    int downTimestamp; // timestamp for oldest down request, only counts if down == true
    bool downAssigned; // has down request for floor been assigned (pending) to some elevator? (makes sense if down == false)
};

class BetterFCFS : public ElevatorManager {
  private:
    // extended state information
    std::vector<ExtendedElevatorState> extendedState; // extended state for all elevators
    // queue to store pickup requests
    std::vector<FloorRequest> pickupRequests;

    int minSet(std::set<int> s, int flag);
    void addPickupRequestsForDirection(int id, int direction); // add all pickup requests 'in the direction' for elevator id
    void addDropoffRequestsForDirection(int id, int direction);
    void updateDestinations(); // update next destination after updating destination list
    int reverseDirection(int dir); // function that returns reversed direction
    int findFurthestRequestedFloorInDirection(int id, int floor, int direction); // returns floor number and adds arbitrary request from that floor, returns -1 if nothing found
  public:
    BetterFCFS(int count, int floors);
    void pickup(int floor, int direction);
    void dropoff(int id, int floor);
    void schedule();
    void printExtendedState();
};