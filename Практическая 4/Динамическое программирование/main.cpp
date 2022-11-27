#define CATCH_CONFIG_RUNNER

#include "../catch.hpp"

#include "lcs.h"
#define N 600

//The program of finding the greatest common subsequence of two strings
//Difficulty of native method O(2^n*m)
//Difficulty of dynamic method O(n*m)


int main(int argc, char* argv[]) {
    setlocale(0, "");
    string str_1, str_2;
    int size;
    for (int n = 10; n <= N; n *= 5)
    {
        size = rand() % n*2 + 1;
        str_1 = random_string(n);
        str_2 = random_string(size);
        cout << "Размер первой строки = " << n << " Размер второй строки = " << size << endl;
        auto t1 = std::chrono::high_resolution_clock::now();
        lcs_native(str_1, str_2);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration<double>(t2 - t1).count();
        cout << "Примитивный способ: " << time << endl;
        t1 = std::chrono::high_resolution_clock::now();
        lcs(str_1, str_2);
        t2 = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration<double>(t2 - t1).count();
        cout << "Динамический способ: " << time << endl << endl;
    }
    int result = Catch::Session().run(argc, argv);
    return result;
}
