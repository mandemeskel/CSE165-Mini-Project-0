// A point data structure
struct Point {
	// The coordinates of the point
	float x;
	float y;

	// The color of the point
	float r;
	float g;
	float b;

    Point();
    Point( float, float );
    Point(float x, float y, float r, float g, float b);
    float distance ( Point * ) const;

};

// direction of line
enum Direction {
    X_AXIS = 'x',
    Y_AXIS = 'y'
};

// what will be drawn on a mouse click
enum Brush {
    POINT = 'POINT',
    SQUARE = 'SQUARE'
};


struct Line {
    Point start;
    Point end;
    float length;
    
    Line();
    Line( Point *, Point * );
    Line( Point *, float, Direction );
    void draw();
    ~Line();
};


struct Square {

    private:
        static const int sides = 4;

        Point origin;    // top left corner
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
        ~Square();
};


struct Button : public Square {
    private:
        char * label;
        void (*callback)();

    public:
        Button();
        Button( Point * );
        Button( Point *, char * );
        Button( Point *, float );
        Button( Point *, float, char * );
        void setCallback( void * );
        void click();
        void draw();
        ~Button();
};


struct Menu {

    private:
        Point origin;
        Button * buttons;
        int num_btns;

    public:
        Menu();
        Menu( Point * );
        void draw();
        ~Menu();

};
