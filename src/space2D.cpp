#include <iostream>
#include <ostream>

#include "../headers/space2D.hpp"
#include "../headers/utils.hpp"

#include <math.h>
#include <cmath>
#include <valarray>
#include <random>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <QDebug>


using namespace std;

space2D::space2D(double length, double width, double infl_radius)
    : length(length), width(width), infl_radius(infl_radius) {

    // Calcul du nombre de subdivisions
    int size = static_cast<int>(length / infl_radius);
    if (fmod(length, infl_radius) != 0) size++;

    this->subdivPerLine = size;

    int height_size = static_cast<int>(width / infl_radius);
    if (fmod(width, infl_radius) != 0) height_size++;

    size *= height_size;
    numberSubdiv = size;

    // Allocation du tableau de subdivisions
    sortedParticles = std::make_unique<std::vector<particle*>[]>(size);
}


space2D::space2D(double length, double width, double infl_radius, double dst) : length(length), width(width), infl_radius(infl_radius) {
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

double space2D::getDensity(double x, double y) const {
    int zone = (int) (x / infl_radius);
    zone += (int) (y / infl_radius) * subdivPerLine;

    double density = 0.0;

    for (int i : getAdjacentZones(zone, subdivPerLine, numberSubdiv)) {
        for (particle *p : sortedParticles[i]) {
            double dst = p->getDistance(x, y);
            density += 2 * p->getInfluence(infl_radius, dst) * p->getMass() / (M_PI * pow(infl_radius, 4));
        }
    }
    
    return density;
}

double space2D::getDensity(double x, double y) const {
    int zone = (int) (x / infl_radius);
    zone += (int) (y / infl_radius) * subdivPerLine;

    double density = 0.0;

    for (int i : getAdjacentZones(zone, subdivPerLine, numberSubdiv)) {
        for (particle *p : sortedParticles[i]) {
            double dst = p->getDistance(x, y);
            density += 2 * p->getInfluence(infl_radius, dst) * p->getMass() / (M_PI * pow(infl_radius, 4));
        }
    }

    return density;
}


void space2D::addParticle(particle p) {
    particles.emplace_back(p);
}


void space2D::sortParticles() {
    if (particles.size() > 0 && particles[0].getZone() >= 0) {
        for (int i = 0; i < numberSubdiv; i++) {
            // Utilisation d'une référence pour éviter la copie
            auto& zone = sortedParticles[i];
            for (auto it = zone.begin(); it != zone.end(); /* pas d'incrément ici */) {
                particle *p = *it;
                double x = p->getX();
                double y = p->getY();

                int newZone = static_cast<int>(x / infl_radius);
                newZone += static_cast<int>(y / infl_radius) * subdivPerLine;

                if (p->getZone() != newZone) {
                    // Supprime le pointeur `p` de la zone actuelle
                    it = zone.erase(it);
                    // Mise à jour de la zone de la particule
                    p->setZone(newZone);
                    // Ajout de `p` à la nouvelle zone
                    sortedParticles[newZone].push_back(p);
                } else {
                    // Passe à la particule suivante si elle reste dans la même zone
                    ++it;
                }
            }
        }
    } else {
        for (auto& p : particles) {
            double x = p.getX();
            double y = p.getY();

            int newZone = static_cast<int>(x / infl_radius);
            newZone += static_cast<int>(y / infl_radius) * subdivPerLine;

            p.setZone(newZone);
            sortedParticles[newZone].push_back(&p);
        }
    }
}





string space2D::toString() const {
    ostringstream oss;

    oss << "Space 2D :" << std::endl;
    oss << "  length : " << length << std::endl;
    oss << "  width : " << width << std::endl;
    oss << "  infl_radius : " << infl_radius << std::endl;
    oss << "  subdivPerLine : " << subdivPerLine << std::endl;
    oss << "  numberSubdiv : " << numberSubdiv << std::endl;

    oss << "  Number of Particles : " << particles.size() << std::endl;

    for (int i = 0; i < numberSubdiv; i++) {
        oss << "  Zone Number : " << i << std::endl;
        oss << "    Number of particles : " << sortedParticles[i].size() << std::endl;
        for (particle *p : sortedParticles[i]) {
            oss << p->toString() << std::endl;
        }
    }

    return oss.str();
}

