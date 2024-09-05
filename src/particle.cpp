#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

#include "particle.hpp"

using namespace std;

particle::particle(double x, double y) : x(x), y(y) {}

double particle::getX() const {
    return x;
}

double particle::getY() const {
    return y;
}

void particle::setX(double x) {
    this->x = x;
}

void particle::setY(double y) {
    this->y = y;
}

string particle::toString() const {
    ostringstream oss;

    oss << "Particle:" << std::endl;
    oss << "  x: " << x << std::endl;
    oss << "  y: " << y << std::endl;

    return oss.str();
}

double particle::getInfluence(double radius, double dst) {
    return pow(max(0.0, radius - dst), 3);
}
