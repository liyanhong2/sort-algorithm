/*************************************************************************
	> File Name: RBTree_insert.cpp
	> Author: 
	> Mail: 
	> Created Time: 六  5/ 7 18:37:13 2016
 ************************************************************************/

#include<iostream>
using namespace std;
// C++程序：实现红黑树的插入操作
#include <iostream>
//红黑树节点
struct Node
{
  int data; //节点数据
  char color;  //颜色属性
  //左孩子，右孩子以及父节点指针
  Node *left, *right, *parent;
};
//左旋
/*
  y                        x
   / \   Right Rotation   /  \
  x   T3   – – – – – – – >  T1   y
 / \       < - - - - - - -      / \
T1  T2   Left Rotation       T2  T3
*/
void LeftRotate(Node **root, Node *x)
{
  //y保存x的右孩子
  Node *y = x->right;
  //将y的左孩子做为x的右孩子
  x->right = y->left;
  //更新x的右孩子的父指针
  if (x->right != NULL)
    x->right->parent = x;
  //更新y的父指针
  y->parent = x->parent;
  //如果x的父节点为null，则y成为新的根节点
  if (x->parent == NULL)
    (*root) = y;
  //将y保存在x的原始位置
  else if (x == x->parent->left)
    x->parent->left = y;
  else  
    x->parent->right = y;
  //将x做为y的左孩子
  y->left = x;
  //更新x的父节点为y
  x->parent = y;
}
//右旋(与左旋正好相反)
/*
  y                        x
   / \   Right Rotation   /  \
  x   T3   – – – – – – – >  T1   y
 / \       < - - - - - - -      / \
T1  T2   Left Rotation       T2  T3
*/
void rightRotate(Node **root, Node *y)
{
  //x保存y的右孩子
  Node *x = y->left;
  //将x的右孩子做为y的左孩子
  y->left = x->right;
  //更新x的右孩子的父指针
  if (x->right != NULL)
    x->right->parent = y;
  //更新x的父指针
  x->parent = y->parent;
  //如果x的父节点为null，则x成为新的根节点
  if (x->parent == NULL)
    (*root) = x;
  //将x保存在y的原始位置
  else if (y == y->parent->left)
    y->parent->left = x;
  else
    y->parent->right = x;
  //将y做为x的右孩子
  x->right = y;
  //更新y的父节点为x
  y->parent = x;
}
//功能函数，在执行标准的BST插入后，调整红黑树。
void insertFixUp(Node **root, Node *z)
{
  //遍历树，直到z不是根节点，并且z的父节点是红色[对应情形3]
  while (z != *root && z->parent->color == 'R')
  {
    Node *y;
    //找到叔节点，保存为y
    if (z->parent == z->parent->parent->left)
      y = z->parent->parent->right;
    else
      y = z->parent->parent->left;
    //如果叔节点为红色，执行下面操作。[对应情形3.1]
    //(a) 将父节点以及叔节点置为黑色
    //(b) 将祖父节点置为红色
    //(c) 将祖父节点赋值给z,继续检测
    if (y->color == 'R')
    {
      y->color = 'B';
      z->parent->color = 'B';
      z->parent->parent->color = 'R';
      z = z->parent->parent;
    }
    //如果叔节点是黑色，则存在4种情形，LL,LR,RL,RR。 [对应情形3.2]
    else
    {
      //Left-Left (LL) case
      //(a) 交换父节点与祖父节点的颜色
      //(b) 祖父节点进行右旋
      if (z->parent == z->parent->parent->left &&
        z == z->parent->left)
      {
        char ch = z->parent->color;
        z->parent->color = z->parent->parent->color;
        z->parent->parent->color = ch;
        rightRotate(root, z->parent->parent);
      }
      //Left-Right (LR) case
      //(a) 交换当前节点与祖父节点的颜色
      //(b) 父节点进行左旋
      //(c) 祖父节点进行右旋
      if (z->parent == z->parent->parent->left &&
        z == z->parent->right)
      {
        char ch = z->color;
        z->color = z->parent->parent->color;
        z->parent->parent->color = ch;
        LeftRotate(root, z->parent);
        rightRotate(root, z->parent->parent);
      }
      //Right-Right (RR) case
      //(a) 交换父节点与祖父节点的颜色
      //(b) 祖父节点进行左旋
      if (z->parent == z->parent->parent->right &&
        z == z->parent->right)
      {
        char ch = z->parent->color;
        z->parent->color = z->parent->parent->color;
        z->parent->parent->color = ch;
        LeftRotate(root, z->parent->parent);
      }
      //Right-Left (RL) case
      //(a) 交换当前节点与祖父节点的颜色
      //(b) 父节点进行右旋
      //(c) 祖父节点进行左旋
      if (z->parent == z->parent->parent->right &&
        z == z->parent->left)
      {
        char ch = z->color;
        z->color = z->parent->parent->color;
        z->parent->parent->color = ch;
        rightRotate(root, z->parent);
        LeftRotate(root, z->parent->parent);
      }
    }
  }
  (*root)->color = 'B'; //根节点总是黑色
}
//功能函数：插入新节点至红黑树
void insert(Node **root, int data)
{
  //分配新节点内存
  Node *z = new Node;
  z->data = data;
  z->left = z->right = z->parent = NULL;
  //如果根节点为null,则z成为根节点
  if (*root == NULL)
  {
    z->color = 'B';  //根节点总是黑色
    (*root) = z;
  }
  else
  {
    Node *y = NULL;
    Node *x = (*root);
    // Follow standard BST insert steps to first insert the node
    while (x != NULL)
    {
      y = x;
      if (z->data < x->data)
        x = x->left;
      else
        x = x->right;
    }
    z->parent = y;
    if (z->data > y->data)
      y->right = z;
    else
      y->left = z;
    z->color = 'R';   //新插入节点总是红色
    // 调用insertFixUp来修复红黑树的属性，因为它可能因为插入操作而被破坏。
    insertFixUp(root, z);
  }
}
//功能函数：中序遍历红黑树
void inorder(Node *root)
{
  if (root == NULL)
    return;
  inorder(root->left);
  std::cout << root->data << "-->";
  inorder(root->right);
}
int main()
{
  Node *root = NULL;
  insert(&root, 5);
  insert(&root, 3);
  insert(&root, 7);
  insert(&root, 2);
  insert(&root, 4);
  insert(&root, 6);
  insert(&root, 8);
  insert(&root, 11);
  std::cout<<"Inorder Traversal Is: \n";
  inorder(root);
  std::cout << "null"<<std::endl;
  return 0;
}
