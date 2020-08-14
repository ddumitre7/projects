#include <iostream>
#include <map>
#include <string>

using namespace std;

// TODO add own namespace

struct TrieNode;

class Trie {

public:

    Trie() { 
        _root = new TrieNode;
    };

    void addString(const std::string &s) {

        auto cursor = _root;
        for (auto c : s) {

            if (!cursor->_map[c]) {
                cursor->_map[c] = new TrieNode; 

            }

            cursor = cursor->_map[c]; 
        }

        cursor->_is_leaf = true;

    return;
}

    void print() {

        printRec(_root);
    }


private:

    struct TrieNode {
        map<char, TrieNode*> _map;
        bool _is_leaf{false};
    };

    TrieNode *_root;
    
    static void printRec(TrieNode *root) {

        if (!root) return;

        if (root->_is_leaf) {
            cout << "\n";
        }

        for (const auto& e : root->_map) {
            cout << e.first << " ";
            printRec(e.second);
        }


    }

};




int main() {

    cout << "But hello!\n";

    Trie t;

    t.addString("to");
    t.addString("towards");
    t.addString("tonight");

    t.print();

    return 0;
}