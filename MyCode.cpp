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

void Line::draw( Point * color ) {

    glColor3f( color->r, color->g, color->b );
    glBegin( GL_LINES );

    glVertex2f( this->start.x, this->start.y );
    glVertex2f( this->end.x, this->end.y );

    glEnd();

}

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

void Line::updateColor( Point * color ) {

    this->start.r = color->r;
    this->start.g = color->g;
    this->start.b = color->b;

}


Line::~Line() {

    // free( this->start );
    // free( this->end );

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

    // update colors of the polygon's lines
    // TODO: this fails for some reason, buttons color does not get updated
    // on cick
    // for( int n = 0; n < this->sides; n++ )
    //     this->lines[n].updateColor( &this->origin );
    
}


/**
    Square Class Definitions
**/
Square::Square( float x, float y ) {

    this->origin = Point( x, y );
    this->length = LENGTH;

}

Square::Square( Point * point ) {

    this->origin = *point;
    this->length = LENGTH;

    // create center point of square for click testing
    float half_len = this->length/2;
    this->center = Point( 
        this->origin.x + half_len,
        this->origin.y + half_len
    );

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

    // cout << "drawing square" << this->length << endl;

}

Square::~Square() {

    // for( int n = 0; n < Square::sides; n++ )
    //     free( this->lines[n] );

}


/*
    Button class definitions
*/
Button::Button( Point * point, Polygon * polygon, void (*callback)() ) : Square( point ) {

    this->origin = *point;
    // label is a pointer, so that the click event changes to 
    // the polygon are kept track of
    this->label = polygon;
    this->callback = callback;
    this->clicked = false;
    this->label_type = SQUARE;

}

Button::Button( Point * point, Polygon * polygon, Brush polygon_type, void (*callback)() ) : Square( point ) {

    this->origin = *point;
    // label is a pointer, so that the click event changes to 
    // the polygon are kept track of
    this->label = polygon;
    this->callback = callback;
    this->clicked = false;
    this->label_type = polygon_type;

}

// Button::Button( Point * point, void (*drawLabel)(Point *), void (*callback)() ) : Square( point ) {

//     this->origin = *point;
//     this->drawLabel = drawLabel;
//     this->callback = callback;
//     this->clicked = false;

// }

void Button::click() {
    
    this->clicked != this->clicked;
    this->callback();
    this->invertColor();

}

void Button::draw() {
    
    // call square draw last for it to be in the  background
    // this->drawLabel( this->origin );
    if( this->label_type == SQUARE )
        ((Square*)this->label )->draw();
    else if( this->label_type == POINT )
        ((Point*)this->label )->draw();

    // this->label->draw();
    ((Square*) this )->draw();

}

void Button::setLabel( Polygon * polygon ) {

    this->label = polygon;

}

const bool Button::isClicked( Point * mouse, bool if_clicked_do_click = false ) {

    this->clicked = this->origin.distance( mouse ) < this->length;

    if( if_clicked_do_click && this->clicked ) {
        this->click();
		cout << "clicked " << this->origin.distance( mouse ) << " len: " << this->length << endl;
    }

    return this->clicked;

}

Button::~Button() {

}


/*
    Menu class definitions
*/
Menu::Menu( Point * point ) {

    this->origin = *point;
    // this->buttons = new vector<Button>;
    // this->num_btns = 0;

}

void Menu::addButton( Button * btn ) {

    this->buttons.push_back( *btn );

}

// creates horizontal menu of buttons
// void Menu::addButton( void (*drawLabel)(Point *), void (*callback)() ) {

//     int num_btns = this->buttons.size() - 1;
//     Point btn_orign( 
//         this->origin.x + LENGTH * num_btns,
//         this->origin.y
//     );
//     Button btn( &btn_orign, drawLabel, callback );

//     this->buttons.push_back( btn );

// }

void Menu::draw() {

    // for( int n = 0; n < this->num_btns; n++ )
    for( int n = 0; n < this->buttons.size(); n++ )
        this->buttons[n].draw();

}

Point Menu::getOrigin() const {

    return this->origin;

}

Menu::~Menu() {


}



