#include <iostream>
#include <thread>

// will run on say_hello_thread
void say_hello(){
  std::cout << "Hello, World\n";	
}

int main(){
  
  //create a new thread
  std::thread say_hello_thread(say_hello);
  // wait for thread to finish execution
  // surprisingly you get some runtime error(not compilation for sure) for not joining the threads.
  say_hello_thread.join();
  std::cout << "Hello, World\n";	
}
