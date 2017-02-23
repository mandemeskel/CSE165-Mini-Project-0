#include <vector>


struct Shape {

    Shape();
    void invertColor();
    ~Shape();

};

// TODO: add privacy to this class
// A point data structure
struct Point : public Shape {
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
    void draw() const;
    void invertColor();

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


struct Line : public Shape {
    Point start;
    Point end;
    float length;
    
    Line();
    Line( Point *, Point * );
    Line( Point *, float, Direction );
    void draw();
    void draw( Point * );
    void draw( bool );
    void updateColor( Point * );
    ~Line();
};


struct Polygon : public Shape {
    protected:
        Point center;
        Point origin;    // top left corner
        float length;
        static const int sides = 0;
        Line lines[sides];

    public:
        Polygon();
        void draw();
        void invertColor();

};


struct Square : public Polygon {

    private:
        static const int sides = 4;

    protected:

        // Lines lines[4];
        Line lines[sides];
        float half_length;

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
        // label is a pointer, so that the click event changes to 
        // the shape are kept track of
        Shape * label;
        Brush label_type;
        void (*drawLabel)();
        void (*callback)();
        bool clicked;

    public:
        Button();
        Button( Point * );
        Button( Point *, Shape *, void (*callback)() );
        Button( Point *, Shape *, Brush, void (*callback)() );
        Button( Point *, void (*drawLabel)(Point *), void (*callback)() );
        void setCallback( void * );
        void setDrawLabel( void * );
        void setLabel( Shape * );
        void setLength();
        void click();
        const bool isClicked( Point *, bool );
        void draw();
        ~Button();
};


struct Menu {

    private:
        Point origin;
        // void * buttons;
        std::vector<Button> buttons;
        // int num_btns;

    public:
        Menu();
        Menu( Point * );
        void addButton( Button * );
        void addButton( void (*drawLabel)(Point *), void (*callback)() );
        void draw();
        Point getOrigin() const;
        ~Menu();

};
