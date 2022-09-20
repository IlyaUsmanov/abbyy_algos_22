#include <stdio.h>

class Prism {
protected:
    double _height;
public:
    Prism(double height): _height(height) {}
    virtual double Square() const = 0;
    double Volume() const {
        return Square() * _height;
    }
};

class Box: public Prism {
private:
    double _a;
public:
    Box(double height, double a): _a(a), Prism(height) {}
    double Square() const override {
        return _a * _a;
    }
};

class Cube: public Box {
public:
    Cube(double a): Box(a, a) {}
};

int main() {
    const Prism *p, *q, *r;
    Box a(0.5, 2), b(5, 0.2);
    Cube c(0.5);
    p = &a; q = &b; r = &c;
    printf("Squares: %3.3lf %3.3lf %3.3lf\n",
           p->Square(), q->Square(), r->Square());
    printf("Volumes: %3.3lf %3.3lf %3.3lf\n",
           p->Volume(), q->Volume(), r->Volume());
    return 0;
}