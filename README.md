# Elevator-Scheduling

## Algorithm
"Keep moving in one direction until possible, then reverse direction"
(list of destinations to go to is maintained for each elevator, algorithms executes at each step)

- For each elevator
    * if elevator has a direction
        * add all dropoffs in that direction to the list of destinations
        * if there are pickup requests for same direction, for floors in same direction,
            add them to list of destinations
        * if destination list is still empty, then reverse direction and repeat above steps
    * if elevator doesn't have a direction
        * if elevator has pending dropoffs, set direction to that of any one dropoff, and do above step

  > at this stage, each elevator either has a direction and some destinations,
  or a direction with no destinations, or no direction (hence no destinations ).
  Elevators in the last two cases are 'available' to schedule more pickup requests.


- For each 'available' elevator
    * pick a direction. Find the furthest request existing in that direction, set elevator
        direction to go to that floor. Then also add all pickup requests 'in that
        direction' to the destination list, as above. Try with the other direction
        if there's nothing in the first direction that was tried
    * if no requests are left at all, reset elevator direction

- For each elevator
    * update destination to closest floor in direction of movement that's also in its list of destinations

  > note that this algorithm does not perform load balancing, and current floor is counted for both directions.
