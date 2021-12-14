//
// Created by Михаил on 09.02.2021.
//

#ifndef LABS_PROGRAMMING_POINT_H
#define LABS_PROGRAMMING_POINT_H


class Point {
private:
    double x_;
    double y_;
public:
    void setX(const double x) {
        x_ = x;
    }

    void setY(const double y) {
        y_ = y;
    }

    double getX() const {
        return x_;
    }

    double getY() const {
        return y_;
    }

    Point() {
        x_ = 0;
        y_ = 0;
    }

    Point(const char x, const char y) {
        x_ = (double) x;
        y_ = (double) y;
    }

    Point(const int x, const int y) {
        x_ = (double) x;
        y_ = (double) y;
    }

    Point(const long long x, const long long y) {
        x_ = (double) x;
        y_ = (double) y;
    }

    Point(const float x, const float y) {
        x_ = (double) x;
        y_ = (double) y;
    }

    Point(const double x, const double y) {
        x_ = x;
        y_ = y;
    }

    Point(const long double x, const long double y) {
        x_ = (double) x;
        y_ = (double) y;
    }

    Point(const Point &source) {
        x_ = source.getX();
        y_ = source.getY();
    }

    Point &operator=(const Point &source) {
        x_ = source.getX();
        y_ = source.getY();
        return *this;
    }

    bool operator==(const Point &source) const {
        return this->getX() == source.getX() && this->getY() == source.getY();
    }

    bool operator==(const int source) const {
        return this->getX() == source && this->getY() == source;
    }

    bool operator%(const int source) const {
        return (int) this->getX() % source && (int) this->getY() % source;
    }

    bool operator>(const int source) const {
        return this->getX() > source && this->getY() > source;
    }

    bool operator>(const Point source) const {
        return this->getX() > source.getX() && this->getY() > source.getY();
    }

    Point &operator-(const double source) const {
        return *(new Point(this->getX() - source, this->getY() - source));
    }


    bool operator<(const int source) const {
        return this->getX() < source && this->getY() < source;
    }

    bool operator!=(const Point &source) const {
        return !(this->getX() == source.getX() && this->getY() == source.getY());
    }

//    ~Point() {
//        delete &x_;
//        delete &y_;
//    }
};


#endif //LABS_PROGRAMMING_POINT_H
