#include <iostream>
#include <stdlib.h> 
using namespace std;

class TreeNode {
public:
  int data;
  TreeNode *left;
  TreeNode *right;

  TreeNode() {
    data = 0;
    left = NULL;
    right = NULL;
  }
};

//BST of such treenodes
class BST {
public:
  TreeNode *root;

  BST() {
    root = NULL;
  }

  //1. Add nodes to the BST
  void addNode(int value) {

    TreeNode *temp = new TreeNode;
    temp->data = value;

    //if tree is empty, make the first value the "root" node
    if(root == NULL) {
      root = temp;
    }
    else {
      TreeNode *slow, *fast;
      slow = fast = root; //start at the top

      while(fast != NULL) {
	if(fast->data == value) {
	  cout << "Duplicate value, we will not add to the tree" << endl;
	  return; 
	}
	if(value < fast->data) {
	  slow = fast;
	  fast = fast ->left;
	}
	else {
	  slow = fast;
	  fast = fast->right;
	}
	
      }
      //Fast has now fallen off the tree
      //We will use "slow" (parent of the tree) to add a new value
      if(value < slow->data) {
	slow->left = temp;
      }
      else {
	slow->right = temp;
      }
      
    }
    cout << "Just added: " << value << " to the BST!" << endl; 
  }
  
  //2. Search for a value (primary objective)
  void search(int key, TreeNode *start) {
    if(start == NULL) {
      cout << "Could not find: " << key << endl;
      return;
    }
    else {
      if(key == start->data) {
	cout << "FOUND IT!!" << endl;
	return;
      }
      else if(key < start->data) {
	search(key, start->left);
      }
      else {
	search(key, start->right);
      }
    }
  }
  
  //3. Delete a value from the BST
  void deleteNode(int value, TreeNode *start) {

    TreeNode *fast; 
    TreeNode *slow; 

    if(start == NULL) {
      cout << "Empty tree, nothing to delete." << endl;
      return;
    }

    slow = fast = start;

    while(fast != NULL && fast->data != value) {
      if(value < fast->data) {
	slow = fast;
	fast = fast->left;
      }
      else {
	slow = fast;
	fast = fast->right;
      }
    }

    if(fast == NULL) {
      cout << "Value not found, cannot delete." << endl;
      return;
    }
    
    //Case 1: Node has no children
    if(fast->left == NULL && fast->right == NULL) {
      if(slow->left == fast) {
	slow->left = NULL;
	cout << "About to delete: " << fast->data << endl; 
	delete fast; 
      }
      else {
	slow->right = NULL;
	cout << "About to delete: " << fast->data << endl; 
	delete fast;
      }
    }
    
    //Case 2: Node has one child
    else if(fast->left != NULL && fast->right == NULL) {
      if(slow->left == fast) {
	slow->left = fast->left;
	cout << "About to delete: " << fast->data << endl; 
	delete fast; 
      }
      else {
	slow->right = fast->left;
	cout << "About to delete: " << fast->data << endl; 
	delete fast;
      }
    }

    else if(fast->left == NULL && fast->right != NULL) {
      if(slow->right == fast) {
	slow->right = fast->left;
	cout << "About to delete: " << fast->data << endl; 
	delete fast; 
      }
      else {
	slow->left = fast->left;
	cout << "About to delete: " << fast->data << endl; 
	delete fast;
      }
    } 
    else {
      
      int minVal = minValueRightSubtree(fast->right); 
      //Swap the current node with minval 
      fast->data = minVal; 
      //We need to delete that minVal from the right subtree right away! 
      deleteNode(minVal, fast->right); 
    }
     //Case 3: Node has two children 
  }
    
  int minValueRightSubtree(TreeNode *start) {
    if(start == NULL) {
      return -1; 
    } 
    else {
      TreeNode *temp = start; 
      while(temp->left != NULL) {
	temp = temp->left; 
      }
      return temp->data; 
    }
  } 
    
  //4. Function(s) to display
  //4.1 preorder
  void preorder(TreeNode *start) {
    if(start == NULL) {
      //base case or anchor value
      return; 
    }
    else {
      //recursive step
      //ROOT
      cout << "^" << start->data;
      //LEFT
      preorder(start->left);
      //RIGHT
      preorder(start->right); 
    }
    
  }

  void postorder(TreeNode *start) {
    if(start == NULL) {
      return;
    }
    else {
      //LEFT
      postorder(start->left);
      //RIGHT
      postorder(start->right);
      //ROOT
      cout << start->data << "^";
    }

  }

  void inorder(TreeNode *start) {
    if(start == NULL) {
      return;
    }
    else {
      //LEFT
      inorder(start->left);
      //ROOT
      cout << "^" << start->data;
      //RIGHT
      inorder(start->right);
    }
    
  }

}; 

int main() {

  BST myTree;
  int choice, value;

  while(1) {
    cout << "Press 1 to add a value" << endl;
    cout << "Press 2 to pre-order" << endl;
    cout << "Press 3 to post-order" << endl;
    cout << "Press 4 to in-order" << endl;
    cout << "Press 5 to search" << endl;
    cout << "Press 6 to delete" << endl; 
    cout << "Anything else to quit" << endl; 
    cin >> choice;

    switch(choice) {
    case 1:
      cout << "What value?" << endl;
      cin >> value;
      myTree.addNode(value);
      break;

    case 2:
      cout << "========================" << endl;
      myTree.preorder(myTree.root);
      cout << endl << "========================" << endl;
      break;

    case 3:
      cout << "========================" << endl;
      myTree.postorder(myTree.root);
      cout << endl << "========================" << endl;
      break;

    case 4:
      cout << "========================" << endl;
      myTree.inorder(myTree.root);
      cout << endl << "========================" << endl;
      break;

    case 5:
      cout << "What value?" << endl;
      cin >> value;
      myTree.search(value, myTree.root);
      break;

    case 6:
      cout << "What value?" << endl;
      cin >> value;
      myTree.deleteNode(value, myTree.root);
      break; 

    default :
      exit(1);
    }
  }
}
