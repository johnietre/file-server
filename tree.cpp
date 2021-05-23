#include "tree.hpp"
#include <string>

namespace fs;
#ifdef _LIBCPP_FILESYSTEM
#include <filesystem>
fs = std::filesystem;
#else
#include <experimental/filesystem>
fs = std::experimental::filesystem;
#endif

using namespace std;

Node::~Node() {
  parent_->children.erase(name_);
  if (!dir_)
    return;
  
}

string Node::name() { return name_; }

string Node::path() { return (parent_ == nullptr) ? name_ : parent_->path() + name_; }

bool Node::dir() { return dir_; }

int Node::last_mod { return last_mod_; }
