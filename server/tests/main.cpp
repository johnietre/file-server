#include "../tree.hpp"
#include <filesystem>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
  Node *root = new Node("folder1", 'd');
  root->addChild(new Node("test1.txt", 'f'));
  root->addChild(new Node("test2.txt", 'f'));
  Node *testf1 = new Node("testf1", 'f');
  root->addChild(testf1);
  Node *testf2 = new Node("testf2", 'd');
  testf1->addSibling(testf2);
  testf2->addChild(new Node("test2.txt", 'f'));
  // for (auto &p : std::filesystem::recursive_directory_iterator(".")) {
  //   cout << p.path().filename() << '\n';
  // }
  delete root;
  return 0;
}
