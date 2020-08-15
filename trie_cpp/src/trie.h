#ifndef TRIEX_TRIE_H_
#define TRIEX_TRIE_H_

#include <iostream>
#include <map>
#include <string>

using namespace std;

namespace triex {

struct TrieNode;

class Trie {
 public:
  Trie() : root_{new TrieNode} {}
  Trie(const Trie &t) { root_ = t.root_; }
  Trie(Trie &&t) {
    root_ = t.root_;
    t.root_ = nullptr;
  }

  ~Trie() {
    cout << "Delete trie:" << endl;
    delete root_;
  }

  Trie &addString(const std::string &s) {
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

  void print() { printRecursively(root_); }

 private:
  struct TrieNode {
    map<char, TrieNode *> map_;
    bool is_leaf_{false};
    ~TrieNode() {
      if (is_leaf_) cout << endl;
      for (auto e : map_) {
        cout << e.first << " ";
        delete e.second;
      }
    }
  };

  TrieNode *root_;

  static void printRecursively(TrieNode *root) {
    if (!root) return;

    if (root->is_leaf_) {
      cout << "\n";
    }

    for (const auto &e : root->map_) {
      cout << e.first << " ";
      printRecursively(e.second);
    }
  }
};

//DD:TODO
// Return allocator
// Traits

}  // namespace triex

#endif  // TRIEX_TRIE_H_