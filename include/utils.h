#ifndef UTILS_H
#define UTILS_H

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <iomanip> // for displaying json text
#include <set> // for storing valid curr in set. lg(N) search time.
#include <fstream> // for file I/O

#include "json.hpp"

using namespace std;
using json = nlohmann::json;


double getFxRate(string curr1, string curr2);

void takeInputsInUpper(string &curr1, string &curr2);

void fetchValidCurrency(set<string> &valid_curr);

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);


#endif
