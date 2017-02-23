/**
 * Michael T. Andemeskel
 * mandemeskel@ucmerced.edu
 * CSE165 Spring 2017
 * 
 * Copyright 2017
 * 
 * Lab info:
 **/

#include <iostream>
#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <cmath>
#include "MyCode.h"
#define LENGTH 0.1 

using namespace std;


/**
    Shape class definitions
**/
Shape::Shape() {
}
Shape::~Shape() {
}


// A constructor for point
Point::Point() {
    this->x = 0;
    this->y = 0;
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

Point::Point( float x, float y ) {
    this->x = x;
    this->y = y;
    this->r = 0;
    this->g = 0;
    this->b = 0;
}

Point::Point(float x, float y, float r, float g, float b) {
    this->x = x;
    this->y = y;
    this->r = r;
    this->g = g;
    this->b = b;
}

float Point::distance( Point * point ) const {

    float x_diff = this->x - point->x;
    float y_diff = this->y - point->y;
    float sum = pow( x_diff, 2) + pow( y_diff, 2 );

    return sqrt( sum );

}

void Point::draw() const {
    // Set the vertex color to be whatever we stored in the point
    glColor3f(this->r, this->g, this->b);

    glBegin(GL_POINTS);

    // Draw the vertex in the right position
    glVertex2f(this->x, this->y);

    glEnd();
}

void Point::invertColor() {
    this->r = abs( this->r - 1 );
    this->g = abs( this->g - 1 );
    this->b = abs( this->b - 1 );
}


/**
    Line Class Definitions
**/
Line::Line() {
    this->start = Point( 0, 0 );
    this->end = Point( 0, 0 );
    this->length = 0;
}

Line::Line( Point * start_point, Point * end_point ) {
    this->start = *start_point;
    this->end = *end_point;
    // TODO: Calculate length
    this->length = this->start.distance( &this->end ); 
}

Line::Line( Point * point, float length, Direction axis ) {

    this->start = *point;
    this->end = *point;
    this->length = length;

    if( axis == X_AXIS ) {

        this->end.x += this->length;

    } else {

        this->end.y += this->length;

    }

} 

void Line::draw() {

    glColor3f( this->start.r, this->start.g, this->start.b );
    glBegin( GL_LINES );

    glVertex2f( this->start.x, this->start.y );
    glVertex2f( this->end.x, this->end.y );

    glEnd();

}

// draws a line with user specific color
void Line::draw( Point * color ) {

    glColor3f( color->r, color->g, color->b );
    glBegin( GL_LINES );

    glVertex2f( this->start.x, this->start.y );
    glVertex2f( this->end.x, this->end.y );

    glEnd();

}

// draws line but supress the line's inherit color
void Line::draw( bool supress_color = false ) {

    // hide the lines natural color, this is for polygons
    // who want to control their color
    if( !supress_color )
        glColor3f( this->start.r, this->start.g, this->start.b );
    
    glBegin( GL_LINES );

    glVertex2f( this->start.x, this->start.y );
    glVertex2f( this->end.x, this->end.y );

    glEnd();

}

// updates the color of a line
void Line::updateColor( Point * color ) {

    this->start.r = color->r;
    this->start.g = color->g;
    this->start.b = color->b;

}


Line::~Line() {

}


/**
    Polygon Class Definitions
**/
Polygon::Polygon() {

    this->origin = Point( 0, 0 );
    this->length = 0;

}

void Polygon::draw() {

}

void Polygon::invertColor() {

    this->origin.r = abs( this->origin.r - 1 );
    this->origin.g = abs( this->origin.g - 1 );
    this->origin.b = abs( this->origin.b - 1 );
    
}


/**
    Square Class Definitions
**/
Square::Square( float x, float y ) {

    this->origin = Point( x, y );
    this->length = LENGTH;
    this->half_length = this->length/2;
    this->center = Point( 
        this->origin.x + this->half_length,
        this->origin.y - this->half_length
    );

}

Square::Square( Point * point ) {

    this->origin = *point;
    this->length = LENGTH;

    // create center point of square
    this->half_length = this->length/2;
    this->center = Point( 
        this->origin.x + this->half_length,
        this->origin.y - this->half_length
    );

    // creates the lines for the square
    Point * p = new Point( 
        this->origin.x + this->length, 
        this->origin.y - this->length,
        this->origin.r,
        this->origin.g,
        this->origin.b
    );
    Point op = *p;

    // top line
    this->lines[0] = Line( 
        point, 
        new Point( this->origin.x + this->length, this->origin.y ) 
    );
    // left line
    this->lines[1] = Line( 
        point, 
        new Point( this->origin.x, this->origin.y - this->length )
    );
    // right line
    this->lines[2] = Line( 
        &op, 
        new Point( op.x, op.y + this->length )
    );
    // bottom line
    this->lines[3] = Line( 
        &op, 
        new Point( op.x - this->length, op.y ) 
    );

}

Square::Square( Point * point, float length ) {

    this->origin = *point;
    this->length = length;

    // create center point of square
    this->half_length = this->length/2;
    this->center = Point( 
        this->origin.x + this->half_length,
        this->origin.y - this->half_length
    );

    // creates the lines for the square
    Point * p = new Point( 
        this->origin.x + this->length, 
        this->origin.y - this->length,
        this->origin.r,
        this->origin.g,
        this->origin.b
    );
    Point op = *p;

    // top line
    this->lines[0] = Line( 
        point, 
        new Point( this->origin.x + this->length, this->origin.y ) 
    );
    // left line
    this->lines[1] = Line( 
        point, 
        new Point( this->origin.x, this->origin.y - this->length )
    );
    // right line
    this->lines[2] = Line( 
        &op, 
        new Point( op.x, op.y + this->length )
    );
    // bottom line
    this->lines[3] = Line( 
        &op, 
        new Point( op.x - this->length, op.y ) 
    );
    
}

void Square::draw() {

    // Set the vertex color to be whatever we stored in the point
    glColor3f(
        this->origin.r, 
        this->origin.g, 
        this->origin.b
    );

    // Draw the lines for the square
    for( int n = 0; n < Square::sides; n++ )
        this->lines[n].draw( true );

}

Square::~Square() {

}


/*
    Button class definitions
*/
Button::Button( Point * point ) : Square( point ) {

    this->origin = *point;
    this->label = NULL;
    this->callback = NULL;
    this->clicked = false;

}

Button::Button( Point * point, Shape * shape, void (*callback)() ) : Square( point ) {

    this->origin = *point;
    // label is a pointer, so that the click event changes to 
    // the shape are kept track of
    this->label = shape;
    this->callback = callback;
    this->clicked = false;
    this->label_type = SQUARE;

}

Button::Button( Point * point, Shape * shape, Brush shape_type, void (*callback)() ) : Square( point ) {

    this->origin = *point;
    // label is a pointer, so that the click event changes to 
    // the shape are kept track of
    this->label = shape;
    this->callback = callback;
    this->clicked = false;
    this->label_type = shape_type;

}

void Button::click() {
    
    this->clicked != this->clicked;
    if( this->callback )
        this->callback();
    
    this->invertColor();

}

void Button::draw() {
    
    // call square draw last for it to be in the  background
    if( this->label_type == SQUARE )
        ((Square*)this->label )->draw();
    else if( this->label_type == POINT )
        ((Point*)this->label )->draw();

    ((Square*) this )->draw();

}

void Button::setLabel( Shape * shape ) {

    this->label = shape;

}

// checks if the button is clicked if it is and if_clicked_do_click is
// true than call the click function of the button
const bool Button::isClicked( Point * mouse, bool if_clicked_do_click = false ) {

    this->clicked = this->center.distance( mouse ) < this->half_length;

    if( if_clicked_do_click && this->clicked ) {
        this->click();
    }

    return this->clicked;

}

Button::~Button() {

}




