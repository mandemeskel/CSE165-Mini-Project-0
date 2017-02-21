// /**
//  * Michael T. Andemeskel
//  * mandemeskel@ucmerced.edu
//  * CSE165 Spring 2017
//  * 
//  * Copyright 2017
//  * 
//  * Lab info:
//  **/

// #include <iostream>
// #if defined WIN32
// #include <freeglut.h>
// #elif defined __APPLE__
// #include <GLUT/glut.h>
// #else
// #include <GL/freeglut.h>
// #endif

// #include "Line.h"

// using namespace std;


// Line::Line( Point * point, float size, Direction dir ) {

//     this->start = *point;
//     this->end = *point; // does this make a new copy?
//     this->length = size;

//     if( dir == Direction.x ) {

//         this->end.x += this->length;

//     } else {

//         this->end.y += this->length;

//     }

// }

// void Line::draw() {

//     glColor3f(
//         this->start.r, 
//         this->start.g, 
//         this->start.b
//     );

//     glBegin( GL_LINES );

//     glVertex2f( this->start.x, this->start.y );
//     glVertex2f( this->end.x, this->end.y );

//     glEnd();

// }