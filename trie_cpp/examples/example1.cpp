#include <algorithm>
#include <iostream>
#include <map>
#include <string>

#include "trie.h"

using namespace std;
using namespace triecont;

int main() {
  cout << "But hello!\n";

  Trie t;

  t.add("copy")
      .add("cosmic")
      .add("cosmos")
      .add("cosmopolitan")
      .add("copper")
      .add("condition");

  t.add("mood")
      .add("moody")
      .add("moon")
      .add("moonbeam")
      .add("moonlight")
      .add("moose")
      .add("mood")    // Add this word again
      .add("moody");  // Add this word again

  cout << "Printing trie with iterators:" << endl;
  for (auto e = t.begin(); e != t.end(); ++e) {
    cout << *e << " ";
  }

  cout << endl << endl;

  cout << "Printing trie with range:" << endl;
  for (auto e : t) {
    cout << e << " ";
  }

  cout << endl << endl;

  cout << "Printing trie with \"for_each\":" << endl;

  for_each(t.begin(), t.end(), [](const string& s) { std::cout << s << " "; });

  cout << endl << endl;

  cout << "Printing the words with prefix \"co\":" << endl;

  auto iterator = t.find_prefix("co");
  for (; iterator != t.end(); ++iterator) {
    cout << *iterator << " ";
  }

  cout << endl << endl;

  cout << "Printing the words with prefix \"moon\":" << endl;

  for_each(t.find_prefix("moon"), t.end(),
           [](const string& s) { std::cout << s << " "; });

  cout << endl << endl;

  cout << "Printing the words with prefix \"moonlight\":" << endl;

  for_each(t.find_prefix("moonlight"), t.end(),
           [](const string& s) { std::cout << s << " "; });

  cout << endl << endl;

  return 0;
}
