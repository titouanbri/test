#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>
#include <vector>
#include <string>

using namespace std;
int N = 5;
mutex chopsticks; //Semaphores
mutex controldeck;
vector <string> state_philo(N);
void take_chopstick(int i) {
  chopsticks.lock(); // left chopstick
  controldeck.lock();
  std::cout<< "Philospher " << (i+1) << " is taking left chopstick"<<std::endl;
    controldeck.unlock();

    controldeck.lock();

  std::cout<< "Philosopher " << (i+1) << " is taking right chopstick"<<std::endl;
    controldeck.unlock();

  this_thread::sleep_for(chrono::milliseconds(2000));

}

void leave_chopstick(int i) {

    controldeck.lock();

  std::cout<< "Philosopher " << (i+1) << " is leaving left chopstick"<<std::endl;
    controldeck.unlock();

  chopsticks.unlock(); // right chopstick
    controldeck.lock();

  std::cout<< "Philosopher " << (i+1) << " is leaving right chopstick"<<std::endl;
    controldeck.unlock();

  this_thread::sleep_for(chrono::milliseconds(2000));
}
void think(int i){
  controldeck.lock();

    std::cout<< "Philosopher " << (i+1) << " is thinking"<<std::endl;
      controldeck.unlock();

    this_thread::sleep_for(chrono::milliseconds(2000));

}
void eat(int i){
  controldeck.lock();

    std::cout<< "Philosopher " << (i+1) << " is eating"<<std::endl;    this_thread::sleep_for(chrono::milliseconds(1000));
      controldeck.unlock();

}

void philosopher(int i)
{
    while(1){
        think(i);
        take_chopstick(i);
        eat(i);
        leave_chopstick(i);

    }

}

bool test(int i){
    if (philo[(i-1)%N].try_acquire() && philo[(i+1)%N].try_acquire()){
    return true;

    }
    else{return false;}

}

int main()
{
	thread p1(philosopher, 0);
	thread p2(philosopher, 1);
    thread p3(philosopher, 2);
	thread p4(philosopher, 3);
    thread p5(philosopher, 4);
	p1.join();
	p2.join();
    p3.join();
	p4.join();
    p5.join();
	return 0;
}
