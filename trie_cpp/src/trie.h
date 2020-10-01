#ifndef TRIECONT_TRIE_H_
#define TRIECONT_TRIE_H_

#include <assert.h>

#include <functional>
#include <list>
#include <map>
#include <string>

using namespace std;

namespace triecont {

// struct TrieNode;

class Trie {
 private:
  // Forward declaration of the data type used internally by the
  // trie. This forward declaration is required by the iterator.
  struct TrieNode;

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

  // Forward declaration
  class const_iterator;

  const_iterator begin() const { return const_iterator{this}; }
  const_iterator end() const { return const_iterator{}; }

  // Add a string to the Trie tree
  Trie &add(const std::string &);
  // Find a subtree based on a prefix
  const_iterator find_prefix(const std::string &);

  class const_iterator {
    list<pair<TrieNode *, map<char, TrieNode *>::const_iterator>> stack;
    std::string prefix;

    inline void next_leaf_node() {
      auto ptr = stack.back().second->second;
      while (ptr->m_is_leaf == false) {
        assert(ptr->m_map.cbegin() != ptr->m_map.cend());
        stack.push_back(make_pair(ptr, ptr->m_map.cbegin()));
        ptr = ptr->m_map.cbegin()->second;
      }
    }

   public:
    const_iterator(const Trie *t) {
      stack.push_back(make_pair(t->m_root, t->m_root->m_map.cbegin()));

      if (t->m_root->m_map.cbegin() == t->m_root->m_map.cend()) {
        stack.clear();
        return;
      }

      next_leaf_node();

      return;
    }

    const_iterator(TrieNode *node, const std::string &str) : prefix{str} {
      if (node->m_map.size() == 0) {
        return;
      }

      stack.push_back(make_pair(node, node->m_map.cbegin()));

      next_leaf_node();
    }

    const_iterator() = default;

    bool operator==(const const_iterator &other) {
      return stack == other.stack;
    }
    bool operator!=(const const_iterator &other) {
      return stack != other.stack;
    }
    // const_iterator operator++(int) {

    //   return ret;
    // }

    const_iterator &operator++() {

      if (stack.empty() == true) {
        return *this;
      }

      // We are always in a leaf at this point
      auto ptr = stack.back().first;
      if (ptr->m_map.size() == 0) {
        stack.clear();
        return *this;
      }
      auto ptr_leaf = stack.back().second->second;

      // First we try to go down in the tree
      if (ptr_leaf->m_map.size() != 0) {
        stack.push_back(make_pair(ptr_leaf, ptr_leaf->m_map.cbegin()));
        next_leaf_node();

        return *this;
      }

      // If we are here then it means that we need to start to
      // pop elements from the stack

      while (stack.empty() == false) {
        ++stack.back().second;
        ptr = stack.back().first;
        if (stack.back().second == ptr->m_map.cend()) {
          stack.pop_back();
          continue;
        }

        next_leaf_node();

        return *this;
      }

      // return *this;

      // We reach here when the stack is empty
      return *this;
    }

    string operator*() const {
      string s;

      for (const auto &e : stack) {
        s.push_back(e.second->first);
      }
      return prefix + s;
    }
  };

 private:
  // TrieNode is the internal data structure of the trie tree
  struct TrieNode {
    map<char, TrieNode *> m_map;
    bool m_is_leaf{false};
    ~TrieNode();

    TrieNode *clone();
    bool isEqual(const TrieNode *);
  };

  TrieNode *m_root;

  void allWordsRecursively_(TrieNode *, string &,
                            function<void(const string &)>);

 public:
  void printTree() {
    string s;
    cout << "PRINT BEGIN\n";

    auto print101 = [](const string &s) { std::cout << s << endl; };
    allWordsRecursively_(m_root, s, print101);
    cout << "PRINT END\n";
  }

};  // namespace triecont

// Class definitions

// Trie

Trie::Trie() : m_root{new TrieNode} {}

Trie::Trie(const Trie &t) { m_root = t.m_root->clone(); }

Trie::Trie(Trie &&t) : m_root{t.m_root} { t.m_root = nullptr; }

Trie::~Trie() { delete m_root; }

Trie &Trie::operator=(const Trie &t) {
  if (this == &t) return *this;

  Trie tmp{t};
  swap(tmp, *this);
  return *this;
}

Trie &Trie::operator=(Trie &&t) {
  swap(m_root, t.m_root);
  return *this;
}

bool Trie::operator==(const Trie &t) { return m_root->isEqual(t.m_root); }

bool Trie::operator!=(const Trie &t) { return *this == t; }

Trie &Trie::add(const std::string &s) {
  auto cursor = m_root;

  for (const auto& c : s) {
    if (cursor->m_map[c] == nullptr) {
      cursor->m_map[c] = new TrieNode;
    }
    cursor = cursor->m_map[c];
  }

  cursor->m_is_leaf = true;

  return *this;
}

void Trie::allWordsRecursively_(TrieNode *root, string &s,
                                function<void(const string &)> f) {
  if (!root) return;

  if (root->m_is_leaf) {
    f(s);
  }

  for (auto e : root->m_map) {
    s.push_back(e.first);
    allWordsRecursively_(e.second, s, f);
    s.pop_back();
  }

  return;
}

// TrieNode

Trie::TrieNode::~TrieNode() {
  // if (m_is_leaf) cout << endl;
  for (auto e : m_map) {
    // cout << e.first << " ";
    delete e.second;
  }
}

Trie::TrieNode *Trie::TrieNode::clone() {
  auto t = new TrieNode;
  t->m_is_leaf = m_is_leaf;

  for (auto e : m_map) {
    t->m_map[e.first] = e.second->clone();
  }
  return t;
}

bool Trie::TrieNode::isEqual(const TrieNode *t) {
  if (!t) return false;

  if (m_is_leaf != t->m_is_leaf) return false;

  auto it1 = m_map.begin();
  auto it2 = t->m_map.begin();

  while (it1 != m_map.end() && (it2 != t->m_map.end())) {
    if (it1->second->isEqual(it2->second)) {
      ++it1;
      ++it2;
    } else
      return false;
  }

  if ((it1 == m_map.end()) && (it2 == t->m_map.end()))
    return true;
  else
    return false;
}

Trie::const_iterator Trie::find_prefix(const std::string &prefix) {
  auto cursor = m_root;

  if (prefix.size() == 0) {
    return Trie::const_iterator{};
  }

  for (const auto &e : prefix) {
    auto iterator = cursor->m_map.find(e);

    if (iterator == cursor->m_map.end()) {
      return Trie::const_iterator{};
    } else {
      cursor = iterator->second;
    }
  }

  return Trie::const_iterator{cursor, prefix};
}

// Find a subtree based on a prefix
// const_iterator Trie::find(const std::string &prefix) {
//   return const_iterator{};
// }

// DD:TODO
// Return allocator
// Traits

}  // namespace triecont

#endif  // TRIECONT_TRIE_H_