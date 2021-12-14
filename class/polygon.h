//
// Created by Михаил on 09.02.2021.
//

#ifndef LABS_PROGRAMMING_POLYGON_H
#ifdef LABS_PROGRAMMING_POINT_H

#define LABS_PROGRAMMING_POLYGON_H
// Parent class for CorrectPolygon, Triangle and Trapezium
class Polygon {
protected:
    vector<Point> shape;

    // Functions to avoid equal dots addition
    static long long findDot(const Point source[], const unsigned long long start,
                             const unsigned long long end, const Point &needle) {
        for (unsigned long long i = start; i < end; ++i)
            if (source[i] == needle) {
                return (long long) i;
            }
        return -1;
    }

    static long long findDot(const vector<Point> &source, const unsigned long long start,
                             const unsigned long long end, const Point &needle) {
        for (unsigned long long i = start; i < end; ++i)
            if (source[i] == needle) {
                return (long long) i;
            }
        return -1;
    }

private:
    // Checking if polygon is convex
    static bool checkIfConvex(const Point pts[], const unsigned long long count) {
        if (count < 3) return false;
        double direction = 0;
        for (int i = 1; i < count - 1; ++i) {
            Point AB(pts[i].getX() - pts[i - 1].getX(), pts[i].getY() - pts[i - 1].getY());
            Point BC(pts[i + 1].getX() - pts[i].getX(), pts[i + 1].getY() - pts[i].getY());
            if (i == 1) {
                direction = AB.getX() * BC.getY() - AB.getY() * BC.getX();
                continue;
            }
            double tmp = AB.getX() * BC.getY() - AB.getY() * BC.getX();
            if (direction < 0 && tmp > 0 || direction > 0 && tmp < 0) return false;
        }

        double square = 0;
        for (unsigned long long i = 0; i < count - 1; ++i) {
            square += pts[i].getX() * pts[i + 1].getY() - pts[i + 1].getX() * pts[i].getY();
        }
        square += pts[count - 1].getX() * pts[0].getY() - pts[0].getX() * pts[count - 1].getY();

        if (std::abs((float) square) == 0) return false;
        return true;
    }

    static bool checkIfConvex(const vector<Point> &source) {
        if (source.size() < 3) return false;
        double direction = 0;
        for (int i = 1; i < source.size() - 1; ++i) {
            Point AB(source[i].getX() - source[i - 1].getX(), source[i].getY() - source[i - 1].getY());
            Point BC(source[i + 1].getX() - source[i].getX(), source[i + 1].getY() - source[i].getY());
            if (i == 1) {
                direction = AB.getX() * BC.getY() - AB.getY() * BC.getX();
                continue;
            }
            double tmp = AB.getX() * BC.getY() - AB.getY() * BC.getX();
            if (direction < 0 && tmp > 0 || direction > 0 && tmp < 0) return false;
        }

        double square = 0;
        for (unsigned long long i = 0; i < source.size() - 1; ++i) {
            square += source[i].getX() * source[i + 1].getY() - source[i + 1].getX() * source[i].getY();
        }
        square += source[source.size() - 1].getX() * source[0].getY() - source[0].getX() * source[source.size() - 1].getY();
        if (std::abs((float) square) == 0) return false;
        return true;
    }

public:
    // General functions for all of the following shapes: polygon, triangle, correct polygon and trapezium.
    // // Function to get a vector of points (set of dots)
    vector<Point> getPolygon() const {
        return shape;
    }

    // // Function to get amount of points
    unsigned long long getSize() const {
        return shape.size();
    }

    // // Function to get square of a polygon
    double getSquare() const {
        if (shape.size() < 3) return 0;
        double square = 0;
        for (unsigned long long i = 0; i < shape.size() - 1; ++i) {
            square += shape[i].getX() * shape[i + 1].getY() - shape[i + 1].getX() * shape[i].getY();
        }
        square += shape[shape.size() - 1].getX() * shape[0].getY() - shape[0].getX() * shape[shape.size() - 1].getY();
        return std::abs(square) / 2;
    }

    // // Function to get perimeter of a polygon
    double getPerimeter() const {
        if (shape.size() < 3) return 0;
        using std::sqrt;
        double perimeter = 0.0;

        for (unsigned long long i = 0; i < shape.size() - 1; ++i) {
            perimeter += sqrt((shape[i + 1].getX() - shape[i].getX()) * (shape[i + 1].getX() - shape[i].getX())
                              + (shape[i + 1].getY() - shape[i].getY()) * (shape[i + 1].getY() - shape[i].getY()));
        }
        perimeter += sqrt((shape[shape.size() - 1].getX() - shape[0].getX())
                          * (shape[shape.size() - 1].getX() - shape[0].getX())
                          + (shape[shape.size() - 1].getY() - shape[0].getY())
                            * (shape[shape.size() - 1].getY() - shape[0].getY()));

        return perimeter;
    }

    // Virtual function to change heights. It's implemented at child classes
    virtual void changeHeight(unsigned long long number, double x, double y) {
        vector<Point> tmp = shape;
        shape[number % shape.size()].setX(x);
        shape[number % shape.size()].setY(y);
        if (!checkIfConvex(shape)) {
            std::cout << "Shape is not convex. Skipped.\n";
            shape = tmp;
        }
    }

    // Clearing all dots
    void clear() {
        shape.clear();
    }

    // /General functions
    // Constructors
    Polygon() {
        shape = {};
    }

    explicit Polygon(const Point pts[], const unsigned long long count = 0) {
        if (!checkIfConvex(pts, count)) {
            std::cout << "Shape is not convex. Skipped.\n";
            return;
        }
        for (unsigned long long i = 0; i < count; ++i) {
            if (!findDot(shape, 0, i, pts[i])) shape.push_back(pts[i]);
        }
    }

    explicit Polygon(const vector<Point> &pts) {
        if (!checkIfConvex(pts)) {
            std::cout << "Shape is not convex. Skipped.\n";
            return;
        }
        for (int i = 0; i < pts.size(); ++i) {
            if (findDot(pts, 0, i, pts[i]) == -1) shape.push_back(pts[i]);
        }
    }

    // Copy constructor
    Polygon(const Polygon &source) {
        shape = source.shape;
    }

    // Virtual equal operators. It's implemented in child classes
    virtual Polygon &operator=(const vector<Point> &source) {
        if (!checkIfConvex(source)) {
            cout << "New shape is not convex. Skipped.\n";
            return *this;
        }
        shape = source;
        return *this;
    }

    virtual Polygon &operator=(const Polygon &source) {
        shape = source.shape;
        return *this;
    }

    // Destructor
    ~Polygon() {
        clear();
    }
};

#endif //LABS_PROGRAMMING_POINT_H
#endif //LABS_PROGRAMMING_POLYGON_H
