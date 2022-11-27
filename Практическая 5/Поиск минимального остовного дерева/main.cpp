#define CATCH_CONFIG_RUNNER

#include "../catch.hpp"
#include <ctime>
#include "min_spanning_tree.h"
const int N = 1000;

int main(int argc, char* argv[]) {
    setlocale(0, "");
    Graph g;
    srand(time(0));
    for (int n = 10; n <= N; n *= 10)
    {
        cout << "Для N = " << n << endl;
        g.random_graph(n);
        auto t1 = std::chrono::high_resolution_clock::now();
        auto a = min_spanning_tree(g);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration<double>(t2 - t1).count();
        cout << "Время Прима: " << time << endl;
        g.clear(n);
    }
    for (int n = 15000; n <= 20000; n +=5000)
    {
        cout << "Для N = " << n << endl;
        g.random_graph(n);
        auto t1 = std::chrono::high_resolution_clock::now();
        auto a = min_spanning_tree(g);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration<double>(t2 - t1).count();
        cout << "Время Прима: " << time << endl;
        g.clear(n);
    }


    int result = Catch::Session().run(argc, argv);
    return result;
}
