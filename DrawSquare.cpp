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

// #include "DrawSquare.h"
// #define LENGTH 0.1 

// using namespace std;


// Square::Square( Point * point ) {

//     this->orgin = *point;
//     this->length = LENGTH;

//     // for( int n = 0; n < Squar::sides; n++ )
//     //     this->lines[n] = Line( point, this->length, );

//     this->lines[0] = Line( point, this->length, Direction.x );
//     this->lines[1] = Line( point, -this->length, Direction.y );
//     this->lines[2] = Line( point, -this->length, Direction.x );
//     this->lines[3] = Line( point, this->length, Direction.y );

// }

// void Square::draw() {

//     // Set the vertex color to be whatever we stored in the point
//     glColor3f(
//         this->orgin.r, 
//         this->orgin.g, 
//         this->orgin.b
//     );


//     // Draw the lines for the square
//     for( int n = 0; n < Squar::sides; n++ )
//         this->lines[n].draw();

// }


