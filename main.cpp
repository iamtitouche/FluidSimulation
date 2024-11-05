#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QImage>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <ostream>

#include "headers/space2D.hpp"
#include "headers/utils.hpp"

class HeatmapWidget : public QWidget {
public:
    HeatmapWidget(const QImage &image, QWidget *parent = nullptr) 
        : QWidget(parent), heatmapImage(image) {
        setFixedSize(heatmapImage.size());
    }

protected:
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.drawImage(0, 0, heatmapImage);
    }

private:
    QImage heatmapImage;
};


int main(int argc, char *argv[]) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int width = 1000;
    int height = 500;
    const double infl_radius = 75.0;

    space2D space(static_cast<double>(width), static_cast<double>(height), infl_radius);

    space.randomInitParticles(400);
    space.sortParticles();

    cout << space.toString() << endl;


    // Initialize Qt application
    QApplication app(argc, argv);

    // Create an image to draw on
    QImage image(width, height, QImage::Format_RGB32);
    const double max_density = 2  / (M_PI * infl_radius);

    // Generate the heatmap
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            double density = space.getDensity(x, y);

            // Normalize density between 0 and 1
            double normalized_density = std::min(1.0, density / max_density);

            // Clamp normalized density between 0 and 1
            normalized_density = std::max(0.0, normalized_density);

            // Calculate the color corresponding
            QRgb color = qRgb(0, 0, static_cast<int>(255 * normalized_density));
            image.setPixel(x, y, color);
        }
    }

    // Create and show the heatmap widget
    HeatmapWidget heatmapWidget(image);
    heatmapWidget.setWindowTitle("Heatmap de la Densité");
    heatmapWidget.show();

    // Start the application event loop
    return app.exec();
}