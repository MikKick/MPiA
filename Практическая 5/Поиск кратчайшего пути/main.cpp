#define CATCH_CONFIG_RUNNER

#include "../catch.hpp"
#include <ctime>
#include "shortest_path.h"
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
        shortest_path(g, 0, n-1);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto time = std::chrono::duration<double>(t2 - t1).count();
        cout << "Время: " << time << endl;

        t1 = std::chrono::high_resolution_clock::now();
        auto a = shortest_path(g, rand() % n, rand() % n);
        t2 = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration<double>(t2 - t1).count();
        cout << "Время: " << time << endl;

        t1 = std::chrono::high_resolution_clock::now();
        shortest_path(g, rand() % n, rand() % n);
        t2 = std::chrono::high_resolution_clock::now();
        time = std::chrono::duration<double>(t2 - t1).count();
        cout << "Время: " << time << endl;
        g.clear(n);
        cout << endl;
    }

    int result = Catch::Session().run(argc, argv);
    return result;
}
