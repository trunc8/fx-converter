# fx-converter

The sole objective of this project is to learn the practical use of various C++ features.  
Besides serving as a handy reference for myself, the motive is to present these usages out in the wild. I hope these usages can be easily understood by new programmers.


### How to use?
```sh
git clone https://github.com/trunc8/fx-converter.git
cd fx-converter
# To run the project
make test

# To debug the project
make debug
```


### Notes
- Command-line instructions are designed for Linux users
- `#include <iostream>; using namespace std;` applies to all snippets below


### Table of Contents
- [Makefile](#makefile)
- [Fetch data using web API](#fetch-data-using-web-api)
- [Fetch data from file](#fetch-data-from-file)
- [Parse json](#parse-json)
- [Operator Overloading](#operator-overloading)
- [Function Template](#function-template)
- [Lambda Function](#lambda-function)
- [Debug](#debug)


### Makefile
For a quick guide on `make` and `Makefile`, please refer to my [blog](https://trunc8.github.io/2021/04/03/tut-makefile). The `Makefile` in this project presents an easier example:
```make
build: clean
  g++ -Wall -o fx main.cpp utils.cpp -lcurl

clean:
  rm -rf fx

test: build
  ./fx 
```
For some intuition of the above code, running `make test` on the terminal:

- first runs `clean`, i.e., the command `rm -rf fx`
- then runs `build`, i.e., the command `g++ -Wall -o fx main.cpp utils.cpp -lcurl`
- finally runs `./fx`

So in a single terminal command, we removed the stale output file, compiled the source code, and ran the executable.

### Fetch data using web API
Ensure that `curl` library is installed in your system. We ultimately want to include the `curl.h` header file in our code. You can verify if the header file is available by checking if the directory `/usr/include/x86_64-linux-gnu/curl` is present. While compiling, add `-lcurl` at the end of the command. 

Relevant lines from `Makefile`:
```make
build: clean
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


### Debug
Ensure that `gdb` is installed in your system. We need to pass an additional flag (`-g`) while compiling in order to use gdb later. 

Relevant lines from `Makefile`:
```make
debug: clean
	g++ -Wall -g -o fx main.cpp utils.cpp -lcurl
	gdb -tui fx
```

Useful gdb shortcuts:

- q: quit
- b: breakpoint (on line number)
- r: run (program)
- l: list (print source code till that point)
- p: print (variable)
- c: continue (until next breakpoint)
- n: next (line in function)
- s: step (next innermost instruction)
- fin: finish (continue until just after current function returns)
- ENTER: repeat previous command
- bt: backtrack (backtrace stack frames)


### Acknowledgement
- [gdb debugging](https://www.thegeekstuff.com/2010/03/debug-c-program-using-gdb/)


### Author(s)

* **Siddharth Saha** - [trunc8](https://github.com/trunc8)

<p align='center'>Created with :heart: by <a href="https://www.linkedin.com/in/sahasiddharth611/">Siddharth</a></p>
