#include <iostream>
#include <map>
#include <string>

#include "trie.h"

using namespace std;
using namespace triecont;

void printer(const vector<string>&);

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

  auto ret_vector = t1.allWords();

  cout << "________________________________" << endl;

  printer(t1.allWords());

  auto t2{t1};
  cout << "________________________________" << endl;

  printer(t2.allWords());

  cout << "==================================" << endl;

    t1.addString("convenient");

  printer(t1.allWords());

cout << "==================================" << endl;

    t2.addString("monster");

  printer(t2.allWords());


  printer(t2.allWords());



auto t3{t2};

std::cout << std::boolalpha;

cout << (t2 == t3) << endl;



  return 0;
}

void printer(const vector<string>& vec) {
  for (const auto& e : vec) {
    cout << e << endl;
  }
}
