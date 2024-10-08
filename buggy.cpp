#include <iostream>

struct Point {
    int x, y;

    Point () : x(), y() {}
    Point (int _x, int _y) : x(_x), y(_y) {}
};

class Shape {
    int vertices;
    Point** points;
    
    // set methods as public to fix access errors later in code
    public:
        Shape (int _vertices) {
            vertices = _vertices;
            points = new Point*[vertices+1];
        }

        ~Shape () {
            // Destructor added because points kept leaking
            for (int i = 0; i <= vertices; i++) {
                delete points[i];
            }
            delete[] points;
        }

        void addPoints (/* formal parameter for unsized array called pts */Point pts[]) {
            // didn't want to add cstring library to deal with memcpy so I removed it and coded it in a more conventional format
            for (int i = 0; i < vertices; i++) {
                points[i] = new Point(pts[i].x,pts[i].y);       
            }
            // add first point a second time to the end to make the shoelace formula work properly 
            points[vertices] = new Point(pts[0].x,pts[0].y);
        }

    double* area () {
        int temp = 0;
            // changed <= to < to fix seg fault here
        for (int i = 0; i < vertices; i++) {
            // FIXME: there are two methods to access members of pointers
            //        use one to fix lhs and the other to fix rhs
            int lhs = points[i]->x * points[i+1]->y;
            int rhs = (*points[i+1]).x * (*points[i]).y;
            temp += (lhs - rhs);
        }
        // needed to make new double to return proper variable type
        double* area = new double(abs(temp)/2.0);
        return area;
    }
};

int main () {
    // FIXME: create the following points using the three different methods
    //        of defining structs:
              Point tri1;
              Point tri2; tri2.x = 1; tri2.y = 2;
              Point tri3(2,0);

    // adding points to tri
    Point triPts[3] = {tri1, tri2, tri3};
    Shape* tri = new Shape(3);
    tri->addPoints(triPts);

    // FIXME: create the following points using your preferred struct
    //        definition:
              Point quad1;
              Point quad2(0,2);
              Point quad3(2,2);
              Point quad4(2,0);

    // adding points to quad
    Point quadPts[4] = {quad1, quad2, quad3, quad4};
    Shape* quad = new Shape(4);
    quad->addPoints(quadPts);

    // FIXME: print out area of tri and area of quad
    double* triArea = tri->area();
    double* quadArea = quad->area();
    printf("Area of triangle: %f\n",*triArea);
    printf("Area of quadrilateral: %f\n",*quadArea);

    // Deleting everyting I dynamically allocated
    delete triArea;
    delete tri;
    delete quadArea;
    delete quad;
    return 0;
}
