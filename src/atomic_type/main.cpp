#include <iostream>
#include <thread>
#include <atomic>

/*

Note: Every Atomic operation have a optional std::memory_order argument which defaults to std::memory_order_seq-cst

*/

int main(){

  // the most basic atomic type is std::atomic_flag
  // must always be initialized to ATOMIC_FLAG_INIT, no other options
  std::atomic_flag my_flag = ATOMIC_FLAG_INIT;
  // test_and_set: sets the flag and returns the previous value
  auto val = my_flag.test_and_set();

  // I want boolean output
  std::cout << std::boolalpha;
  // test() was introduced lately in C++20, atomically returns the current value.
  std::cout << "The flag was initially " << val << " and it is now set to " << my_flag.test() << '\n' ;

  // sets to false again.
  my_flag.clear();
	
  // not allowed in atomic type, assignment operator is deleted
  // std::atomic_bool is a typedef of std::atomic<bool>.
  //std::atomic_bool f = true;

  std::atomic_bool f(true);

  // loads a value to the variable 
  bool new_val = f.load();

  std::cout << new_val << '\n';
  //stores non-atomic value to atomic variable
  f.store(false);
  // f is now false
  std::cout << f << '\n';
  /*
    exchange: read-modify-write, takes in a desired value, replace the value with the desired one and 
              returns previous value
  */
  bool some_val = f.exchange(true);
  // f is now true but some_val is false because f was false previously.
  std::cout << "some_val is " << some_val << '\n';
  std::cout << "f is " << f;

  /*
   
    compare_exchange_weak(expected, desired, memory_order success, memory_order failure): 
                 Compares the value with expected, if equal sets to desired otherwise loads the current value to expected.
   
  */

   //auto v = f.compare_exchange_weak(true, false,std::memory_order_relaxed, std::memory_order_relaxed);
}
