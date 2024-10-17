#include <iostream>
#include <ostream>

#include "space2D.hpp"

#include <math.h>
#include <valarray>
#include <random>

using namespace std;

space2D::space2D(double length, double width) : length(length), width(width) {}

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

void space2D::randomInitParticles(int numParticles) {

    std::random_device rd;  // Initialise le générateur avec une source d'entropie
    std::mt19937 gen(rd());  // Mersenne Twister, un générateur de nombres aléatoires
    std::uniform_real_distribution<double> distr_x(0, this->length);
    std::uniform_real_distribution<double> distr_y(0, this->width);// Distribution uniforme entre a et b


    for (int i = 0; i < numParticles; i++) {
        particle newParticle(distr_x(gen), distr_y(gen));
        addParticle(newParticle);
    }
}

double space2D::getDensity(double x, double y, double infl_radius) const {
    double density = 0.0;
    for (int i = 0; i < particles.size(); i++) {
        double dst = particles[i].getDistance(x, y);
        density += particles[i].getInfluence(infl_radius, dst) * particles[i].getMass();
    }

    return density;
}

void space2D::addParticle(particle p) {
    particles.emplace_back(p);
}
