#include <iostream>
#include <thread>


class BackgroundTask{
 public:
    void operator() (){
      std::cout << "I am callable\n";	    
    }
};
// To run multiple threads on a C++ program just create a std::thread object
int main(){
 	
  BackgroundTask t;	
  // t is a callable object so can be passed to the thread
  // t is copied not moved
  std::thread my_thread(t);
  std::thread my_another_thread(t);
  std::thread my_yet_another_thread(t);

  // the original t can be deleted(if possible) because we are passing the copy
  // but we must be careful while deleting if the object contains any pointer or a reference..

  // join all the threads 
  my_thread.join();
  my_another_thread.join();
  my_yet_another_thread.join();
}
