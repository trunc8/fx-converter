#include "include/utils.h"

template<typename T>
void printSet(set<T> const &s) {
  // for(auto i : s) makes a copy of each element of s
  for (auto const &i: s) {
    cout << i << " ";
  }
  cout << endl;
}

ostream &operator<<(ostream &os, const set<string> &s) {
  for (auto const &i: s) {
    os << i << " ";
  }
  os << "\n";
  return os;
}

int main(void) {
  cout << "---------Start of program----------\n\n\n";
  
  set<string> valid_curr {};
  fetchValidCurrency(valid_curr);
  
  // Using template function
  // printSet<string>(valid_curr);

  // Using operator overloading
  // cout << valid_curr;

  string curr1, curr2;
  curr1 = "USD";
  curr2 = "INR";
  
  takeInputsInUpper(curr1, curr2);

  // Using lambda expression
  auto validateCurrency = [valid_curr](const string curr) -> bool {
    return valid_curr.find(curr) != valid_curr.end();
  };

  if (!validateCurrency(curr1) || !validateCurrency(curr2)) {
    cout << "Please use valid currency code. Exiting.\n";
  }
  else {
    double fx_rate = getFxRate(curr1, curr2);
    cout << "Using FX rate: " << fx_rate << "\n\n";

    cout << "Input amount in " << curr1 << ": ";
    double amount;
    cin >> amount;
    cout << "Equivalent amount in " << curr2 << ": " << 
      amount*fx_rate << "\n";
  }



  cout << "\n\n---------End of program----------\n";

  return 0;
}
