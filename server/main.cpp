#include "tree.hpp"
#include <filesystem>
#include <iostream>
using namespace std;

int main() {
  Node *root = new Node("folder1", 'd');
  root->addChild(new Node("test1.txt", 'f'));
  root->addChild(new Node("test2.txt", 'f'));
  Node *testf1 = new Node("testf1", 'f');
  root->addChild(testf1);
  Node *testf2 = new Node("testf2", 'd');
  testf1->addSibling(testf2);
  testf2->addChild(new Node("test2.txt", 'f'));
  delete root;
  return 0;
}
