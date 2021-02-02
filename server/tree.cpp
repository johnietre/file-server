#include "tree.hpp"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

Node::Node(string name, char type, int lastModified)
    : name(name), type(type), lastModified(lastModified), parent(nullptr),
      children(nullptr), prev(nullptr), next(nullptr), numSiblings(1) {}

Node::~Node() {
  cout << name << '\n';
  for (; children != nullptr; children = children->next)
    delete children;
  if (prev != nullptr) {
    prev->next = next;
  } else {
    if (parent != nullptr)
      parent->children = next;
  }
  if (next != nullptr) {
    next->prev = prev;
  }
}

void Node::addChild(Node *node) {
  if (children == nullptr)
    children = node;
  else
    children->addSibling(node);
}

void Node::removeChild(string name) {
  Node *n = children;
  for (; n != nullptr; n = n->next) {
    if (n->name == name) {
      this->removeChild(n);
      break;
    }
  }
}

void Node::removeChild(Node *node) {
  Node *n = children;
  for (; n != nullptr; n = n->next) {
    if (n == node) {
      if (n->prev != nullptr)
        n->prev->next = n->next;
      if (n->next != nullptr)
        n->next->prev = n->prev;
      if (n == children)
        children = n->next;
      if (n->type == 'd') {
        for (; n->children != nullptr; n->children = n->children->next)
          n->removeChild(n->children);
      }
      delete n;
      return;
    }
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
  node->numSiblings = n->numSiblings;
}

Node *Node::getFirst() {
  Node *n = this;
  for (; n->prev != nullptr; n = n->prev)
    ;
  return n;
}

vector<Node *> Node::siblingsToVector() {
  vector<Node *> v(numSiblings);
  int i = 0;
  for (Node *n = getFirst(); n != nullptr; n = n->next)
    v[i++] = n;
  return v;
}

Node *Node::find(string path) { return nullptr; }

string Node::fullPath() {
  string path = name;
  for (Node *p = parent; p != nullptr; p = p->parent)
    path = p->name + "/" + path;
  return path;
}

// LLNode::LLNode(TreeNode *node) : node(node), next(nullptr) {}

// void LLNode::append(TreeNode *node) {
//   LLNode *n = this;
//   while (n->next != nullptr)
//     n = n->next;
//   n->next = new LLNode(node);
// }

// TreeNode::TreeNode(string name, char type) : name(name), type(type),
// children(nullptr) {}

// void TreeNode::addChild(TreeNode *node) {
//   node->parent = this;
//   children->append(node);
// }

// void TreeNode::removeChild(string name) {
//   LLNode *ln = children, *prev = nullptr;
//   for (; ln != nullptr; prev = ln, ln = ln->next) {
//     if (ln->node->name == name)
//       break;
//   }
//   if (ln != nullptr) {
//     if (ln->node->type == 'd') {
//       LLNode *nietos = ln->node->children; // spanish for grandchildren
//       for (; nietos != nullptr; nietos = nietos->next)
//         ln->node->removeChild(nietos->node->name);
//     }
//     if (prev != nullptr) {
//       prev->next = ln->next;
//       delete ln;
//     } else {
//       delete children;
//       children = nullptr;
//     }
//   }
// }

// TreeNode* TreeNode::find(string path) {
//   int n = 0;
//   for (char c : path)
//     n += (c == '/') ? 1 : 0;
//   string *parts = new string[n], *p = parts, part;
//   for (char c : path) {
//     if (c == '/') {
//       *p = part;
//       p++;
//     } else
//       part += c;
//   }
//   p = parts;
//   TreeNode *tn = this;
//   for (int i = 0; i < n;) {
//     LLNode *ln = tn->children;
//     for (; ln != nullptr; ln = ln->next) {
//       if (ln->node->name == *p)
//         break;
//     }
//     if (ln == nullptr) {
//       delete[] parts;
//       return nullptr;
//     }
//     i++;
//     p++;
//   }
//   delete[] parts;
//   return tn;
// }

// string TreeNode::fullPath() {
//   string path = name;
//   for (TreeNode *p = parent; p != nullptr; p = p->parent)
//     path = p->name + "/" + path;
//   return path;
// }
