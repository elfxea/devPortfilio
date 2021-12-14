//
// Created by Михаил on 09.02.2021.
//

#ifndef LABS_PROGRAMMING_TRAPEZIUM_H
#ifdef LABS_PROGRAMMING_POLYGON_H
#define LABS_PROGRAMMING_TRAPEZIUM_H

class Trapezium : public Polygon {
private:
    // Checking if a shape is a Trapezium
    static bool checkIfTrapezium(const Point source[], const unsigned long long count) {
        if (count != 4) return false;

        for (int i = 0; i < count; ++i) {
            unsigned long long index = findDot(source, 0, i, source[i]);
            if (index != -1) return false;
            index = findDot(source, i + 1, count, source[i]);
            if (index != -1) return false;
        }

        double direction = 0;
        Point AB(source[1].getX() - source[0].getX(), source[1].getY() - source[0].getY());
        Point BC(source[2].getX() - source[1].getX(), source[2].getY() - source[1].getY());
        Point CD(source[3].getX() - source[2].getX(), source[3].getY() - source[2].getY());
        Point DA(source[0].getX() - source[3].getX(), source[0].getY() - source[3].getY());

        direction = AB.getX() * BC.getY() - AB.getY() * BC.getX();

        if ((AB.getX() * CD.getY() - AB.getY() * CD.getX()) != 0 &&
            (BC.getX() * DA.getY() - BC.getY() * DA.getX()) != 0)
            return false;

        if ((AB.getX() * CD.getY() - AB.getY() * CD.getX()) == 0 &&
            (AB.getX() * BC.getY() - AB.getY() * BC.getX()) == 0)
            return false;
        return true;
    }

    static bool checkIfTrapezium(const vector<Point> &source) {
        if (source.size() != 4) return false;

        for (int i = 0; i < source.size(); ++i) {
            unsigned long long index = findDot(source, 0, i, source[i]);
            if (index != -1) return false;
            index = findDot(source, i + 1, source.size(), source[i]);
            if (index != -1) return false;
        }

        double direction = 0;
        Point AB(source[1].getX() - source[0].getX(), source[1].getY() - source[0].getY());
        Point BC(source[2].getX() - source[1].getX(), source[2].getY() - source[1].getY());
        Point CD(source[3].getX() - source[2].getX(), source[3].getY() - source[2].getY());
        Point DA(source[0].getX() - source[3].getX(), source[0].getY() - source[3].getY());

        direction = AB.getX() * BC.getY() - AB.getY() * BC.getX();

        if ((AB.getX() * CD.getY() - AB.getY() * CD.getX()) != 0 &&
            (BC.getX() * DA.getY() - BC.getY() * DA.getX()) != 0)
            return false;

        if ((AB.getX() * CD.getY() - AB.getY() * CD.getX()) == 0 &&
            (AB.getX() * BC.getY() - AB.getY() * BC.getX()) == 0)
            return false;
        return true;
    }

public:
    // Implementation of changeHeight
    void changeHeight(unsigned long long number, double x, double y) override {
        vector<Point> tmp = shape;
        Polygon::changeHeight(number, x, y);
        if (!checkIfTrapezium(shape)) {
            std::cout << "New shape is not a trapezium. Skipped.\n";
            shape = tmp;
        }
    }

    // Constructors
    Trapezium() : Polygon() {
        shape = {};
    }

    explicit Trapezium(const Point pts[], const unsigned long long count = 0) : Polygon(pts, count) {
        if (!checkIfTrapezium(pts, count)) {
            std::cout << "Shape is not a trapezium. Skipped.\n";
            return;
        }
        shape = (new Polygon(pts, count))->getPolygon();
    }

    explicit Trapezium(const vector<Point> &pts) : Polygon(pts) {
        if (!checkIfTrapezium(pts)) {
            std::cout << "Shape is not a trapezium. Skipped.\n";
            return;
        }
        shape = (new Polygon(pts))->getPolygon();
    }

    explicit Trapezium(const Polygon &source) : Polygon(source) {
        if (!checkIfTrapezium(source.getPolygon())) {
            std::cout << "Shape is not a trapezium. Skipped.\n";
            return;
        }
        shape = (new Polygon(source))->getPolygon();
    }

#ifdef LABS_PROGRAMMING_CORRECTPOLYGON_H

    explicit Trapezium(const CorrectPolygon &source) : Polygon(source) {
        if (!checkIfTrapezium(source.getPolygon())) {
            std::cout << "Shape is not a trapezium. Skipped.\n";
            return;
        }
        shape = (new Polygon(source.getPolygon()))->getPolygon();
    }

#endif

    // Copy constructor
    Trapezium(const Trapezium &source) : Polygon(source) {
        shape = (new Polygon(source.getPolygon()))->getPolygon();
    }

    Trapezium &operator=(const vector<Point> &source) override {
        if (!checkIfTrapezium(source)) {
            cout << "New shape is not a trapezium. Skipped.\n";
            return *this;
        }
        *this = Polygon::operator=(source);
        return *this;
    }

    // Equal operators
    Trapezium &operator=(const Polygon &source) override {
        if (!checkIfTrapezium(source.getPolygon())) {
            std::cout << "New shape is not a trapezium. Skipped.\n";
            return *this;
        }
        shape = (new Polygon(source.getPolygon()))->getPolygon();
        return *this;
    }

#ifdef LABS_PROGRAMMING_CORRECTPOLYGON_H

    Trapezium &operator=(const CorrectPolygon &source) {
        if (!checkIfTrapezium(source.getPolygon())) {
            std::cout << "New shape is not a trapezium. Skipped.\n";
            return *this;
        }
        shape = (new Polygon(source.getPolygon()))->getPolygon();
        return *this;
    }

#endif

    Trapezium &operator=(const Trapezium &source) {
        shape = source.shape;
        return *this;
    }

    ~Trapezium() = default;
};

#endif //LABS_PROGRAMMING_POLYGON_H
#endif //LABS_PROGRAMMING_TRAPEZIUM_H
