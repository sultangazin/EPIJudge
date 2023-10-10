#include <string>

#include "test_framework/generic_test.h"
using std::string;

string ConvertBase(const string& num_as_string, int b1, int b2) {
  // check if negative
  bool is_negative = false; 
  if (num_as_string.front() == '-') {
    is_negative = true; 
  }
  // convert from b1 to int
  int num = 0;
  for (auto digit : num_as_string) {
    if (digit == '-') {
      continue; 
    }
    num *= b1;
    if (digit >= '0' && digit <= '9') {
      num += digit - '0';
    }
    else if (digit >= 'A' && digit <= 'F') {
      num += digit - 'A' + 10;
    }
  }
  
  // convert from int to b2
  string s;
  while (num != 0) {
    int digit = num % b2;
    if (digit >= 0 && digit <= 9) {
      s.push_back(digit + '0');
    }
    if (digit >= 10 && digit <= 16) {
      s.push_back(digit - 10 + 'A');
    }
    num /= b2;
  }
  return s;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
