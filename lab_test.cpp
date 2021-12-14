//
// Created by Михаил on 15.02.2021.
//

//
// Created by Михаил on 09.02.2021.
//

#include <iostream>
#include <vector>
#include <cmath>

using std::vector;
using std::cout;

#include "class/point.h"
#include "class/polyline.h" // Requires point.h
#include "class/closed_polyline.h" // Requires polyline.h

#include "class/polygon.h" // Requires point.h
#include "class/correct_polygon.h" // Requires polygon.h
#include "class/triangle.h" // Requires polygon.h [optional: corrert_polygon.h]
#include "class/trapezium.h" // Requires polygon.h [optional: correct_polygon.h]

void printPoints(vector<Point> &source) {
    cout << "\tPoints list:\n";
    for (auto &i : source) {
        cout << "\t\t" << i.getX() << " " << i.getY() << '\n';
    }
}

void printPolyline(Polyline &source) {
    cout << "\tPolyline size: " << source.getSize() << '\n';
    cout << "\tPolyline dots:\n";
    for (unsigned long long i = 0; i < source.getSize(); ++i) {
        cout << "\t\t" << source.getPolyline()[i].getX() << " " << source.getPolyline()[i].getY() << '\n';
    }

}

void printClosedPolyline(ClosedPolyline &source) {
    cout << "\tClosed Polyline size: " << source.getSize() << '\n';
    cout << "\tSource dots:\n";
    for (unsigned long long i = 0; i < source.getSize(); ++i) {
        cout << "\t\t" << source.getPolyline()[i].getX() << " " << source.getPolyline()[i].getY() << '\n';
    }
}

void printPolygon(Polygon &source) {
    cout << "\tPolygon size: " << source.getSize() << '\n';
    cout << "\tPolygon square: " << source.getSquare() << '\n';
    cout << "\tPolygon perimeter: " << source.getPerimeter() << '\n';
    cout << "\tPolygon dots:\n";
    for (unsigned long long i = 0; i < source.getSize(); ++i) {
        cout << "\t\t" << source.getPolygon()[i].getX() << " " << source.getPolygon()[i].getY() << '\n';
    }
}

void printTriangle(Triangle &source) {
    // using parental methods
    cout << "\tTriangle size: " << source.getSize() << '\n';
    cout << "\tTriangle square: " << source.getSquare() << '\n';
    cout << "\tTriangle perimeter: " << source.getPerimeter() << '\n';
    cout << "\tTriangle dots:\n";
    for (unsigned long long i = 0; i < source.getSize(); ++i) {
        cout << "\t\t" << source.getPolygon()[i].getX() << " " << source.getPolygon()[i].getY() << '\n';
    }
}

void printCorrectPolygon(CorrectPolygon &source) {
    // using parental methods
    cout << "\tCorrect polygon size: " << source.getSize() << '\n';
    cout << "\tCorrect polygon square: " << source.getSquare() << '\n';
    cout << "\tCorrect polygon perimeter: " << source.getPerimeter() << '\n';
    cout << "\tCorrect polygon dots:\n";
    for (unsigned long long i = 0; i < source.getSize(); ++i) {
        cout << "\t\t" << source.getPolygon()[i].getX() << " " << source.getPolygon()[i].getY() << '\n';
    }
}

void printTrapezium(Trapezium &source) {
    // using parental methods
    cout << "\tTrapezium size: " << source.getSize() << '\n';
    cout << "\tTrapezium square: " << source.getSquare() << '\n';
    cout << "\tTrapezium perimeter: " << source.getPerimeter() << '\n';
    cout << "\tTrapezium dots:\n";
    for (unsigned long long i = 0; i < source.getSize(); ++i) {
        cout << "\t\t" << source.getPolygon()[i].getX() << " " << source.getPolygon()[i].getY() << '\n';
    }
}

int main() {
    cout << "/************** POINTS TEST **************\\\n";
    Point a(0, 0);
    Point b(1, 0);
    Point c(2, 1);

    vector<Point> array = {a, b, c};

    printPoints(array);

    a.setX(20); a.setY(30);
    b.setX(1); b.setY(0);
    c.setX(0); c.setY(0);

    array = {a, b, c};

    printPoints(array);

    cout << "/************** POLYLINE TEST **************\\\n";
    a.setX(0); a.setY(0);
    b.setX(20); b.setY(10);
    c.setX(10); c.setY(-10);

    array = {a, b, c};
    Polyline polyline(array);

    printPoints(array);
    printPolyline(polyline);

    polyline.changeHeight(2, 3, 3);
    polyline.changeHeight(5, 0, 0); // Incorrect due to number > polyline.getSize().
    // Numeration with zero. Error will be occured

    printPolyline(polyline);

    cout << "/************** CLOSED POLYLINE TEST **************\\\n";
    ClosedPolyline closedPolyline(polyline); // Initialization with parent class object
    array = closedPolyline.getPolyline();

    printPoints(array);
    printClosedPolyline(closedPolyline);

    closedPolyline.changeHeight(2, 4, 40);
    closedPolyline.changeHeight(4, 5, 5); // Correct. Will be replaced 4 % 3 == 1st height.

    printClosedPolyline(closedPolyline);

    cout << "/************** POLYGON TEST **************\\\n";
    a.setX(0); a.setY(0);
    b.setX(0); b.setY(0); // Incorrect shape
    c.setX(10); c.setY(-10);

    array = {a, b, c};

    Polygon polygon(array);

    printPoints(array);
    printPolygon(polygon);


    a.setX(0); a.setY(0);
    b.setX(1); b.setY(1);
    c.setX(2); c.setY(2); // Incorrect shape

    array = {a, b, c};
    polygon = array;

    printPoints(array);
    printPolygon(polygon);

    a.setX(0); a.setY(0);
    b.setX(0); b.setY(2);
    c.setX(2); c.setY(2);
    Point d(2, 0);

    array = {a, b, c, d};
    polygon = array;

    printPoints(array);
    printPolygon(polygon);

    cout << "/************** TRIANGLE TEST **************\\\n";
    Triangle triangle(polygon); // Incorrect initialization with 4 heights
    printPoints(array);
    printTriangle(triangle);

    array = {a, b, c};
    triangle = array;
    triangle.changeHeight(3, 2, 3); // Will be changed 1st height

    printPoints(array);
    printTriangle(triangle);

    triangle.changeHeight(3, 2, 2); // Incorrect replacement: height is already exists

    printTriangle(triangle);

    cout << "/************** CORRECT POLYGON TEST **************\\\n";
    a.setX(0); a.setY(0);
    b.setX(0); b.setY(0.5);
    c.setX(1); c.setY(0);
    d.setX(5); d.setY(5);

    array = {a, b, c, d};
    CorrectPolygon correctPolygon(array); // Incorrect init: not a correct shape

    printPoints(array);
    printCorrectPolygon(correctPolygon);

    a.setX(0); a.setY(0);
    b.setX(0); b.setY(3);
    c.setX(3); c.setY(3);
    d.setX(3); d.setY(0);

    array = {a, b, c, d};
    polygon = array; // Square
    correctPolygon = polygon; // correct polygon init by a polygon

    printPoints(array);
    printCorrectPolygon(correctPolygon);

    correctPolygon.changeSize(0); // Incorrect reshape
    printCorrectPolygon(correctPolygon);

    correctPolygon.changeSize(1.5); // Correct reshape
    printCorrectPolygon(correctPolygon);

    cout << "/************** TRAPEZIUM TEST **************\\\n";
    Trapezium trapezium(correctPolygon); // Trapezium init by a correct polygon

    printPoints(array);
    printTrapezium(trapezium);

    a.setX(0); a.setY(0);
    b.setX(1); b.setY(3);
    c.setX(3); c.setY(3);
    d.setX(4); d.setY(0);

    array = {a, b, c, d}; // correct trapezium
    trapezium = array;
    printTrapezium(trapezium);

    array = {a, b, c}; // too few dots
    trapezium = array;
    printPoints(array);
    printTrapezium(trapezium);

    a.setX(-2); a.setY(-4);
    b.setX(3); b.setY(6);
    c.setX(4.5); c.setY(15);
    d.setX(15); d.setY(0);

    array = {a, b, c, d}; // random shape; not a trapezium
    trapezium = array;
    printPoints(array);
    printTrapezium(trapezium);

    return 0;
}