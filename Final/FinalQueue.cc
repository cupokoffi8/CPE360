#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int storeClock = 0; 

class Customer{
public:
  int inTime;
  int outTime;
  int waitTime;
  int orderTime;
  Customer *next;
  
  Customer() {
    inTime = storeClock;
    outTime = 0;
    waitTime = 0;
    orderTime = rad()%6 + 1;
    next = NULL;
  }
}; 

class Queue {
public:
  Customer *head;

  Queue() {
    head = NULL;
  }

  void enqueue() {
    Customer *temp = new Customer(); 
  }

  void dequeue() {

  }

  int queueSize() {
    return 1;
  }
}; 

int main() {

    Queue myStore; 
    srand(time(NULL));

    int customerCount = 0;
    int queue_length = 0;
    int wait_time_sum = 0;
    int service_time_sum = 0;
    int min_wait_time = 99999;
    int max_wait_time = -1;
    int min_service_time = 99999;
    int max_service_time = -1;
    int random_number;

    while(storeClock < 1020) {
      storeClock++;

      //Are we in the time [8-10 a.m.]
      if(storeClock <= 120) {
	//Let's see if a new customer arrives now
	random_number = rand()%100 + 1;
	if(random_number <= 30) {
	  //New customer arrival
	  cout << "New customer at time " << storeClock << endl;
	  customerCount++;
	  myStore.enqueue();
	}
	else {
	  //No new customer 
	}
      }

      else if(storeClock > 120 && storeClock <= 210) {
	//Brunch time 
      }

      //2. Is a new customer done with an order this minute?
      if(myStore.head != NULL) {
	if(myStore.head->orderTime == 0) {
	  cout << "Customer departing" << endl;
	}
	else {
	  myStore.head->orderTime--;
	}
      }

      //3. Let's check on our vital stats real quick: wait time, service time and queue length 

}
