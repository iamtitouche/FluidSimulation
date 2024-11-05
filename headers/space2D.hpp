#ifndef SPACE2D_HPP
#define SPACE2D_HPP

#include <vector>
#include <memory>

#include "particle.hpp"


using namespace std;

class space2D {
public:
    space2D(double length, double width, double infl_radius);
    space2D(double length, double width, double infl_radius, double dst);
    void evenlyInitParticles(double dst);
    void randomInitParticles(int numParticles);
    void addParticle(particle p);
    vector<particle>& getParticles();
    [[nodiscard]] double getDensity(double x, double y) const;
    void sortParticles();
	[[nodiscard]] string toString() const;
private:
    const double length, width;
    const double infl_radius;
    vector<particle> particles;
	std::unique_ptr<std::vector<particle*>[]> sortedParticles;
	int subdivPerLine;
	int numberSubdiv;
};


#endif //SPACE2D_HPP
