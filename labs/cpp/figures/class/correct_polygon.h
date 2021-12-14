//
// Created by Михаил on 09.02.2021.
//

#ifndef LABS_PROGRAMMING_CORRECTPOLYGON_H
#ifdef LABS_PROGRAMMING_POLYGON_H

#define LABS_PROGRAMMING_CORRECTPOLYGON_H

class CorrectPolygon : public Polygon {
private:
    // Checking if a Polygon is a Correct Polygon
    static bool checkIfCorrect(const Point source[], const unsigned long long count) {
        if (count < 3) return false;

        for (int i = 0; i < count; ++i) {
            unsigned long long index = findDot(source, 0, i, source[i]);
            if (index != -1) return false;
            index = findDot(source, i + 1, count, source[i]);
            if (index != -1) return false;
        }

        double length = 0;
        for (int i = 0; i < count - 1; ++i) {
            double tmp = std::sqrt((source[i + 1].getX() - source[i].getX())
                                   * (source[i + 1].getX() - source[i].getX())
                                   + (source[i + 1].getY() - source[i].getY())
                                     * (source[i + 1].getY() - source[i].getY()));
            if (i == 0) {
                length = tmp;
                continue;
            }
            if (length != tmp) return false;
        }
        return true;
    }

    static bool checkIfCorrect(const vector<Point> &source) {
        if (source.size() < 3) return false;

        for (int i = 0; i < source.size(); ++i) {
            unsigned long long index = findDot(source, 0, i, source[i]);
            if (index != -1) return false;
            index = findDot(source, i + 1, source.size(), source[i]);
            if (index != -1) return false;
        }

        double length = 0;
        for (int i = 0; i < source.size(); ++i) {
            double tmp = std::sqrt((source[i + 1].getX() - source[i].getX())
                                   * (source[i + 1].getX() - source[i].getX())
                                   + (source[i + 1].getY() - source[i].getY())
                                     * (source[i + 1].getY() - source[i].getY()));
            if (i == 0) {
                length = tmp;
                continue;
            }
            if (length != tmp) return false;
        }
        return true;
    }

public:
    // Implementation of a virtual changeHeight function at Parent class
    void changeHeight(const unsigned long long number, const double x, const double y) override {
        std::cout << "Can't reshape a correct polygon with 1 height.";
    }

    void changeSize(const double multiplier) {
        if (multiplier == 0) {
            std::cout << "Can't reshape a correct polygon with multiplier = 0. Skipped.\n";
            return;
        }
        for (auto & i : shape) {
            i.setX(i.getX() * multiplier);
            i.setY(i.getY() * multiplier);
        }
    }

    // Constructors
    CorrectPolygon() : Polygon() {
        shape = {};
    }

    explicit CorrectPolygon(const Point pts[], const unsigned long long count = 0) : Polygon(pts, count) {
        if (!checkIfCorrect(pts, count)) {
            std::cout << "New shape is not a triangle. Skipped.\n";
            return;
        }
        for (int i = 0; i < count; ++i) {
            shape.push_back(pts[i]);
        }
    }

    explicit CorrectPolygon(const vector<Point> &pts) : Polygon(pts) {
        if (!checkIfCorrect(pts)) {
            std::cout << "New shape is not a correct polygon. Skipped.\n";
            return;
        }
        shape = pts;
    }

    explicit CorrectPolygon(const Polygon &source) : Polygon(source) {
        if (!checkIfCorrect(source.getPolygon())) {
            std::cout << "New shape is not a correct polygon. Skipped.\n";
            return;
        }
        shape = source.getPolygon();
    }

    // Copy constructor
    CorrectPolygon(const CorrectPolygon &source) : Polygon(source) {
        shape = source.getPolygon();
    }

    CorrectPolygon &operator=(const vector<Point> &source) override {
        if (!checkIfCorrect(source)) {
            cout << "New shape is not a correct polygon. Skipped.\n";
            return *this;
        }
        *this = Polygon::operator=(source);
        return *this;
    }

    CorrectPolygon &operator=(const Polygon &source) override {
        if (!checkIfCorrect(source.getPolygon())) {
            std::cout << "New shape is not a correct polygon. Skipped.\n";
            return *this;
        }
        shape = source.getPolygon();
        return *this;
    }

    CorrectPolygon &operator=(const CorrectPolygon &source) {
        if (!checkIfCorrect(source.getPolygon())) {
            std::cout << "New shape is not a correct polygon. Skipped.\n";
            return *this;
        }
        shape = source.getPolygon();
        return *this;
    }

    ~CorrectPolygon() = default;
};

#endif //LABS_PROGRAMMING_POLYGON_H
#endif //LABS_PROGRAMMING_CORRECTPOLYGON_H
