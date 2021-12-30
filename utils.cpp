#include "include/utils.h"

double getFxRate(string curr1, string curr2) {
  double _fx_rate = 0;
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

  // Using nlohmann json
  json fx_json = json::parse(readBuffer);
  // Pretty print in json format
  // cout << setw(4) << fx_json << std::endl;
  _fx_rate = fx_json.at(curr1+"_"+curr2);

  return _fx_rate;
}


void takeInputs(string &curr1, string &curr2) {
  cout << "Please enter currency code 1: ";
  cin >> curr1;
  cout << "Please enter currency code 2: ";
  cin >> curr2;
}


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


size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
