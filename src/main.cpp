#include "ElevatorManager.h"
#include "FCFS.h"

int main() {
  FCFS em(1,100);

  em.step();
  em.pickup(4,1);
  em.schedule();

  em.step();
  em.schedule();

  em.step();
  em.schedule();

  em.step();
  em.pickup(2,1);
  em.schedule();

  em.step();
  em.dropoff(0,7);
  em.schedule();

  em.step();
  em.schedule();

  em.step();
  em.schedule();

  em.step();
  em.schedule();

  em.step();
  em.schedule();

  em.step();
  em.schedule();

  em.step();
  em.schedule();

  em.step();
  em.schedule();

  em.step();
  em.dropoff(0,0);
  em.schedule();

  em.step();
  em.schedule();

  em.step();
  em.schedule();

  em.step();
  em.schedule();

  em.step();
  em.schedule();

  em.step();
  em.schedule();

  em.step();
  em.schedule();
  return 0;
}