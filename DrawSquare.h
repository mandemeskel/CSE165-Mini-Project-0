#include "Line.h"

struct Square {

    private:
        static const int sides = 4;

        Point orgin;    // top left corner
        float length;

        // Lines lines[4];
        Line lines[sides];

    public:
        Square();
        Square( Point * );
        Square( Point *, float );
        Square( float, float );
        Square( float, float, float );
        void draw();
        void setLength( float size );
        float getLength();
        // static deque<Square> squares;
    
};
