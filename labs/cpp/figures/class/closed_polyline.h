//
// Created by Михаил on 09.02.2021.
//

#ifndef LABS_PROGRAMMING_CLOSED_POLYLINE_H
#ifdef LABS_PROGRAMMING_POLYLINE_H
#define LABS_PROGRAMMING_CLOSED_POLYLINE_H

class ClosedPolyline : public Polyline {
public:
    void changeHeight(const unsigned long long number, const double x, const double y) override {
        points[number % points.size()].setX(x);
        points[number % points.size()].setY(y);
    };

    double getLength() const override {
        double length = 0;
        for (unsigned long long i = 0; i < points.size() - 1; ++i) {
            length += std::sqrt((points[i + 1].getX() - points[i].getX()) * (points[i + 1].getX() - points[i].getX())
                                + (points[i + 1].getY() - points[i].getY()) * (points[i + 1].getY() - points[i].getY()));
        }
        length += sqrt((points[points.size() - 1].getX() - points[0].getX())
                          * (points[points.size() - 1].getX() - points[0].getX())
                          + (points[points.size() - 1].getY() - points[0].getY())
                            * (points[points.size() - 1].getY() - points[0].getY()));
        return length;
    }

    ClosedPolyline() : Polyline() {}

    explicit ClosedPolyline(const Point pts[], unsigned long long count = 0) : Polyline(pts, count) {}

    explicit ClosedPolyline(const vector<Point> &pts) : Polyline(pts) {}

    explicit ClosedPolyline(const Polyline &source) : Polyline(source) {}

    ClosedPolyline &operator=(const Polyline &source) override {
        points = source.getPolyline();
        return *this;
    }

    ClosedPolyline &operator=(const ClosedPolyline &source) {
        points = source.getPolyline();
        return *this;
    }

    ~ClosedPolyline() {
        clear();
    }
};

#endif //LABS_PROGRAMMING_POLYLINE_H
#endif //LABS_PROGRAMMING_CLOSED_POLYLINE_H
