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

  // Adding a string
  Trie &addString(const std::string &);
  // Iterating through the tree
  void forEach(function<void(const string &)>);

  // Forward declaration
  class const_iterator;

  const_iterator begin() const { return const_iterator{this}; }
  const_iterator end() const { return const_iterator{}; }

  class const_iterator {
    list<pair<TrieNode *, map<char, TrieNode *>::const_iterator>> stack;

   public:
    const_iterator(const Trie *t) {
      stack.push_back(make_pair(t->m_root, t->m_root->m_map.cbegin()));

      if (t->m_root->m_map.cbegin() == t->m_root->m_map.cend()) {
        stack.clear();
        return;
      }

      auto it = t->m_root->m_map.cbegin();
      while (it->second->is_leaf_ == false) {
        auto it1 = it->second->m_map.cbegin();
        assert(it->second->m_map.cbegin() != it->second->m_map.cend());
        stack.push_back(make_pair(it->second->m_map.cbegin()->second, it1));
        it = it1;
      }
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
      stack.clear();
      return *this;
    }

    string operator*() const {
      string s;

      for (const auto &e : stack) {
        s.push_back(e.second->first);
      }
      return s;
    }
  };

 private:
  // TrieNode is the internal data structure of the trie tree
  struct TrieNode {
    map<char, TrieNode *> m_map;
    bool is_leaf_{false};
    ~TrieNode();

    TrieNode *clone();
    bool isEqual(const TrieNode *);
  };

  TrieNode *m_root;

  void allWordsRecursively_(TrieNode *, string &,
                            function<void(const string &)>);
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

Trie &Trie::addString(const std::string &s) {
  auto cursor = m_root;

  for (auto c : s) {
    if (!cursor->m_map[c]) {
      cursor->m_map[c] = new TrieNode;
    }

    cursor = cursor->m_map[c];
  }

  cursor->is_leaf_ = true;

  return *this;
}

void Trie::forEach(function<void(const string &)> f) {
  string s;

  assert(m_root);

  for (auto e : m_root->m_map) {
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

  for (auto e : root->m_map) {
    s.push_back(e.first);
    allWordsRecursively_(e.second, s, f);
    s.pop_back();
  }

  return;
}

// TrieNode

Trie::TrieNode::~TrieNode() {
  // if (is_leaf_) cout << endl;
  for (auto e : m_map) {
    // cout << e.first << " ";
    delete e.second;
  }
}

Trie::TrieNode *Trie::TrieNode::clone() {
  auto t = new TrieNode;
  t->is_leaf_ = is_leaf_;

  for (auto e : m_map) {
    t->m_map[e.first] = e.second->clone();
  }
  return t;
}

bool Trie::TrieNode::isEqual(const TrieNode *t) {
  if (!t) return false;

  if (is_leaf_ != t->is_leaf_) return false;

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

// DD:TODO
// Return allocator
// Traits

}  // namespace triecont

#endif  // TRIECONT_TRIE_H_