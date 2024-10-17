#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "space2D.hpp"

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    const int width = 200;
    const int height = 200;

    space2D space((double) width, (double) height);

    space.randomInitParticles(10000);

    const double infl_radius = 10.0;
    const double max_density = pow(infl_radius, 3.0);
    cv::Mat image(height, width, CV_8UC3, cv::Scalar(255, 255, 255));

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            double density = space.getDensity(x, y, infl_radius);
            std::cout << density << std::endl;

            // Normaliser la densité entre 0 et 1
            double normalized_density = density / max_density;

            // Limiter la normalisation entre 0 et 1
            if (normalized_density < 0) normalized_density = 0;
            if (normalized_density > 1) normalized_density = 1;

            // Calculer la couleur correspondante
            cv::Vec3b color; // BGR format
            color[0] = 0; // Blue channel
            color[1] = 0; // Green channel
            color[2] = static_cast<uchar>(255 * normalized_density); // Red channel

            // Affecter la couleur à l'image
            image.at<cv::Vec3b>(y, x) = color;
        }
    }


    // Afficher l'image
    cv::imshow("Heatmap de la Densité", image);

    // Attendre que l'utilisateur appuie sur une touche
    cv::waitKey(0);


    cv::destroyAllWindows();

    return 0;
}
