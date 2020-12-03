#ifndef __PAGE_H__
#define __PAGE_H__
#include <iostream>
#include <fstream>
#include <string>
#include<vector>
using namespace std;

class Page{
 public:
  vector<string> navigation;
  vector<string> text;
  vector<long> choicePage;
  int navigationCatogry;
 public:
  Page();
  void read(string filename);
  void checkNavigation();
  void printPage();
  ~Page();
};

#endif
