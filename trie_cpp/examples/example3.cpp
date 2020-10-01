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

  cout << "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ" << endl;

  for (auto e = t.begin(); e != t.end(); ++e) {
    cout << *e << endl;
  }

  cout << "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT" << endl;

  auto print101 = [](const string& s) { std::cout << s << endl; };

  for_each(t.begin(), t.end(), print101);

  cout << "MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl;


  for(const auto&r : t) print101(r); 

  cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" << endl;

  auto t2{t};

  auto print = [](const string& s) { cout << s << endl; };

  cout << "________________________________" << endl;

  //t2.forEach(print);

  t.add("convenient");

  t2.add("monster");

  std::cout << std::boolalpha;

  cout << "(t1 == t2): " << (t == t2) << endl;

  cout << "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG" << endl;

  //t2.forEach(print);

  cout << "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH" << endl;

  int counter{};

  //t2.forEach([&counter](const string& s) { ++counter; });

  cout << "Counter: " << counter << endl;


  cout << "X X X X X X X X X X X X X X X X X X X X X X X X X X" << endl;

  auto ee = t.find_prefix("codition");

  for (; ee != t.end(); ++ee) {
    cout << *ee << endl;
  }


  cout << "X X X X X X X X X X X X X X X X X X X X X X X X X X" << endl;

  return 0;
}
