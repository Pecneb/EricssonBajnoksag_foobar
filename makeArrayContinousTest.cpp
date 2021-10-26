#include "makeArrayContinous.cpp"
#include <iostream>

int main() {
  for(int i=-19; i<19; i++) {
    std::cout << i << ": " << makeArrayContinous(i,9) << "\n";
  }
  return 0;
}
