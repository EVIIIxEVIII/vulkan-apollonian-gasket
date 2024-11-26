#ifndef GASKET_HPP
#define GASKET_HPP

#include "./complex.hpp"
#include <vector>
#include <array>
#include <glm/vec3.hpp>

struct Circle {
    Circle(): center(0.0, 0.0), radius(0.0), curvature(0.0) {}
    complex center;
    double curvature;
    double radius;
};

class Gasket {
public:
    Gasket() { initApollonianGasket(); };

    void initApollonianGasket();
    void generateApollonianGasket(int levels, bool useRandom);

    const std::vector<Circle>& getAllCircles() const {
        return allCircles;
    }

    const std::vector<glm::vec3>& getCircleColors() const {
        return circleColors;
    }

    const std::vector<int>& getCirclesInLevel() const {
        return circlesInLevel;
    }

private:
    std::array<Circle, 4> computeNextCircles(const Circle c1, const Circle c2, const Circle c3, const std::array<double, 2> k4);
    std::array<double, 2> computeNextCurvature(const Circle circle1, const Circle circle2, const Circle circle3);

    bool isValidCircle(const Circle c1, const Circle c2, const Circle c3, const Circle newCircle);

    double computeDistance(const Circle c1, const Circle c2) const;
    bool checkPositionValid(const Circle c1, const Circle c2);

    std::vector<std::vector<Circle>> circlesQueue;
    std::vector<Circle> allCircles;

    std::vector<int> circlesInLevel;

    // colors repeated twice because I want it like this
    std::vector<glm::vec3> circleColors {
        {1.0f, 0.0f, 0.0f}, // Red
        {0.0f, 1.0f, 0.0f}, // Green
        {0.0f, 0.0f, 1.0f}, // Blue
        {1.0f, 1.0f, 0.0f}, // Yellow
        {0.0f, 1.0f, 1.0f}, // Cyan
        {1.0f, 0.0f, 1.0f}, // Magenta
        {1.0f, 0.5f, 0.0f}, // Orange
        {0.5f, 0.0f, 1.0f}, // Purple
        {0.0f, 0.5f, 0.5f}, // Teal
        {0.5f, 0.5f, 0.0f}, // Olive
        {0.8f, 0.0f, 0.4f}, // Deep Pink
        {0.2f, 0.8f, 0.2f}, // Lime Green
        {0.2f, 0.2f, 0.8f}, // Soft Blue
        {0.9f, 0.7f, 0.3f}, // Gold
        {0.6f, 0.3f, 0.1f}, // Brown
        {1.0f, 0.0f, 0.0f}, // Red
        {0.0f, 1.0f, 0.0f}, // Green
        {0.0f, 0.0f, 1.0f}, // Blue
        {1.0f, 1.0f, 0.0f}, // Yellow
        {0.0f, 1.0f, 1.0f}, // Cyan
        {1.0f, 0.0f, 1.0f}, // Magenta
        {1.0f, 0.5f, 0.0f}, // Orange
        {0.5f, 0.0f, 1.0f}, // Purple
        {0.0f, 0.5f, 0.5f}, // Teal
        {0.5f, 0.5f, 0.0f}, // Olive
        {0.8f, 0.0f, 0.4f}, // Deep Pink
        {0.2f, 0.8f, 0.2f}, // Lime Green
        {0.2f, 0.2f, 0.8f}, // Soft Blue
        {0.9f, 0.7f, 0.3f}, // Gold
        {0.6f, 0.3f, 0.1f}, // Brown
    };
};
#endif
