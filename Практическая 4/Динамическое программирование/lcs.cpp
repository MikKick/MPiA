#include "lcs.h"
#include <algorithm>
#include <chrono>

std::string random_string(int size, const std::string& alphabet) {
    std::string result;
    auto random_char = [&]() { return alphabet[rand() % alphabet.size()]; };
    std::generate_n(std::back_inserter(result), size, random_char);
    return result;
}

string random_string(int size) {
    static const string alphabet = "abcdefghijklmnopqrstuvwxyz";
    return random_string(size, alphabet);
}

string lcs_native(const string &first, const string &second) 
{
    string result = "", str;
    int last_pos = -1;
    for (int i = 0; i < first.length(); i++)
    {
        for (int j = i; j < first.length(); j++)
            for (int k = 0; k < second.length(); k++)
                if (first[j] == second[k] && k > last_pos)
                {
                    str += first[j];
                    last_pos = k;
                    break;
                }
        if (str.length() > result.length())
            result = str;
        str = "";
        last_pos = -1;
    }
    return result;
}


string lcs(const string& first, const string& second)
{
    string result;
    const int N = first.size(), M = second.size();
    if (first.empty() || second.empty())
        return "";

    string** LCS = new string * [N + 1];
    for (int i = 0; i < N + 1; i++)
        LCS[i] = new string[M+1];
    for (int i = 1; i < N+1; i++)
        for (int j = 1; j < M+1; j++)
            if (first[i-1] == second[j-1])
                LCS[i][j] = LCS[i-1][j-1] + first[i-1];
            else
            {
                if (LCS[i - 1][j].length() > LCS[i][j - 1].length())
                    LCS[i][j] = LCS[i - 1][j];
                else
                    LCS[i][j] = LCS[i][j - 1];
            }
    return LCS[N][M];
}
