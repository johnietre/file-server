#ifndef TREE_HPP
#define TREE_HPP

#include <string>
using namespace std;

class Node {
private:
  // If the node is a directory, the name will have a trailing "/"
  struct llnode {
    Node *data;
    llnode *prev;
    llnode *next;
  };
  string name_;
  bool dir_;
  int last_mod_;
  Node *parent_;
  llnode *child_list_;
public:
  Node();
  ~Node();
  string name();
  string path();
  bool dir();
  int last_mod();

  Node* getChild();
  void addChild();
  void removeChild();
}

#endif
