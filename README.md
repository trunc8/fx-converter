# fx-converter

The sole objective of this project is to learn the practical use of various C++ features.  
Besides serving as a handy reference for myself, the motive is to present these usages out in the wild. I hope these usages can be easily understood by new programmers.


### How to use?
```zsh
git clone https://github.com/trunc8/fx-converter.git
cd fx-converter
make test
```


### Notes
- Command-line instructions are designed for Linux users
- `#include <iostream>; using namespace std;` applies to all snippets below


### Table of Contents
- [Fetch data using web API](#fetch-data-using-web-api)
- [Fetch data from file](#fetch-data-from-file)
- [Parse json](#parse-json)
- [Operator Overloading](#operator-overloading)
- [Function Template](#function-template)
- [Lambda Function](#lambda-function)


### Fetch data using web API
Ensure that `curl` library is installed in your system. We ultimately want to include the `curl.h` header file in our code. You can verify if it's available by checking if the directory `/usr/include/x86_64-linux-gnu/curl` is present. While compiling, add `-lcurl` at the end of the command:
```zsh
g++ -Wall -o fx main.cpp utils.cpp -lcurl
```

Relevant snippets from the project code:
```cpp

#include <curl/curl.h>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

double getFxRate(string curr1, string curr2) {
  ...
  string url_string = "https://free.currconv.com/api/v7/convert?q="
    +curr1+"_"+curr2+"&compact=ultra&apiKey=b0591706cb6a10f406d5";

  CURL *curl;
  string readBuffer;

  curl = curl_easy_init();

  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url_string.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
  }
  ...
}
```


### Fetch data from file
We have `currency_codes.txt` as a text file in the same directory.  
Relevant snippets from the project code:
```cpp
#include <fstream>

void fetchValidCurrency(set<string> &valid_curr) {
  if (ifstream input{"currency_codes.txt"}) {
    
    while (input) {
      string line;
      getline(input, line);
      
      if (line.empty())
        continue;
      
      valid_curr.insert(line);
    }
  }
}
```


### Parse json
We shall use [nlohmann's json library](https://github.com/nlohmann/json). Head to their [GitHub releases](https://github.com/nlohmann/json/releases). Scroll down to their latest assets. Download the `json.hpp` file to the `include` directory of your project.  
Relevant snippets from the project code:
```cpp
#include "json.hpp"
using json = nlohmann::json;

double getFxRate(string curr1, string curr2) {
  double _fx_rate = 0;
  
  ... // string readBuffer contains json text in string format

  // Using nlohmann json
  json fx_json = json::parse(readBuffer);
  // Pretty print in json format
  // cout << setw(4) << fx_json << std::endl;
  _fx_rate = fx_json.at(curr1+"_"+curr2);

  return _fx_rate;
}
```


### Operator Overloading
Relevant snippets from the project code:
```cpp
ostream &operator<<(ostream &os, const set<string> &s) {
  for (auto const &i: s) {
    os << i << " ";
  }
  os << "\n";
  return os;
}

```


### Function Template
Relevant snippets from the project code:
```cpp
template<typename T>
void printSet(set<T> const &s) {
  // for(auto i : s) makes a copy of each element of s
  for (auto const &i: s) {
    cout << i << " ";
  }
  cout << endl;
}
```


### Lambda Function
Relevant snippets from the project code:
```cpp
int main(void) {
  ...

  // Using lambda expression
  auto validateCurrency = [valid_curr](string curr) -> bool {
    return valid_curr.find(curr) != valid_curr.end();
  };

  if (!validateCurrency(curr1) || !validateCurrency(curr2)) {
    cout << "Please use valid currency code. Exiting.\n";
  }
  else {
    ...
  }
  ...
}
```



### Author(s)

* **Siddharth Saha** - [trunc8](https://github.com/trunc8)

<p align='center'>Created with :heart: by <a href="https://www.linkedin.com/in/sahasiddharth611/">Siddharth</a></p>
