#include "tree.hpp"

/*
 * Better combine the removeChild(), removeSibling() and ~Node() methods
 * Possibly handle case where remove method removes self
 * Handle for duplicate names in children/siblings (when adding sibling/child)
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

Node::Node(string name, char type, int lastModified)
    : name(name), type(type), lastModified(lastModified), parent(nullptr),
      children(nullptr), prev(nullptr), next(nullptr), numSiblings(1) {}

Node::~Node() {
  #ifdef DEBUG
  printf("Deleting %s (type: %c)\n", this->fullPath().c_str(), type);
  #endif
  for (; children != nullptr; children = children->next)
    delete children;
  if (name == "folder1") {
    cout << "folder1";
    cout << (prev == nullptr) << '\n';
    cout << (next == nullptr) << '\n';
  }
  if (prev != nullptr) {
    prev->next = next;
  } else {
    if (parent != nullptr)
      parent->children = next;
  }
  if (next != nullptr)
    next->prev = prev;
}

void Node::addChild(Node *node) {
  node->parent = this;
  if (children == nullptr)
    children = node;
  else
    children->addSibling(node);
}

// returns nullptr if path already exists
Node* Node::addChild(string path, char type) {
  Node *n = this;
  string part = "";
  for (char c : path) {
    if (c == '/') {
      if (part == ".")
        continue;
      n = n->findChild(part);
      if (n == nullptr)
        return n;
    } else
      part += c;
  }
  if (n->findChild(part) != nullptr)
    return nullptr;
  Node *child = new Node(path, type);
  n->addChild(child);
  return child;
}

Node* Node::findChild(string name) {
  return (children == nullptr) ? nullptr : children->findSibling(name);
}

void Node::removeChild(string name) {
  Node *n = findChild(name);
  if (n != nullptr)
    delete n;
}

void Node::removeChild(Node *node) {
  if (children != nullptr) {
    Node *n = children->findSibling(node->name);
    if (n != nullptr)
      delete n;
  }
}

void Node::addSibling(Node *node) {
  Node *n = this;
  n->numSiblings++;
  while (n->next != nullptr) {
    n = n->next;
    n->numSiblings++;
  }
  n->next = node;
  node->prev = n;
  node->parent = n->parent;
  node->numSiblings = n->numSiblings;
}

Node* Node::findSibling(string name) {
  Node *n = this;
  for (; n != nullptr && n->name != name; n = n->next);
  return n;
}

void Node::removeSibling(Node *node) {
  Node *n = this->findSibling(node->name);
  if (n != nullptr)
    delete n;
}

Node *Node::getFirstSibling() {
  Node *n = this;
  for (; n->prev != nullptr; n = n->prev)
    ;
  return n;
}

vector<Node *> Node::siblingsToVector() {
  vector<Node *> v(numSiblings);
  int i = 0;
  for (Node *n = getFirstSibling(); n != nullptr; n = n->next)
    v[i++] = n;
  return v;
}

vector<Node*> Node::childrenToVector() {
  if (children == nullptr) {
    vector<Node*> v;
    return v;
  }
  return children->siblingsToVector();
}

Node *Node::find(string path) { return nullptr; }

string Node::fullPath() {
  string path = name;
  for (Node *p = parent; p != nullptr; p = p->parent)
    path = p->name + "/" + path;
  return path;
}
