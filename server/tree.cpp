#include "tree.hpp"

/* Notes
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
  // printf("Deleting %s\t(path: %s type: %c)\n", name.c_str(), this->fullPath().c_str(), type);
  #endif
  for (Node *prev = children; children != nullptr; children = prev->next) {
    prev = children;
    delete children;
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

Node* Node::addChild(Node *node) {
  if (type == 'f')
    return nullptr;
  node->parent = this;
  if (children == nullptr)
    children = node;
  else
    children->addSibling(node);
  return node;
}

// returns nullptr if path already exists
Node* Node::addChild(string path, char type, bool recursive) {
  Node *n = this;
  string part = "";
  for (char c : path) {
    if (c == '/') {
      if (part != ".") {
        Node *node = n->findChild(part);
        if (node == nullptr) {
          if (!recursive)
            return node;
          n = n->addChild(new Node(part, 'd'));
        } else
          n = node;
      }
      part = "";
    } else
      part += c;
  }
  if (n->findChild(part) != nullptr)
    return nullptr;
  Node *child = new Node(part, type);
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

Node* Node::addSibling(Node *node) {
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
  return node;
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
  // NOTE: sometimes getting malloc() corrupted top size when using resize
  // or constructor
  vector<Node *> v;
  // v.resize(numSiblings);
  int i = 0;
  for (Node *n = getFirstSibling(); n != nullptr; n = n->next)
    v.push_back(n);
    // v[i++] = n;
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
