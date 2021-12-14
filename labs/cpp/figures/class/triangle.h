//
// Created by Михаил on 09.02.2021.
//

#ifndef LABS_PROGRAMMING_TRIANGLE_H
#ifdef LABS_PROGRAMMING_POLYGON_H
#define LABS_PROGRAMMING_TRIANGLE_H

class Triangle : public Polygon {
private:
    // Checking if Polygon is Triangle
    static bool checkIfTriangle(const Point source[], const unsigned long long count) {
        if (count != 3) return false;

        for (int i = 0; i < count; ++i) {
            unsigned long long index = findDot(source, 0, i, source[i]);
            if (index != -1) return false;
            index = findDot(source, i + 1, count, source[i]);
            if (index != -1) return false;
        }
        return true;
    }

    static bool checkIfTriangle(const vector<Point> &source) {
        if (source.size() != 3) return false;

        for (int i = 0; i < source.size(); ++i) {
            unsigned long long index = findDot(source, 0, i, source[i]);
            if (index != -1) return false;
            index = findDot(source, i + 1, source.size(), source[i]);
            if (index != -1) return false;
        }
        return true;
    }

public:
    // Implementation of a virtual changeHeight at a parent class
    void changeHeight(const unsigned long long number, const double x, const double y) override {
        for (auto &i : shape)
            if (i.getX() == x && i.getY() == y) {
                std::cout << "New dot is already exists. Skipped.\n";
                return;
            }
        Polygon::changeHeight(number, x, y);
    }

    // Constructors
    Triangle() : Polygon() {
        shape = {};
    }

    explicit Triangle(const Point pts[], const unsigned long long count = 0) : Polygon(pts, count) {
        if (!checkIfTriangle(pts, count)) {
            shape = {};
            std::cout << "New shape is not a triangle. Skipped.\n";
            return;
        }
        for (int i = 0; i < count; ++i) {
            shape.push_back(pts[i]);
        }
    }

    explicit Triangle(const vector<Point> &pts) : Polygon(pts) {
        if (!checkIfTriangle(pts)) {
            shape = {};
            std::cout << "New shape is not a triangle. Skipped.\n";
            return;
        }
        shape = pts;
    }

    explicit Triangle(const Polygon &source) : Polygon(source) {
        shape = {};
        if (!checkIfTriangle(source.getPolygon())) {
            std::cout << "New shape is not a triangle. Skipped.\n";
            return;
        }
        shape = source.getPolygon();
    }

#ifdef LABS_PROGRAMMING_CORRECTPOLYGON_H
    explicit Triangle(const CorrectPolygon &source) {
        if (!checkIfTriangle(source.getPolygon())) {
            shape = {};
            std::cout << "New shape is not a triangle. Skipped.\n";
            return;
        }
        shape = source.getPolygon();
    }
#endif
    // Copy constructor
    Triangle(const Triangle &source) : Polygon(source) {
        shape = source.shape;
    }

    // Equal constructors
    Triangle &operator=(const vector<Point> &source) override {
        if (!checkIfTriangle(source)) {
            cout << "New shape is not a triangle. Skipped.\n";
            return *this;
        }
        *this = Polygon::operator=(source);
        return *this;
    }

    Triangle &operator=(const Triangle &source) {
        shape = source.shape;
        return *this;
    }

    Triangle &operator=(const Polygon &source) override {
        if (!checkIfTriangle(source.getPolygon())) {
            std::cout << "New shape is not a triangle. Skipped.\n";
            return *this;
        }
        shape = source.getPolygon();
        return *this;
    }

    ~Triangle() = default;
};

#endif //LABS_PROGRAMMING_POLYGON_H
#endif //LABS_PROGRAMMING_TRIANGLE_H
