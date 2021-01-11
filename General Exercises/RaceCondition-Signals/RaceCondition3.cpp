// g++ -std=c++0x -pthread -o RaceCondition3.exe  RaceCondition3.cpp

#include <chrono>    // std::chrono::seconds
#include <iostream>  // std::cout
#include <thread>    // std::thread, std::this_thread::sleep_for

int contador;
void pause_thread(int n) {
  std::cout << "Thread with ID: " << n << "\n";
  contador++;
}

int main() {
  contador = 0;
  std::cout << "Spawning and detaching 3 threads...\n";
  for (int x = 1; x < 10; x++) {
    std::thread(pause_thread, x).detach();
  }
  std::cout << "End of threads \n";
  for (;;) {
    if (contador == 9) {
      break;
    }
  }
  return 0;
}

/*
Spawning and detaching 3 threads...
End of threads
Thread with ID: 7
Thread with ID: 8
Thread with ID: 9
Thread with ID: 6
Thread with ID: 5
Thread with ID: 4
Thread with ID: 3
Thread with ID: 2
Thread with ID: 1
*/