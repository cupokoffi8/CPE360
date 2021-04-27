#include <iostream>
#include <iterator> 
using namespace std;

class Tab {
public:
  int length;
  int width;
  Tab *next; 

  Tab() {

    length = 100;
    width = 50;
    next = NULL; 

  }

  void openLink() {

    cout << "Opened link" << endl; 

  }


};

int main() {

  //=============================================================================
  //             A P P    S P A C E
  //=============================================================================
  
  int x;
  Tab myTab;

  myTab.length = 200;
  myTab.width = 100;

  //=============================================================================
  //             H  E  A  P
  //=============================================================================

  Tab *ptr;

  ptr = new Tab; //one tab

  ptr->length = 200;
  ptr->width = 100;

  //second tab
  ptr->next = new Tab;

  //third tab
  ptr->next->next = new Tab;

  //fourth tab
  ptr->next->next->next = new Tab;

  //fifth tab
  ptr->next->next->next->next = new Tab; 

  //deleting first tab (deleting a chunk from the front) 
  Tab *another;

  another = ptr;
  ptr = ptr->next;
  delete another;
  another = NULL; 

  //adding a new chunk to position 3 (replacing new chunk made by another, and adding it to the ptr chain) 
  another = new Tab;
  another->next = ptr->next->next;
  ptr->next->next = another;
  another = NULL;

  //deleting chunk from position 3
  another = ptr->next->next;
  ptr->next->next = ptr->next->next->next;
  delete another;
  another = NULL;

  //Deleting a chunk from the end
  another = ptr->next->next->next->next;
  ptr->next->next->next->next = NULL;
  delete another; 
  
}
