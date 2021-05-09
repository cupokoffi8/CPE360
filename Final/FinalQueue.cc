#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

float storeClock = 0;

class Customer
{
public:
  float inTime;
  int outTime;
  int waitTime;
  int orderTime;
  Customer *next;

  Customer()
  {
    inTime = storeClock;
    outTime = 0;
    waitTime = rand() % 6 + 1;
    orderTime = 0;
    next = NULL;
  }
};

class Queue
{
public:
  Customer *head;
  float wait_time_sum;
  int service_time_sum;
  int min_wait_time;
  int max_wait_time;
  int min_service_time;
  int max_service_time;
  int serviceWaitTime; 

  Queue()
  {
    head = NULL;
    wait_time_sum = 0;
    service_time_sum = 0;
    min_wait_time = 99999;
    max_wait_time = -1;
    min_service_time = 99999;
    max_service_time = -1; 
    int serviceWaitTime = 0; 
  }

  void enqueue()
  {
    Customer *temp = new Customer();
    cout << "New customer at " << storeClock / 60 << " hours and wait time " << temp->waitTime << " minutes " << endl;
    serviceWaitTime = temp->waitTime; 
    wait_time_sum += temp->waitTime; 
    if(min_wait_time > temp->waitTime) {
      min_wait_time = temp->waitTime; 
    } else if(max_wait_time < temp->waitTime) {
      max_wait_time = temp->waitTime; 
    }

    if (head == NULL)
    {
      head = temp;
    }
    else
    {
      Customer *another;
      another = head; //start at the beginning
      while (another->next != NULL)
      {
        another = another->next;
      }
      //When we are at the end, we want to make this new chunk (temp) the last one
      another->next = temp;
      temp->next = NULL;
    }
  }

  void dequeue()
  {
    if (head == NULL)
    {
      cout << "Empty queue, nothing to delete" << endl;
    }
    else
    {
      Customer *temp;
      temp = head;       //grab the address of the first chunk
      head = head->next; //head moves to the next chunk
      cout << "At hour " << storeClock / 60 << " order has been placed" << endl;
      delete temp;
    }
  }

  int queueSize()
  {
    return 1;
  }
};

int main()
{

  Queue myStore;
  srand(time(NULL));

  float customerCount = 0;
  int queue_length = 0; 
  int random_number;

  while (storeClock < 1020)
  {
    storeClock++;

    //Are we in the time [8-10 a.m.]
    if (storeClock <= 120)
    {
      //Let's see if a new customer arrives now
      random_number = rand() % 100 + 1;
      if (random_number <= 30)
      {
        //New customer arrival
        customerCount++;
        myStore.enqueue();
      }
      else
      {
//No new customer
#if 0
        cout << "No new customer at hour " << storeClock / 60 << endl;
#endif
      }
    }

    else if (storeClock > 120 && storeClock <= 210)
    {
      //Brunch time
      //Let's see if a new customer arrives now
      random_number = rand() % 100 + 1;
      if (random_number <= 10)
      {
        //New customer arrival
        customerCount++;
        myStore.enqueue();
      }
      else
      {
//No new customer
#if 0
        cout << "No new customer at hour " << storeClock / 60 << endl;
#endif
      }
    }

    else if (storeClock > 210 && storeClock <= 330)
    {
      //Lunch time
      //Let's see if a new customer arrives now
      random_number = rand() % 100 + 1;
      if (random_number <= 40)
      {
        //New customer arrival
        customerCount++;
        myStore.enqueue();
      }
      else
      {
//No new customer
#if 0
        cout << "No new customer at hour " << storeClock / 60 << endl;
#endif
      }
    }

    else if (storeClock > 330 && storeClock <= 570)
    {
      //Afternoon snacks
      //Let's see if a new customer arrives now
      random_number = rand() % 100 + 1;
      if (random_number <= 10)
      {
        //New customer arrival
        customerCount++;
        myStore.enqueue();
      }
      else
      {
//No new customer
#if 0
        cout << "No new customer at hour " << storeClock / 60 << endl;
#endif
      }
    }

    else if (storeClock > 570 && storeClock <= 720)
    {
      //Dinner time
      //Let's see if a new customer arrives now
      random_number = rand() % 100 + 1;
      if (random_number <= 25)
      {
        //New customer arrival
        customerCount++;
        myStore.enqueue();
      }
      else
      {
//No new customer
#if 0
        cout << "No new customer at hour " << storeClock / 60 << endl;
#endif
      }
    }

    else if (storeClock > 720 && storeClock <= 900)
    {
      //Late night
      //Let's see if a new customer arrives now
      random_number = rand() % 100 + 1;
      if (random_number <= 20)
      {
        //New customer arrival
        customerCount++;
        myStore.enqueue();
      }
      else
      {
//No new customer
#if 0
        cout << "No new customer at hour " << storeClock / 60 << endl;
#endif
      }
    }

    else
    {
      //Midnight snack
      //Let's see if a new customer arrives now
      random_number = rand() % 100 + 1;
      if (random_number <= 10)
      {
        //New customer arrival
        customerCount++;
        myStore.enqueue();
      }
      else
      {
//No new customer
#if 0
        cout << "No new customer at hour " << storeClock / 60 << endl;
#endif
      }
    }

    //2. Is a new customer done with an order this minute?
    if (myStore.head != NULL)
    {
      if (myStore.head->waitTime == 1)
      {
        myStore.head->orderTime = rand() % 6 + 1; 
        cout << "with order prep time " << myStore.head->orderTime << " minutes" << endl; 
        myStore.service_time_sum+=myStore.head->orderTime; 
        if(myStore.min_service_time > myStore.head->orderTime+myStore.serviceWaitTime) {
          myStore.min_service_time = myStore.head->orderTime+myStore.serviceWaitTime; 
        } else if(myStore.max_service_time < myStore.head->orderTime+myStore.serviceWaitTime) {
          myStore.max_service_time = myStore.head->orderTime+myStore.serviceWaitTime; 
        }
        storeClock+=myStore.head->orderTime; 
        myStore.dequeue();
          }
      else
      {
        myStore.head->waitTime--;
      }
    }

    //3. Let's check on our vital stats real quick: wait time, service time and queue length
  }

  float mean_wait_time; 
  float mean_service_time; 
  mean_wait_time = myStore.wait_time_sum/customerCount; 
  mean_service_time = (myStore.service_time_sum+myStore.wait_time_sum)/customerCount; 

  cout << endl; 
  cout << "==========================================" << endl; 
  cout << "Total wait time: " << myStore.wait_time_sum << endl; 
  cout << "Total service time: " << myStore.service_time_sum << endl; 
  cout << "Total customer count: " << customerCount << endl; 
  cout << "Average wait time: " << mean_wait_time << " minutes" << endl; 
  cout << "Average service time: " << mean_service_time << " minutes" << endl; 
  cout << "Minimum wait time: " << myStore.min_wait_time << " minutes" << endl; 
  cout << "Maximum wait time: " << myStore.max_wait_time << " minutes" << endl; 
  cout << "Minimum service time: " << myStore.min_service_time << " minutes" << endl; 
  cout << "Maximum service time: " << myStore.max_service_time << " minutes" << endl; 
  cout << "==========================================" << endl; 
  cout << endl; 
}
