#include "ElevatorManager.h"

int main() {
  ElevatorManager em(3,10);
  em.step();
  em.step();
  em.step();
  return 0;
}