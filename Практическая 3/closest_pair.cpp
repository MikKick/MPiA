#include "closest_pair.h" ЛОХ

#include <stdexcept>

using namespace std;

pair<Point, Point> closest_pair_between(const std::vector <Point>& PLeft, const std::vector <Point>& PRight, double d)
{
	vector <Point> PStripe;
	pair<Point, Point> result = make_pair(PLeft.back(), PRight.front());
	double xm = (PLeft.back().x + PRight.front().x) / 2;
	for (const auto& point : PLeft)
		if (abs(xm - point.x) < d)
			PStripe.push_back(point);
	for (const auto& point : PRight) 
		if (abs(xm - point.x) < d) 
			PStripe.push_back(point);
	sort(PStripe.begin(), PStripe.end(), [](Point p1, Point p2) {return p1.y < p2.y;});
	for (int i = 0; i < PStripe.size(); i++)
		for (int j = i - 1; j >= 0; j--)
		{
			if (abs(PStripe[i].y - PStripe[j].y) > d)
				break;
			if (PStripe[i].distance(PStripe[j]) < result.first.distance(result.second))
				result = make_pair(PStripe[i], PStripe[j]);
		}
	return result;
}

pair<Point, Point> closest_pair_trivial(const std::vector<Point> &points) {
	if (points.size() < 2) {
		throw invalid_argument("Not enough points");
	}
	pair<Point, Point> result;
	auto min{ std::numeric_limits<double>::infinity() };
	for (int i = 0; i < points.size() - 1; i++)
		for(int j = i+1; j < points.size(); j++)
			if (points[i].distance(points[j]) < min)
			{
				min = points[i].distance(points[j]);
				result = make_pair(points[i], points[j]);
			}
	return result;
}

pair<Point, Point> closest_pair(const std::vector<Point>& points) {
	double d_pl, d_pr, d_pb, min_p;
	if (points.size() < 2) {
		throw invalid_argument("Not enough points");
	}
	if (points.size() <= 3) {
		return closest_pair_trivial(points);
	}
	vector <Point> vec(points);
	sort(vec.begin(), vec.end(), [](Point p1, Point p2) {return p1.x < p2.x;});
	vector <Point> PLeft(vec.begin(), vec.begin() + vec.size() / 2), PRight(vec.begin() + vec.size() / 2, vec.end());
	pair<Point, Point> pl = closest_pair(PLeft), pr = closest_pair(PRight), pb, result;
	double d = min(pl.first.distance(pl.second), pl.first.distance(pl.second));
	pb = closest_pair_between(PLeft, PRight, d);
	d_pl = pl.first.distance(pl.second);
	d_pr = pr.first.distance(pr.second);
	d_pb = pb.first.distance(pb.second);
	if (d_pl >= d_pr && d_pr <= d_pb)
		result = pr;
	else if (d_pr >= d_pl && d_pl <= d_pb)
		result = pl;
	else
		result = pb;
	return result;
}
