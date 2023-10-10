#include <string>
#include <algorithm>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
  bool is_negative = false;
  if (x < 0) {
    is_negative = true;
    x = -x;
  }
  if (x == 0) {
    return "0";
  }
  string result = "";
  while (x != 0) {
    result.push_back((x % 10) + '0');
    x /= 10;
  }
  if (is_negative) {
    result.push_back('-');
  }
  std::reverse(result.begin(), result.end());
  return result;
}
int StringToInt(const string& s) {
  int result = 0;
  bool is_negative = false; 
  for (auto num : s) {
    if (num == '-') {
      is_negative = true; 
    }
    result *= 10;
    result += num - '0';
  }
  if (is_negative) {
    result = -result;
  }
  return result;
}
void Wrapper(int x, const string& s) {
  if (stoi(IntToString(x)) != x) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
