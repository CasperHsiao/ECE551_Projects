#include "circle.hpp"

#include <cmath>
#include <cstdio>
using namespace std;

Circle::Circle(Point center, double radius) : center(center), radius(radius) {
}

void Circle::move(double dx, double dy) {
  center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double dist = this->center.distanceFrom(otherCircle.center);
  double r = this->radius;
  double R = otherCircle.radius;
  if (dist >= r + R) {
    return 0.0;
  }
  double min = r;
  if (R < r) {
    min = R;
  }
  if (abs(r - R) >= dist) {
    return acos(-1.0) * pow(min, 2);
  }
  double t1 = acos((dist * dist + r * r - R * R) / (2 * dist * r));
  double t2 = acos((dist * dist + R * R - r * r) / (2 * dist * R));
  return r * r * t1 + R * R * t2 - r * dist * sin(t1);
}
