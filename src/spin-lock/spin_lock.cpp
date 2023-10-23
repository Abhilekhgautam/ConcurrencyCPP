#include <thread>
#include <atomic>
#include <ranges>
#include <iostream>

/*

   SpinLock -> special lock, if unable to get a lock when desired repeatedely checks 
   for its availability.

*/

/*

   Could've implemented using atomic_flag
   but the challange was to use an atomic_bool :)

*/

class SpinLock{
  public:
    SpinLock(){
      is_locked = false;
    }	  
    void lock(){
      bool expected = false;
      // wasting CPU Cycle here..
      // No Guarantee for non-preemption
      while(!is_locked.compare_exchange_weak(expected, true)){
	 expected = false;     
      }
    }

    void unlock(){
      is_locked = false;
    }
  private:
    std::atomic_bool is_locked;
};



int main(){

 int x = 0;
 SpinLock my_lock;
 std::thread t1([&]() mutable{
    for(int i : std::views::iota(1,1000)){
     my_lock.lock();
     x++;
     my_lock.unlock();
    } 		 
 });

 std::thread t2([&]() mutable{
     for(int i : std::views::iota(1,1000)){
     my_lock.lock();
     x++;
     my_lock.unlock();
    } 		 
  });

 std::thread t3([&](){
  while(true){
    my_lock.lock();
    std::cout << x << " ";
    my_lock.unlock();
   }
  });

 t1.join();
 t2.join();
 t3.join();
}
