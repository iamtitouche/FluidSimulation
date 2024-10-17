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

double particle::getMass() const {
    return mass;
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

double particle::getInfluence(double max_radius, double dst) {
    return pow(max(max_radius - dst, 0.0), 3);
}

double particle::getDistance(double x, double y) const {
    return sqrt(pow(x - this->x, 2) + pow(y - this->y, 2));
}

