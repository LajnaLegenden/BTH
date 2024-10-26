#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include <string>
#include <vector>
using namespace std;
struct SymbolTableEntry
{
  public:
  string id;
  string type;
};

class Scope
{
  public:
  string id;
  Scope *parent = nullptr;
  //List of children using vector
  vector<Scope*> children = {};
  vector<SymbolTableEntry> table = {};
};


#endif // SYMBOL_TABLE_H
