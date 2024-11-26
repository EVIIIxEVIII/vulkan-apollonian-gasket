#include "gasket.hpp"

#include <math.h>
#include <iostream>

const double EPSILON = 1e-4;
const double MIN_RADIUS = 1e-3;
const double MAX_RADIUS = 1;

void Gasket::initApollonianGasket() {
    Circle circle1{};
    circle1.radius = 1;
    circle1.center = complex(0.0, 0.0);
    circle1.curvature = -1;

    Circle circle2{};
    circle2.radius = 0.5;
    circle2.curvature = 1.0/0.5;
    circle2.center = complex(0.5, 0.0);

    Circle circle3{};
    circle3.radius = 0.5;
    circle3.curvature = 1.0/0.5;
    circle3.center = complex(-0.5, 0.0);

    // std::vector<Circle> randomCircles = generate2RandomTanCircles(circle1);

    allCircles.push_back(circle1);
    allCircles.push_back(circle2);
    allCircles.push_back(circle3);

    circlesQueue.push_back(std::vector<Circle> {circle1, circle2, circle3});

    circlesInLevel = {3};
}

void Gasket::generateApollonianGasket(int levels, bool useRandom) {
    int numOfCirc = static_cast<int>(allCircles.size());

    for (int i = 0; i < levels; i++) {
        std::vector<std::vector<Circle>> nextQueue;
        circlesInLevel.push_back(0);

        for (int j = 0; j < circlesQueue.size(); j++) {
            Circle c1 = circlesQueue[j][0];
            Circle c2 = circlesQueue[j][1];
            Circle c3 = circlesQueue[j][2];

            std::array<double, 2> nextCurvature = computeNextCurvature(c1, c2, c3);
            float radius4 = abs(1.0 / fabs(nextCurvature[0]));

            std::array<Circle, 4> newCircles = computeNextCircles(c1, c2, c3, nextCurvature);
            numOfCirc += newCircles.size();

            for (int z = 0; z < newCircles.size(); z++) {
                if (!isValidCircle(c1, c2, c3, newCircles[z])) continue;
                circlesInLevel[i+1]++;
                allCircles.push_back(newCircles[z]);

                std::vector<Circle> t1 {c1, c2, newCircles[z]};
                std::vector<Circle> t2 {c2, c3, newCircles[z]};
                std::vector<Circle> t3 {c1, c3, newCircles[z]};

                nextQueue.push_back(t1);
                nextQueue.push_back(t2);
                nextQueue.push_back(t3);
            }
        }

        circlesQueue = nextQueue;
    }

    std::cout << "Number of circles generated: " << numOfCirc << '\n';
    std::cout << "Number of circles in vec: " << allCircles.size() << '\n';
}

std::array<double, 2> Gasket::computeNextCurvature(const Circle circle1, const Circle circle2, const Circle circle3) {
    float k1 = circle1.curvature;
    float k2 = circle2.curvature;
    float k3 = circle3.curvature;

    float sum = k1 + k2 + k3;
    float squareRoot = 2*sqrt(fabs(k1*k2 + k2*k3 + k1*k3));

    return std::array<double, 2>{sum + squareRoot, sum - squareRoot};
}

std::array<Circle, 4> Gasket::computeNextCircles(const Circle c1, const Circle c2, const Circle c3, const std::array<double, 2> k4) {
    double k1 = c1.curvature;
    double k2 = c2.curvature;
    double k3 = c3.curvature;

    complex z1 = c1.center;
    complex z2 = c2.center;
    complex z3 = c3.center;

    complex zk1 = z1 * k1;
    complex zk2 = z2 * k2;
    complex zk3 = z3 * k3;

    complex sum = zk1 + zk2 + zk3;
    complex root = (zk1*zk2 + zk2*zk3 + zk1*zk3).sqrt()*2.0;

    complex center_1 = (sum + root)*(1.0 / k4[0]);
    complex center_2 = (sum - root)*(1.0 / k4[0]);
    complex center_3 = (sum + root)*(1.0 / k4[1]);
    complex center_4 = (sum - root)*(1.0 / k4[1]);

    Circle circle_1{};
    circle_1.curvature = k4[0];
    circle_1.center = center_1;
    circle_1.radius = 1.0 / k4[0];

    Circle circle_2{};
    circle_2.curvature = k4[0];
    circle_2.center = center_2;
    circle_2.radius = 1.0 / k4[0];

    Circle circle_3{};
    circle_3.curvature = k4[1];
    circle_3.center = center_3;
    circle_3.radius = 1.0 / k4[1];

    Circle circle_4{};
    circle_4.curvature = k4[1];
    circle_4.center = center_4;
    circle_4.radius = 1.0 / k4[1];

    return std::array<Circle, 4> {
        circle_1,
        circle_2,
        circle_3,
        circle_4
    };
}

double Gasket::computeDistance(const Circle c1, const Circle c2) const {
    return sqrt(
        (c1.center.getReal() - c2.center.getReal()) *
        (c1.center.getReal() - c2.center.getReal())

        +

        (c1.center.getImaginary() - c2.center.getImaginary()) *
        (c1.center.getImaginary() - c2.center.getImaginary())
    );
}

bool Gasket::isValidCircle(const Circle c1, const Circle c2, const Circle c3, const Circle newCircle) {
    // an interesting thing is that 2 circles out of 4 will always have a wrong position
    // because the algo is creating 2 inside circles and 2 outside circles
    if (newCircle.radius > MAX_RADIUS)  return false;

    for (int i = 0; i < allCircles.size(); i++) {
        double distance = computeDistance(newCircle, allCircles[i]);
        if (distance < MIN_RADIUS) {
            return false;
        }
    }

    return  checkPositionValid(c1, newCircle) &&
            checkPositionValid(c2, newCircle) &&
            checkPositionValid(c3, newCircle);
}

bool Gasket::checkPositionValid(Circle c1, Circle c2) {
    double d = computeDistance(c1, c2);

    if (d - (c1.radius + c2.radius) < EPSILON) {
        return true;
    }

    if (d - fabs(c1.radius - c2.radius) < EPSILON) {
        return true;
    }

    return false;
}
