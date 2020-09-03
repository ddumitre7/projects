#include <algorithm>
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

  cout << "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ" << endl;

  auto ii = t1.begin();

  cout << *ii << endl;

  cout << "UUUUUUUUUUUUUUUUUUUUUUUUUUU" << endl;

  for (auto e = t1.begin(); e != t1.end(); ++e) {
    cout << *e << endl;
  }

  cout << "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT" << endl;

  auto print101 = [](const string& s) { std::cout << s << endl; };

  for_each(t1.begin(), t1.end(), print101);

  cout << "MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM" << endl;


  for(const auto&
   r : t1) print101(r); 

  cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" << endl;

  auto t2{t1};

  auto print = [](const string& s) { cout << s << endl; };

  cout << "________________________________" << endl;

  t2.forEach(print);

  t1.addString("convenient");

  t2.addString("monster");

  std::cout << std::boolalpha;

  cout << "(t1 == t2): " << (t1 == t2) << endl;

  cout << "GGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG" << endl;

  t2.forEach(print);

  cout << "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH" << endl;

  int counter{};

  t2.forEach([&counter](const string& s) { ++counter; });

  cout << "Counter: " << counter << endl;

  return 0;
}
