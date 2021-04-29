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
    waitTime = 0;
    orderTime = rand() % 6 + 1;
    next = NULL;
  }
};

class Queue
{
public:
  Customer *head;

  Queue()
  {
    head = NULL;
  }

  void enqueue()
  {
    Customer *temp = new Customer();
    cout << "New customer at " << storeClock / 60 << " hours and order time " << temp->orderTime << " minutes " << endl;

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
      cout << "At hour " << storeClock / 60 << " we have a departing customer" << endl;
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

  int customerCount = 0;
  int queue_length = 0;
  int wait_time_sum = 0;
  int service_time_sum = 0;
  int min_wait_time = 99999;
  int max_wait_time = -1;
  int min_service_time = 99999;
  int max_service_time = -1;
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
        cout << "New customer at hour " << storeClock / 60 << endl;
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
        cout << "New customer at hour " << storeClock / 60 << endl;
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
        cout << "New customer at hour " << storeClock / 60 << endl;
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
        cout << "New customer at hour " << storeClock / 60 << endl;
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
        cout << "New customer at hour " << storeClock / 60 << endl;
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
        cout << "New customer at hour " << storeClock / 60 << endl;
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
        cout << "New customer at hour " << storeClock / 60 << endl;
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
      if (myStore.head->orderTime == 0)
      {
        cout << "Customer departing" << endl;
      }
      else
      {
        myStore.head->orderTime--;
      }
    }

    //3. Let's check on our vital stats real quick: wait time, service time and queue length
  }
}
