/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			bst.cpp
 * Author(s):		Peter Bauer
 * Due Date:		May 31, 2017
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include "bst.h"
#include <stdlib.h>
#include "general.h"

Node* create_new_node(int value);



struct Node{
    int value;
    Bst left;
    Bst right;
};

Bst new_bst()
{
    return 0;

}

void delete_bst(Bst bst)
{
  if (bst == 0)
  {
    return;
  }
  delete_bst(bst->left);
  delete_bst(bst->right);
  sfree(bst);


}

/**
*** @return The depth of the BST
*/
int get_depth(Bst bst)
{
     if(bst != 0)
     {
         int leftNext = get_depth(bst->left);
         int rightNext = get_depth(bst->right);

         if(leftNext <= rightNext)
         {/* code */
           return rightNext+1;
         }
         else
         {
           return leftNext+1;
         }
     }
     else
     {
        return 0;
     }
}

/**
*** Adds a value to the BST
*/
void add(Bst* bst, int value)
{
  if ((*bst) == 0)
  {
      Node* newNode = create_new_node(value);
      (*bst) = newNode;
      return;
  }
  if (value <= (*bst)->value)
  {
    if ((*bst)->left == 0)
    {
      Node* newNode = create_new_node(value);
      (*bst)->left = newNode;
    }
    else
    {
      Node* toAdd = (*bst)->left;
      add(&toAdd, value);
    }
  }
  else
  {
    if ((*bst)->right == 0)
    {
      Node* newNode = create_new_node(value);
      (*bst)->right = newNode;
    }
    else
    {
      Node* toAdd = (*bst)->right;
      add(&toAdd, value);
    }

  }



}


Node* create_new_node(int value)
{
  Node* newNode = (struct Node*)malloc(sizeof(struct Node));
  newNode->value = value;
  newNode->right = 0;
  newNode->left = 0;
  return newNode;

}



/**
*** @return The value of the root element of the BST
*/
int root_value(Bst bst)
{
    if (bst == 0)
    {
        return 0;
    }
    else
    {
        return bst->value;
    }
}

/**
*** @return The left subtree of the BST
*/
Bst left_subtree(Bst root)
{
    if (root == 0) return 0;
    return root->left;

}

/**
*** @return The right subtree of the BST
*/
Bst right_subtree(Bst root)
{
    if (root == 0) return 0;
    return root->right;

}

/**
*** Traverses the BST depth first by first returning the root, then traversing the left
*** subtree, then traversing the right subtree.
*** @param bst The BST to be traversed
*** @param elements Array of elements in the order how they are found during traversal
*** @param start Start index of elements wherer the function should start to add the found elements
*** @return Number of elements found during traversal
*/
int traverse_pre_order(Bst bst, int *elements, int start)
{
    int temp = start;

    if(bst != 0)
    {
        elements[start] = bst->value;
        start++;
        start = traverse_pre_order(bst->left, elements, start);
        start = traverse_pre_order(bst->right, elements, start);
        return start;
    }
    else
    {
        return temp;
    }

}

/**
*** Traverses the BST depth first by first traversing the left subtree, then adding the root,
*** then traversing the right subtree.
*** @param bst The BST to be traversed
*** @param elements Array of elements in the order how they are found during traversal
*** @param start Start index of elements wherer the function should start to add the found elements
*** @return Number of elements found during traversal
*/
int traverse_in_order(Bst bst, int *elements, int start)
{
    int temp = start;

      if(bst != 0)
      {
          start = traverse_in_order(bst->left, elements, start);
          elements[start] = bst->value;
          start++;
          start = traverse_in_order(bst->right, elements, start);
          return start;
      }
      else
      {
          return temp;
      }
}

/**
*** Traverses the BST depth first by first traversing the left subtree, then traversing the right
*** subtree and finally adding the root.
*** @param bst The BST to be traversed
*** @param elements Array of elements in the order how they are found during traversal
*** @param start Start index of elements wherer the function should start to add the found elements
*** @return Number of elements found during traversal
*/
int traverse_post_order(Bst bst, int *elements, int start)
{
    int temp = start;

      if(bst != 0)
      {
          start = traverse_post_order(bst->left, elements, start);
          start = traverse_post_order(bst->right, elements, start);
          elements[start] = bst->value;
          start++;

          return start;
      }
      else
      {
          return temp;
      }
}






bool is_equal(int* depth1, int* depth2, int length)
{
  for (int i = 0; i < length+1; i++)
  {
    if (depth1[i] != depth2[i])
    {
      return false;
    }
  }
  return true;
}

/**
*** Checks whether two trees are equal
*** @param bst1 First bst
*** @param bst2 Second bst
*** @return true if bst1 and bst2 are equal, false otherwise
*/
bool are_equal(Bst bst1, Bst bst2)
{

    if (bst1 == 0 && bst1 == 0)
    {
         return true;
    }
    if (get_depth(bst1) == get_depth(bst2))
    {

      int *depth1 = new int[get_depth(bst1)];
      
      traverse_in_order(bst1,depth1, 0);
      int *depth2 = new int[get_depth(bst2)];
      traverse_in_order(bst2,depth2, 0);

      return (bst1->value == bst2->value && is_equal(depth1,depth2,get_depth(bst1)));
    }
    return false;


}





/**
*** Calculates the longest branch in the tree. If two branches are equally long
*** the left branch is taken.
*** @param bst Bst which longest branch should be found
*** @return A tree where each node has only one child equal to the longest
*** branch of bst
*/
void most_left_longest_branch(Bst bst, Bst* branch)
{
  if (bst != 0)
  {
    if (get_depth(bst->left) >= get_depth(bst->right))
    {
      add(branch, bst->value);
      most_left_longest_branch(bst->left, branch);
    }
    else
    {
      add(branch, bst->value);
      most_left_longest_branch(bst->right, branch);
    }
  }
}

/**
*** Gets the number of non-empty subtrees of a tree
*** @param bst The tree which number of subtrees to get
*** @return The number of non-empty subtrees
*/
int get_number_of_subtrees(Bst bst)
{
   if (bst != 0)
   {
     int* elements = new int [get_depth(bst)];
     return traverse_post_order(bst, elements, 0) -1;
   }
   return -1;
}
