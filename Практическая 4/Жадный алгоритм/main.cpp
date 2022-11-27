#define CATCH_CONFIG_RUNNER

#include "../catch.hpp"

#include "activities.h"
#define N 10

//The program of finding the largest subset of mutually compatible processes
//Difficulty of native method O(n^2*2^n)
//Difficulty of greedy method O(n*ln(n))

int main(int argc, char* argv[]) {
    setlocale(0, "");
    for (int n = 10; n <= N; n *=10)
    {
        cout << "Для N = " << n << endl;
        vector<Activity> test = random_sequence(n, 1, 100);
        auto t1 = std::chrono::high_resolution_clock::now();
        get_max_activities(test);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration<double>(t2 - t1).count();
        cout << "Жадный алгоритм: " << time << endl;
        t1 = std::chrono::high_resolution_clock::now();
        get_max_activities_native(test);
        t2 = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration<double>(t2 - t1).count();
        cout << "Примитивный способ: " << time << endl << endl;
        test.clear();
    }
    int result = Catch::Session().run(argc, argv);
    return result;
}