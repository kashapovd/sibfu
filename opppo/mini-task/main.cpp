#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include <cmath>
#include <tuple>
#include <functional>

class Point {
public:
    Point(double x, double y) : mY(x), mX(y){}
    const double getX() const {
        return mX;
    }
    const double getY() const {
        return mY;
    }
private:
    double mX;
    double mY;
};

class Segment { // might be a trait in Rust
public:
    Segment(){}
    virtual double len() const = 0;
    bool operator > (const Segment& seg) const {
        return (len() > seg.len());
    }
};

class Circle : public Segment {
public:
    Circle(Point center, double radius) : mCenter(center), mRadius(radius){}
    double len() const override {
        return 2. * M_PI * mRadius;
    }
private:
    Point mCenter;
    double mRadius;
};

class Line : public Segment {
public:
    Line(std::tuple<Point, Point> points): linePoints(points){};
    double len() const override {
        return sqrt(pow(std::get<1>(linePoints).getX() - std::get<0>(linePoints).getX(),2)
                   +pow(std::get<1>(linePoints).getY() - std::get<0>(linePoints).getY(),2));
    }
private:
    std::tuple<Point, Point> linePoints;
};

int main() {
    std::ifstream is{"/home/yaroslav/study/in.txt"};
    if (!is.is_open()) {
        throw std::runtime_error{"Unable to open file"};
    }

    // match any doubles and numbers. Can be started with -
    std::regex rgx{"[.\\-\\d]+"};
    std::vector<double> numbers;
    std::vector<std::unique_ptr<Segment>> segments;

    std::string SegementLine;
    while (std::getline(is, SegementLine)) {
        // simple number parser. thx google
        std::transform(std::sregex_token_iterator{SegementLine.begin(), SegementLine.end(), rgx },
                       {}, std::back_inserter(numbers),
                       std::bind(static_cast<double(*)(std::string const&, std::size_t*)>(&std::stod),
                                 std::placeholders::_1, nullptr));
        if (numbers.size() == 3) {
            segments.push_back(std::make_unique<Circle>(Point(numbers[0], numbers[1]), numbers[2]));
        }
        else if (numbers.size() == 4) {
            segments.push_back(std::make_unique<Line>(std::make_tuple(
                                                          Point(numbers[0], numbers[1]),
                                                          Point(numbers[2], numbers[3]))));
        }
        numbers.clear();
    }

    std::sort(segments.begin(), segments.end());

    for (auto const &f : segments) {
        std::cout << f->len() << std::endl;
    }

    is.close();
}
