#include "ElevatorManager.h"
#include "FCFS.h"

int main() {
  FCFS em(3,10);
  em.step();
  em.dropoff(0,5);
  em.step();
  em.dropoff(0,8);
  em.dropoff(1,4);
  em.step();
  return 0;
}