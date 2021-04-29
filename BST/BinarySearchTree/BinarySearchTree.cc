#include <iostream>
#include <stdlib.h>
using namespace std;

class TreeNode
{
public:
  int value;
  TreeNode *right;
  TreeNode *left;

  TreeNode() : value(0), right(NULL), left(NULL) {}
};

class BST
{
public:
  TreeNode *root;

  BST() : root(NULL) {}

  void search(int key, TreeNode *start)
  {
    if (start == NULL)
    {
      cout << "Could not find " << key << endl;
    }
    else if (key == start->value)
    {
      cout << "Found " << key << " in the BST" << endl;
      return;
    }
    else
    {
      if (key > start->value)
      {
        search(key, start->right);
      }
      else
      {
        search(key, start->left);
      }
    }
  }

  void addNode(int key)
  {
    if (root == NULL)
    {
      root = new TreeNode;
      root->value = key;
      return;
    }
    else
    {
      TreeNode *slow, *fast;
      slow = fast = root;
      while (fast != NULL)
      {
        if (fast->value == key)
        {
          cout << "Duplicate value, not added" << endl;
        }
        else
        {
          if (key > fast->value)
          {
            slow = fast;
            fast = fast->right;
          }
          else
          {
            slow = fast;
            fast = fast->left;
          }
        }
      }
      TreeNode *temp = new TreeNode;
      temp->value = key;
      if (key < slow->value)
      {
        slow->left = temp;
      }
      else
      {
        slow->right = temp;
      }
    }
  }

  void deleteNode(int key, TreeNode *start)
  {
    bool found = false;
    if (start->value == NULL)
    {
      cout << "Tree is empty";
    }
    else
    {
      TreeNode *fast, *slow;
      fast = slow = start;

      while (fast != NULL || fast->value != key)
      {
        if (fast->value == key)
        {
          found = true;
          break;
        }
        else
        {
          if (key > fast->value)
          {
            slow = fast;
            fast = fast->right;
          }
          else
          {
            slow = fast;
            fast = fast->left;
          }
        }
      }
      if (fast == NULL)
      {
        cout << "Value not found in tree" << endl;
        return;
      }
      else
      {
        //Case 1. has no children
        if (fast->left == NULL && fast->right == NULL)
        {
          if (slow->left == fast)
          {
            delete fast;
            slow->left = NULL;
          }
          else
          {
            delete fast;
            slow->right = NULL;
          }
        }
        //Case 2. has one child
        else if (fast->left == NULL || fast->right == NULL)
        {
          if (slow->right == fast)
          {
            if (fast->left == NULL)
            {
              slow->right = fast->right;
            }
            else
            {
              slow->right = fast->left;
            }
          }
          else
          {
            if (fast->left == NULL)
            {
              slow->left = fast->right;
            }
            else
            {
              slow->left = fast->left;
            }
          }
        }
        //Case 3. has two children
        else
        {
          int minVal = minValRSubTree(fast->right);
          deleteNode(minVal, fast);
          fast->value = minVal;
        }
      }
    }
  }

  int minValRSubTree(TreeNode *start)
  {
    TreeNode *temp = start;
    while (temp->left != NULL)
    {
      temp = temp->left;
    }
    return temp->value;
  }

  void inorder(TreeNode *start)
  {
    if (start == NULL)
    {
      return;
    }
    else
    {
      inorder(start->left);
      cout << "[" << start->value << "]";
      inorder(start->right);
    }
  }

  void preorder(TreeNode *start)
  {
    if (start == NULL)
    {
      return;
    }
    else
    {
      cout << "[" << start->value << "]";
      preorder(start->left);
      preorder(start->right);
    }
  }

  void postorder(TreeNode *start)
  {
    if (start == NULL)
    {
      return;
    }
    else
    {
      inorder(start->left);
      inorder(start->right);
      cout << "[" << start->value << "]";
    }
  }
};

int main()
{
  BST myTree;
  int choice, value;
  value = choice = 0;
  while (choice < 7)
  {
    cout << endl;
    cout << "==================================" << endl;
    cout << "Press 1 to add a number to the BST" << endl;
    cout << "Press 2 to search for a number" << endl;
    cout << "Press 3 to delete a number" << endl;
    cout << "Press 4 for in-order display" << endl;
    cout << "Press 5 for pre-order display" << endl;
    cout << "Press 6 for post-order display" << endl;
    cout << "Press any other button to quit" << endl;
    cout << "==================================" << endl;
    cin >> choice;

    switch (choice)
    {
    case 1:
      cout << "Add what?" << endl;
      cin >> value;
      myTree.addNode(value);
      cout << "Added " << value << endl;
      break;
    case 2:
      cout << "What number are you looking for?" << endl;
      cin >> value;
      myTree.search(value, myTree.root);
      break;
    case 3:
      cout << "Delete what?" << endl;
      cin >> value;
      myTree.deleteNode(value, myTree.root);
      break;
    case 4:
      myTree.inorder(myTree.root);
      break;
    case 5:
      myTree.preorder(myTree.root);
      break;
    case 6:
      myTree.postorder(myTree.root);
      break;
    default:
      return 0;
    }
  }

  return 0;
}