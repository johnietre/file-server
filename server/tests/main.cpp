#include "../tree.hpp"
#include <filesystem>
#include <iostream>
#include <string>
using namespace std;

void TestHardCoded();
void TestRealDir();

int main(int argc, char *argv[]) {
  TestRealDir();
  return 0;
}

void TestHardCoded() {
  Node *root = new Node("folder1", 'd');
  Node *file1 = new Node("file1.txt", 'f');
  root->addChild(file1);
  Node *file2 = new Node("file2.txt", 'f');
  file1->addSibling(file2);
  Node *sub1 = new Node("sub1", 'd');
  root->addChild(sub1);
  Node *sub2 = new Node("sub2", 'd');
  sub1->addSibling(sub2);
  Node *file3 = new Node("file3.txt", 'f');
  sub2->addChild(file3);
  Node *file4 = new Node("file4.txt", 'f');
  file3->addSibling(file4);
  Node *file5 = root->addChild("./sub1/file5.txt", 'f');
  Node *file6 = root->addChild("./sub3/file6.txt", 'f', true);
  delete root;
}

void TestRealDir() {
  Node *root = new Node(".", 'd');
  for (auto &p : std::filesystem::recursive_directory_iterator(".")) {
    root->addChild(p.path(), 'd');
  }
  delete root;
}
