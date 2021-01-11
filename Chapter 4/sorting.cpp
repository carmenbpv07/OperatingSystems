#include <iostream>
#include <thread>
const long long size = 12;

/** Chapter 4: Threads & Concurrency
    Programming Projects P-26
    Project 2 — Multithreaded Sorting Application
    To compile: g++ -std=c++11 sorting.cpp -o sorting -pthread
    To execute: ./sorting
**/
using namespace std;

long long* arr = new long long[size];

void sort(long long* array, long long init, long long final) {
  long long i = init;
  long long f = final;
  long long tmp;
  long long x = array[(init + final) / 2];
  do {
    while (x > array[i] && f <= final) {
      i++;
    }
    while (array[f] > x && f > init) {
      f--;
    }
    if (i <= f) {
      tmp = array[i];
      array[i] = array[f];
      array[f] = tmp;
      i++;
      f--;
    }
  } while (i <= f);

  if (init < f) {
    sort(array, init, f);
  }
  if (i < final) {
    sort(array, i, final);
  }
}

void merge(long long low, long long mid, long long high) {
  long long* left = new long long[mid - low];
  long long* right = new long long[high - mid];
  long long n1 = mid - low, n2 = high - mid, i, j;
  for (i = 0; i < n1; i++) left[i] = arr[i + low];
  for (i = 0; i < n2; i++) right[i] = arr[i + mid];
  long long k = low;
  i = j = 0;
  while (i < n1 && j < n2) {
    if (left[i] <= right[j])
      arr[k++] = left[i++];
    else
      arr[k++] = right[j++];
  }
  while (i < n1) {
    arr[k++] = left[i++];
  }
  while (j < n2) {
    arr[k++] = right[j++];
  }
  delete left;
  delete right;
}

int main() {
  srand(time(NULL));
  for (int i = 0; i < size; i++) {
    arr[i] = (rand() % 100);
  }
  thread t1(sort, arr, 0, size / 2);
  thread t2(sort, arr, (size / 2) + 1, size - 1);
  t1.join();
  t2.join();
  thread t3(merge, 0, (size / 2) + 1, size);
  t3.join();
  cout << "Sorted array: ";
  for (long long i = 0; i < size; i++) {
    cout << arr[i] << " ";
  }
  cout << "\n";
}
