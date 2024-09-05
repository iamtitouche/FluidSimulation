#include <iostream>
#include <ostream>

#include "space2D.hpp"

using namespace std;

space2D::space2D(double length, double width, double dst) : length(length), width(width) {
    this->evenlyInitParticles(dst);
}

vector<particle>& space2D::getParticles() {
    return particles;
}

void space2D::evenlyInitParticles(double dst) {
    if (this->length / dst < 1.0 || this->width / dst < 1.0) {
        cerr << "Error: space dimensions are too small or distance required between particle is too large" << endl;
    }

    particles.clear();

    for (int i = 1; i <= (int) (this->length / dst); i++) {
        for (int j = 1; j <= (int) (this->width / dst); j++) {
            double x = i * dst;
            double y = j * dst;
            particles.emplace_back(x, y);
        }
    }
}
