#include "closest_pair.h"
#define CATCH_CONFIG_RUNNER
#include "../catch.hpp"
#define N 1000
using namespace std;

//The program of searching two closest points in space
//Difficulty of native method O(N^2)
//Difficulty of improved method O(n*log^2(n))

vector<Point> random_sequence(int size, int min, int max) {
    default_random_engine generator;
    uniform_int_distribution<int> distribution(min, max);
    vector<Point> result;
    Point point;
    for (int i = 0; i < size; i++) {
        point.x = distribution(generator);
        point.y = distribution(generator);
        result.push_back(point);
    }
    return result;
}


int main(int argc, char **argv) {
    setlocale(0, "");
    vector<Point> random_points;
    pair<Point, Point> result_1;
    for (int n = 10; n <= N; n *= 10)
    {
        cout << "Для N = " << n << endl;
        random_points = random_sequence(n, -100, 100);
        auto t1 = chrono::high_resolution_clock::now();
        result_1 = closest_pair(random_points);
        auto t2 = chrono::high_resolution_clock::now();
        chrono::duration<double> time = (t2 - t1);
        cout << "Разделяй и властвуй: " << time.count() << endl;
        t1 = chrono::high_resolution_clock::now();
        result_1 = closest_pair_trivial(random_points);
        t2 = chrono::high_resolution_clock::now();
        time = (t2 - t1);
        cout << "Примитивный способ: " << time.count() << endl;
        random_points.clear();
    }
    int result = Catch::Session().run(argc, argv);
    return result;
}
