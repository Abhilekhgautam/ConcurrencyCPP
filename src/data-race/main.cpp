#include <thread>
#include <iostream>

static int x = 0;

void inc(){
  x++;	
}

int main(){
  // error: undefined behaviour, introudce data race
  // solution: use some synchronization mechanism between threads
  std::thread t1(inc);
  std::thread t2(inc);

  t1.join();
  t2.join();
  // not guaranteed to be 2.. undefined behaviour can yield anything.
  std::cout << "X is " << x << '\n';
}
