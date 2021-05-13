#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
const int DAY = 1020; //a work day is 17 hours. 17 hours * 60 minutes is 1020 minutes in a day
float storeClock, orderTime, orderTimeSum, waitSum, waitAvg, serviceSum, serviceAvg, queueCount, queueSum, queueAvg, waitBest, serviceBest, queueBest, waitWorst, serviceWorst, queueWorst, waitBestTime, serviceBestTime, queueBestTime, waitWorstTime, serviceWorstTime, queueWorstTime;
bool emptyLine = true, singleLine = false; 

int customerCount = 0; 

class Customer
{
public:
	int order, waitTime, serviceTime; //track wait time and service time, use before customer leaves
	Customer *next;

	Customer()
	{
		order = rand() % 6 + 1; 
		waitTime = serviceTime = 0;
		next = NULL;
	}
};

class QueueLine //QueueLines follow FIFO order. elements must be added and removed from opposite sides.
{
public:
	Customer * back;

	QueueLine()
	{
		back = NULL;
	}

	//1: add to back
	void enqueue()
	{
		Customer *temp = new Customer; 
		customerCount++; 

		if (back == NULL) //if empty, our Customer becomes the new back Customer
			back = temp;
		else
		{
			temp->next = back;
			back = temp;
		} 

	}

	//2: delete from front
	void dequeue()
	{
		Customer *temp, *target;
		temp = target = back;

		if (target == NULL) //empty
		{
			return;
		}
		else if (target->next == NULL) //exactly 1 Customer
		{
			delete back;
			back = NULL;
		}
		else //more than one Customer
		{
			while (target->next != NULL)
			{
				temp = target;
				target = target->next; //temp is now the second to last Customer, and target is the last Customer
			}
			temp->next = NULL; //ground our new last Customer
			delete target; //delete target Customer
		}
	}

	//goes through the day's clock. at each minute, check if a customer will arrive.
	//then, check the status of the current customer's order. if it is done, place the next order.
	void simulateDay()
	{
		storeClock = orderTime = orderTimeSum = waitSum = waitAvg = serviceSum = serviceAvg = queueCount = queueSum = queueAvg = 0; 

		waitBest = serviceBest = queueBest = 99999; 

		waitWorst = serviceWorst = queueWorst = -1; 
		//events 1: someone walks in, 2: someone is done and walks out (both, 1, or neither can happen in any min)

		while (storeClock < DAY) //simulate a day one minute at a time
		{
			if (willCustomerArrive()) //every minute, first check if a customer will join the line
			{
				if (queueSize() == 0) //if line is empty, then someone joins, it creates a special case.
					emptyLine = true;
				else
					emptyLine = false;
					enqueue();
				if (queueSize() == 1)
					singleLine = true;
				else
					singleLine = false;
			}
			if (orderTime == 0) //if current order is done, customer can leave. place new order
			{
				if (emptyLine && singleLine) //if one person just joined the line and is the only one,
				{							//don't make them leave the queue. 
					orderTime = getOrder(); 
					customerCount++; 
					orderTimeSum += orderTime; 
					serviceSum = orderTime; 
					if(serviceBest > serviceSum) {serviceBest = serviceSum; serviceBestTime = storeClock; } 
					if(serviceWorst < serviceSum) {serviceWorst = serviceSum; serviceWorstTime = storeClock; }
					cout << "A customer has arrived in the previously empty line with order time: " << orderTime << " minutes at " << storeClock/60 << " hours" << endl; 
				}
				else
				{ 
					dequeue(); //else, this means the previous order is done and the next customer can step up
					orderTime = rand() % 6 + 1; 
					orderTimeSum += orderTime; 
					if(queueSize() > 1) {serviceSum = back->next->waitTime + orderTime; } 
					else {serviceSum = 1+orderTime; } 
					if(serviceBest > serviceSum) {serviceBest = serviceSum; serviceBestTime = storeClock; } 
					if(serviceWorst < serviceSum) {serviceWorst = serviceSum; serviceWorstTime = storeClock; } 
					cout << "Front customer has left and the following customer in line now has an order time: " << orderTime << " minutes at " << storeClock/60 << " hours" << endl; 
				}
				
			}
			storeClock++;
			if(orderTime > 0) 
				orderTime--; 
				if(queueSize() > 1) {
					back->next->waitTime++; 
					waitSum += back->next->waitTime; 
					if(waitBest > back->next->waitTime) {waitBest = back->next->waitTime; waitBestTime = storeClock; } 
					if(waitWorst < back->next->waitTime) {waitWorst = back->next->waitTime; waitWorstTime = storeClock; } 

				}

				if(queueBest > queueSize()) {
					queueBest = queueSize(); 
					queueBestTime = storeClock; 
				} 

				if(queueWorst < queueSize()) {
					queueWorst = queueSize(); 
					queueWorstTime = storeClock; 
				}

				queueSum += queueSize(); 
				queueCount++; 
		}

		waitAvg = waitSum/customerCount; 
		queueAvg = queueSum/queueCount; 
		serviceAvg = (orderTimeSum + waitSum)/customerCount; 

		cout << "Restaurant now closing" << endl; 
		cout << endl; 
		cout << "================================================" << endl;
  		cout << "|            WELCOME TO BURGER KING            |" << endl;
  		cout << "|            here are today's stats            |" << endl;
  		cout << "================================================" << endl;
  		cout << "Total customer count: [" << customerCount << "]" << endl; 
		cout << "Average wait time: [" << waitAvg << "] minutes " << endl; 
		cout << "Best wait time: [" << waitBest << "] minutes at time " << waitBestTime << endl; 
		cout << "Worst wait time: [" << waitWorst << "] minutes at time " << waitWorstTime << endl; 
		cout << "Average service time: [" << serviceAvg << "] minutes " << endl; 
		cout << "Best service time: [" << serviceBest << "] minutes at time " << serviceBestTime << endl; 
		cout << "Worst service time: [" << serviceWorst << "] minutes at time " << serviceWorstTime << endl; 
		cout << "Average queue size: [" << queueAvg << "]" << endl; 
		cout << "Smallest queue length: [" << queueBest << "] at time " << queueBestTime << endl; 
		cout << "Largest queue length: [" << queueWorst << "] at time " << queueWorstTime << endl; 
		cout << "================================================" << endl; 
		cout << endl; 
	}

	//determine if a customer will arrive at the given minute
	bool willCustomerArrive()
	{
		int prob = rand() % 100;
		if (storeClock < 120) //8:00 to 10:00
		{
			if (prob <= 30)
				return true;
		}
		else if (storeClock < 210) //10:00 to 11:30
		{
			if (prob <= 10)
				return true;
		}
		else if (storeClock < 330) //11:30 to 1:30
		{
			if (prob <= 40)
				return true;
		}
		else if (storeClock < 570) //1:30 to 5:30
		{
			if (prob <= 10)
				return true;
		}
		else if (storeClock < 720) //5:30 to 8:00
		{
			if (prob <= 25)
				return true;
		}
		else if (storeClock < 900) //8:00 to 11:00
		{
			if (prob <= 20)
				return true;
		}
		else if (storeClock < DAY) //11:00 to 1:00 (close) 
		{
			if (prob <= 10)
				return true;
		}
		return false;
	}

	int getOrder()
	{
		Customer *traverse = back;
		if (traverse == NULL)
			return 0;
		while (traverse->next != NULL)
		{
			traverse = traverse->next;
		}
		return traverse->order;
	}

	int queueSize()
	{
		int queueLength = 0;
		Customer *traverse = back;
		while (traverse != NULL)
		{
			traverse = traverse->next;
			queueLength++;
		}
		return queueLength;
	}

};

int main()
{
	srand(time(NULL));
	QueueLine myStore;
	myStore.simulateDay(); 
    return 0;
}
