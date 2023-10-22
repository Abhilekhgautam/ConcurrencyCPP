#include <thread>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <ranges>
#include <iostream>

std::mutex m;
std::deque<int> d;
std::condition_variable is_non_empty;

void produce_and_insert(){
  for(int i : std::views::iota(1,1000)){
    std::unique_lock<std::mutex> lock(m);
    std::cout << "Pushing value: " << i << '\n';
    d.push_back(i);
   // notify that one waiting thread...
   is_non_empty.notify_one();
  }
}

void consume_and_remove(){
 for(int i : std::views::iota(1,1000)){
   std::unique_lock<std::mutex> lock(m);
   //wait if queue is empty
   is_non_empty.wait(lock, [] (){return !d.empty();});
   // just for printing purpose
   auto val = d.front();
   std::cout << "Popping Value: " <<  val << "\n";
   //consume
   d.pop_front();
 }
}

int main(){
  std::thread producer(produce_and_insert);
  std::thread consumer(consume_and_remove);

  producer.join();
  consumer.join();
}
