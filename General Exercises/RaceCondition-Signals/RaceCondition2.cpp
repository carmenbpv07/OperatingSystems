// g++ -std=c++0x -pthread -o RaceCondition2.exe  RaceCondition2.cpp

#include <chrono>    // std::chrono::seconds
#include <iostream>  // std::cout
#include <thread>    // std::thread, std::this_thread::sleep_for

void pause_thread(int n) {
  for (;;) {
  }
  std::cout << "Thread with ID: " << n << "\n";
}

int main() {
  std::cout << "Spawning and detaching 3 threads...\n";
  for (int x = 1; x < 10; x++) {
    std::thread(pause_thread, x).detach();
  }
  std::cout << "End of threads \n";
  for (;;) {
  }
  return 0;
}

/*
Spawning and detaching 3 threads...
End of threads
...
*/