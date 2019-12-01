#include <iostream>
#include <iomanip>
#include <cmath>

class Point {
    public:
        double x;
        double y;
        Point() : x(0), y(0) {}
        Point(double xI, double yI) {
            x = xI;
            y = yI;
        }
        friend std::ostream& operator<< (std::ostream &out, const Point &point) {
            out << std::fixed << std::setprecision(2) << '(' << point.x << ", " << point.y << ')';
            return out;
        }
        friend std::istream& operator>> (std::istream &in, Point &point){
            in >> point.x;
            in >> point.y;
            return in;
        } 
};

double distance(Point one, Point two) {
    return sqrt((one.x - two.x) * (one.x - two.x) + (one.y - two.y) * (one.y - two.y));
}

class Figure {
    public:
        virtual void printCoor() {
            std::cout << "CoorTest\n";
        }
        virtual double area() {
            return 0;
        }
        virtual Point centr() {
            return Point();
        }
};

class Pentagon : public Figure {
    public:
        Pentagon(Point Centr, int R) {
             int N = 5;
             double angle;
              for (int i = 0; i < N; i++){
                  angle = 2*M_PI*i/N;
                  points[i].x =  R*cos(angle)+Centr.x;
                  points[i].y = R*sin(angle)+Centr.y;
              }
        }

        void printCoor() {
            std::cout << "1st = " << points[0] << "\t2nd = " << points[1] << "\n3rd = " << points[2] << "\t4th = " << points[3] << "\t5th = " << points[4] << '\n';
        }

        double area() {
            return (2.5*(distance(points[2],points[3])*0.85)*(distance(points[2],points[3])*0.85)*sin(0.4*M_PI));
        }

        Point centr() {
            Point out;

            out.x = points[0].x - distance(points[2],points[3])*0.85;
            
            out.y = points[0].y;
            
            return out;
        }
    private:
        Point points[5];
};

class Rhombus : public Figure {
    public:
        Rhombus(Point in1, Point in2, int length) {
            points[3] = in1;
            points[1] = in2;
            double tgA = abs(points[3].y - points[1].y) / abs(points[3].x - points[1].x);
            Point mid((points[3].x +points[1].x) / 2, (points[3].y +points[1].y) / 2);
            double midLen = sqrt(length*length - pow(distance(mid, in1), 2));
            if (points[3].x > points[1].x) {
                points[0].x = mid.x + midLen * cos(90 * M_PI / 180 - atan(tgA));
                points[2].x = mid.x - midLen * cos(90 * M_PI / 180 - atan(tgA));
            } else {
                points[0].x = mid.x - midLen * cos(90 * M_PI / 180 - atan(tgA));
                points[2].x = mid.x + midLen * cos(90 * M_PI / 180 - atan(tgA));
            }
            if (points[3].y > points[1].y) {
                points[0].y = mid.y - midLen * sin(90 * M_PI / 180 - atan(tgA));
                points[2].y = mid.x + midLen * sin(90 * M_PI / 180 - atan(tgA));
            } else {
                points[0].y = mid.y + midLen * sin(90 * M_PI / 180 - atan(tgA));
                points[2].y = mid.y - midLen * sin(90 * M_PI / 180 - atan(tgA));
            }
        }

        void printCoor() {
            std::cout << "1st = " << points[0] << "\t2nd = " << points[1] << "\n4rd = " << points[3] << "\t3th = " << points[2] << '\n';
        }

        double area() {
            return (distance(points[1], points[3]) * distance(points[0], points[2])) / 2;
        }

        Point centr() {
            Point out;
            for (int i = 0; i < 4; i++) {
                out.x += points[i].x;
                out.y += points[i].x;
            }
            out.x /= 4;
            out.y /= 4;
            return out;
        }
    private:
        Point points[4];
};

class Hexagon : public Figure {
    public:
        Hexagon(Point Centr, int R) {
             int N = 6;
             double angle;
              for (int i = 0; i < N; i++){
                  angle = 2*M_PI*i/N;
                  points[i].x =  R*cos(angle)+Centr.x;
                  points[i].y = R*sin(angle)+Centr.y;
              }
        }

        void printCoor() {
            std::cout << "1st = " << points[0] << "\t2nd = " << points[1] << "\n3rd = " << points[2] << "\t4th = " << points[3] << "\t5th = " << points[4] << "\t6th = " << points[5]<< '\n';
        }

        double area() {
            return (1.5 * sqrt(3) * (points[5].x - points[4].x) * (points[5].x - points[4].x));
        }

        Point centr() {
            Point out;
            
            out.x = points[5].x-(points[5].x - points[4].x)/2;
            out.y = points[5].y+(points[1].y - points[5].y)/2 ;
            return out;
        }
    private:
        Point points[6];
};
