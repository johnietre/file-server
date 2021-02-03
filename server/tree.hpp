#ifndef TREE_HPP
#define TREE_HPP

#include <cstddef> // ptrdiff_t
#include <iterator> // forward_iterator_tag
#include <string>
#include <vector>
using namespace std;

// Mixture of Tree and Double Linked List
struct Node {
  struct Iterator {
  public:
    using iter_cat = forward_iterator_tag;
    using diff_type = ptrdiff_t;
    using val_type = Node *;
    using pointer = Node **;
    using reference = Node *&;

    Iterator(pointer ptr) : m_ptr(ptr) {}
    reference operator*() const { return *m_ptr; }
    pointer operator->() { return m_ptr; }
    Iterator &operator++() {
      m_ptr++;
      return *this;
    }
    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }

  private:
    pointer m_ptr;
  };

  string name;
  char type; // 'f' or 'd'
  int lastModified;
  Node *parent;    // Points to parent
  Node *children;  // Points to head of "doubly linked list" of children/leaves
  Node *prev;      // Prev node in "doubly linked list"
  Node *next;      // Next node in "doubly linked list"
  int numSiblings; // number includes self; "number of siblings in family"

  Node(string name, char type, int lastModified = 0);
  ~Node();

  Node* addChild(Node *node);
  Node* addChild(string path, char type, bool recursive=false);
  Node *findChild(string name);
  void removeChild(string name);
  void removeChild(Node *node);

  Node* addSibling(Node *node);
  Node *findSibling(string name);
  void removeSibling(Node *node);
  Node *getFirstSibling(); // returns the "head" of the tree leaf linked list

  Node *find(string path);

  vector<Node *> siblingsToVector();
  vector<Node*> childrenToVector();
  string fullPath();
};

#endif
