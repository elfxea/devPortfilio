//
// Created by Михаил on 09.02.2021.
//

#ifndef LABS_PROGRAMMING_POLYLINE_H
#ifdef LABS_PROGRAMMING_POINT_H
#define LABS_PROGRAMMING_POLYLINE_H

// Parent class for ClosedPolyline
class Polyline {
protected:
    std::vector<Point> points;
public:
    virtual void changeHeight(const unsigned long long number, const double x, const double y) {
        if (number >= points.size()) {
            cout << "Height #" << number << " not found. Skipped.\n";
            return;
        }
        points[number].setX(x);
        points[number].setY(y);
    }

    void clear() {
        points.clear();
    }

    std::vector<Point> getPolyline() const {
        return points;
    }

    unsigned long long getSize() const {
        return points.size();
    }

    virtual double getLength() const {
        double length = 0;
        for (unsigned long long i = 0; i < points.size() - 1; ++i) {
            length += std::sqrt((points[i + 1].getX() - points[i].getX()) * (points[i + 1].getX() - points[i].getX())
                              + (points[i + 1].getY() - points[i].getY()) * (points[i + 1].getY() - points[i].getY()));
        }
        return length;
    }

    Polyline() {
        points = {};
    };

    explicit Polyline(const Point pts[], unsigned long long count = 0) {
        for (int i = 0; i < count; ++i)
            points.push_back(pts[i]);
    }

    explicit Polyline(const std::vector<Point> &pts) {
        points = pts;
    }

    Polyline(const Polyline &source) {
        points = source.getPolyline();
    }

    virtual Polyline &operator=(const Polyline &source) {
        points = source.getPolyline();
        return *this;
    }

    ~Polyline() {
        clear();
    }
};

#endif //LABS_PROGRAMMING_POINT_H
#endif //LABS_PROGRAMMING_POLYLINE_H
