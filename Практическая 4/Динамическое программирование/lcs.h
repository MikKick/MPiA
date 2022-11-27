#pragma once

#include <string>
#include "iostream"
using namespace std;
string random_string(int size);
string random_string(int size, const std::string& alphabet);

string lcs_native(const std::string &first, const std::string &second);
string lcs(const string& first, const string& second);