#ifndef TRIECONT_TRIE_H_
#define TRIECONT_TRIE_H_

#include <assert.h>

#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>

using namespace std;

namespace triecont {

struct TrieNode;

class Trie {
 public:
  // Constructors and destructor
  Trie();
  Trie(const Trie &t);
  Trie(Trie &&t);
  ~Trie();

  // Operators
  Trie &operator=(const Trie &);
  Trie &operator=(Trie &&);
  bool operator==(const Trie &);
  bool operator!=(const Trie &);

  // Adding a string
  Trie &addString(const std::string &);
  // Iterating through the tree
  void forEach(function<void(const string &)>);

 private:
  // TrieNode is the internal data structure of the trie tree
  struct TrieNode {
    map<char, TrieNode *> map_;
    bool is_leaf_{false};
    ~TrieNode();

    TrieNode *clone();
    bool isEqual(const TrieNode *);
  };

  TrieNode *root_;

  void allWordsRecursively_(TrieNode *, string &,
                            function<void(const string &)>);
};

// Class definitions

// Trie

Trie::Trie() : root_{new TrieNode} {}

Trie::Trie(const Trie &t) { root_ = t.root_->clone(); }

Trie::Trie(Trie &&t) : root_{t.root_} { t.root_ = nullptr; }

Trie::~Trie() { delete root_; }

Trie &Trie::operator=(const Trie &t) {
  if (this == &t) return *this;

  Trie tmp{t};
  swap(tmp, *this);
  return *this;
}

Trie &Trie::operator=(Trie &&t) {
  swap(root_, t.root_);
  return *this;
}

bool Trie::operator==(const Trie &t) { return root_->isEqual(t.root_); }

bool Trie::operator!=(const Trie &t) { return *this == t; }

Trie &Trie::addString(const std::string &s) {
  auto cursor = root_;

  for (auto c : s) {
    if (!cursor->map_[c]) {
      cursor->map_[c] = new TrieNode;
    }

    cursor = cursor->map_[c];
  }

  cursor->is_leaf_ = true;

  return *this;
}

void Trie::forEach(function<void(const string &)> f) {
  string s;

  assert(root_);

  for (auto e : root_->map_) {
    s.push_back(e.first);
    allWordsRecursively_(e.second, s, f);
    s.pop_back();
  }

  return;
}

void Trie::allWordsRecursively_(TrieNode *root, string &s,
                                function<void(const string &)> f) {
  if (!root) return;

  if (root->is_leaf_) {
    f(s);
  }

  for (auto e : root->map_) {
    s.push_back(e.first);
    allWordsRecursively_(e.second, s, f);
    s.pop_back();
  }

  return;
}

// TrieNode

Trie::TrieNode::~TrieNode() {
  // if (is_leaf_) cout << endl;
  for (auto e : map_) {
    // cout << e.first << " ";
    delete e.second;
  }
}

Trie::TrieNode *Trie::TrieNode::clone() {
  auto t = new TrieNode;
  t->is_leaf_ = is_leaf_;

  for (auto e : map_) {
    t->map_[e.first] = e.second->clone();
  }
  return t;
}

bool Trie::TrieNode::isEqual(const TrieNode *t) {
  if (!t) return false;

  if (is_leaf_ != t->is_leaf_) return false;

  auto it1 = map_.begin();
  auto it2 = t->map_.begin();

  while (it1 != map_.end() && (it2 != t->map_.end())) {
    if (it1->second->isEqual(it2->second)) {
      ++it1;
      ++it2;
    } else
      return false;
  }

  if ((it1 == map_.end()) && (it2 == t->map_.end()))
    return true;
  else
    return false;
}

// DD:TODO
// Return allocator
// Traits

}  // namespace triecont

#endif  // TRIECONT_TRIE_H_