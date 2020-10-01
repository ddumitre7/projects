#include <iostream>
#include <map>
#include <string>

#include "trie.h"

using namespace std;
using namespace triecont;

int main() {
  cout << "But hello!\n";
  cout << "X X X X X X X X X X X X X X X X X X X X X X X X X X" << endl;

  Trie tx;

  tx.add("copy")
      .add("cosmic")
      .add("cosmos")
      .add("cosmopolitan")
      .add("copper")
      .add("uxyz")
      .add("conf")
      .add("con")
      .add("condition")
      .add("contur");

tx.printTree();

  auto counter = 0;
  // for (auto e = tx.begin(); e != tx.end(); ++e) {
  //    cout << "%%%%%%%%%%%% " << *e << endl;
  //    counter++;
  // }
  //  cout << "COUNTER:::::: " << counter << endl;
  
  counter = 0;

  auto it = tx.find_prefix("con");

  for (auto e = it; e != tx.end(); ++e) {
     cout << "^^^^^^^^ " << *e << endl;
     counter++;
  }
   cout << "COUNTER 2:::::: " << counter << endl;


  //auto e = tx.begin();
  //cout << "%%%%%%%%%%%% "<< *e << endl;
  //++e;
  //cout << "%%%%%%%%%%%% "<< *e << endl;
  // ++e;
  // cout << *e << endl;

//   ++e;
//  cout << *e << endl;
  // ++e;
  // cout << *e << endl;
  // ++e;
  // cout << *e << endl;

  return 0;
}
