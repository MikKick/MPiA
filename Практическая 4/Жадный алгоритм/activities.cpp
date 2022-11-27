#include "activities.h"


vector<Activity> random_sequence(int size, int min, int max) {
    int i = 0;
    default_random_engine generator;
    uniform_int_distribution<int> distribution(min, max);
    vector<Activity> result;
    Activity point;
    while(i < size) {
        point.start = distribution(generator);
        point.finish = distribution(generator);
        if (point.finish > point.start)
        {
            result.push_back(point);
            i++;
        }
    }
    return result;
}


vector<Activity> get_max_activities_native(const std::vector<Activity> &activities) {

    if (activities.empty())
        return {};

    vector<Activity> result, subset;
    bool flag = false;
    long int M = pow(2, activities.size());
    for (long int i = 0; i < M; i++)
    {
        int a = i;
        for (int j = 0; j < activities.size(); j++)
        {
            if (a % 2)
                subset.push_back(activities[j]);
            a /= 2;
        }
        
        if (subset.empty())
            continue;

        for (int k = 0; k < subset.size() - 1; k++)
            for (int l = k + 1; l < subset.size(); l++)
                if (subset[k].finish > subset[l].start && subset[l].finish > subset[k].start)
                {
                    flag = true;
                    break;
                }
        if (subset.size() > result.size() && !flag)
            result = subset;
        flag = false;
        subset.clear();
    }
    return result;
}

vector<Activity> get_max_activities(const std::vector<Activity>& activities)
{
    if (activities.empty())
        return {};
    vector<Activity> sorted{ activities }, result, result_1;
    sort(sorted.begin(), sorted.end(), [](Activity a, Activity b) {return a.finish < b.finish;});
    result.push_back(sorted[0]);
    for (int i = 1; i < sorted.size(); i++)
        if (!(sorted[0].finish > sorted[i].start && sorted[i].finish > sorted[0].start))
        {
            sorted.erase(sorted.begin(), sorted.begin() + i);
            result_1 = get_max_activities(sorted);
            result.insert(result.end(), result_1.begin(), result_1.end());
            break;
        }
    return result;
}
