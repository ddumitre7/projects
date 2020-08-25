#include <iostream>
#include <map>
#include <string>

#include "trie.h"

using namespace std;
using namespace triecont;

int main() {
  cout << "But hello!\n";

  Trie t1;

  t1.addString("copy")
      .addString("cosmic")
      .addString("cosmos")
      .addString("cosmopolitan")
      .addString("copper")
      .addString("condition");

  t1.addString("mood")
      .addString("moody")
      .addString("moon")
      .addString("moonbeam")
      .addString("moonlight")
      .addString("moose")
      .addString("mood")    // Add this word again
      .addString("moody");  // Add this word again

  auto t2{t1};

  auto print = [](const string& s) { cout << s << endl; };

  cout << "________________________________" << endl;

  t2.forEach(print);

  t1.addString("convenient");

  t2.addString("monster");

  std::cout << std::boolalpha;

  cout << "(t1 == t2): " <<(t1 == t2) << endl;

  cout << "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG" << endl;

  t2.forEach(print);

  cout << "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH" << endl;

  int counter{};

  t2.forEach([&counter](const string& s) { ++counter; });

  cout << "Counter: " << counter << endl;

  return 0;
}
