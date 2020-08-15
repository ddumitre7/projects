#include <iostream>
#include <map>
#include <string>

#include "trie.h"

using namespace std;
using namespace triex;

int main() {
  cout << "But hello!\n";

  Trie t;

  t.addString("copy")
      .addString("cosmic")
      .addString("cosmos")
      .addString("cosmopolitan")
      .addString("copper")
      .addString("condition");

  t.addString("mood")
      .addString("moody")
      .addString("moon")
      .addString("moonbeam")
      .addString("moonlight")
      .addString("moose")
      .addString("mood") // Add this word again
      .addString("moody"); // Add this word again

  t.print();

  return 0;
}