#include "Point.h"

enum Direction {
    x = 'x',
    y = 'y'
}

struct Line {
    Point start;
    Point end;
    float length;
    
    Line();
    Line( Point *, Point * );
    Line( Point *, float, Direction );
    void draw();
};