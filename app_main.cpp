#include <iostream>
#include <deque>

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

// my code
// #include "DrawSquare.h"
#include "MyCode.h"


using namespace std;


// enum that controls what shape is draw on mouse click
Brush brush = POINT; 


// Some global variables to maintain state
// A "Double Ended QUEue" to store points 
deque<Point> points;
deque<Square> squares;
deque<Button> buttons;



// Variables to store current color, initialize to black
float red = 0.0, green = 0.0, blue = 0.0;

// Store the width and height of the window
int width = 640, height = 640;

//-------------------------------------------------------
// A function to draw the scene
//-------------------------------------------------------
void appDrawScene() {
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set background color to white
	glClearColor(1.0, 1.0, 1.0, 1.0);

	// Set up the transformations stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set the color to the current values of the global vars
	glColor3f(red, green, blue);

	// // Set point size
	glPointSize(6);

	// Draw a point at the bottom-right
	glBegin(GL_POINTS);

	glVertex2f(-0.625, -0.925);

	glEnd();

	// Draw all the points stored in the double-ended queue
	for (int i = 0; i < points.size(); i++) {

		points[i].draw();

	}

	// Draw all squares
	for( int n = 0; n < squares.size(); n++ ) {

		squares[n].draw();

	}

	// Draw all buttons
	for( int n = 0; n < buttons.size(); n++ ) {

		buttons[n].draw();

	}

	// We have been drawing everything to the back buffer
	// Swap the buffers to see the result of what we drew
	glFlush();
	glutSwapBuffers();
}

//-------------------------------------------------------
// A function to convert window coordinates to scene
// We use it when a mouse event is handled
// Arguments: 	
//	x, y - the coordinates to be updated
//-------------------------------------------------------
void windowToScene(float& x, float& y) {
	x = (2.0f*(x / float(width))) - 1.0f;
	y = 1.0f - (2.0f*(y / float(height)));
}

//-------------------------------------------------------
// A function to handle window resizing
// Called every time the window is resized
// Arguments: 	
//	b    - mouse button that was clicked, left or right
//	s 	 - state, either mouse-up or mouse-down
//	x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appReshapeFunc(int w, int h) {
	// Window size has changed
	width = w;
	height = h;

	double scale, center;
	double winXmin, winXmax, winYmin, winYmax;

	// Define x-axis and y-axis range
	const double appXmin = -1.0;
	const double appXmax = 1.0;
	const double appYmin = -1.0;
	const double appYmax = 1.0;

	// Define that OpenGL should use the whole window for rendering
	glViewport(0, 0, w, h);

	// Set up the projection matrix using a orthographic projection that will
	// maintain the aspect ratio of the scene no matter the aspect ratio of
	// the window, and also set the min/max coordinates to be the disered ones
	w = (w == 0) ? 1 : w;
	h = (h == 0) ? 1 : h;

	if ((appXmax - appXmin) / w < (appYmax - appYmin) / h) {
		scale = ((appYmax - appYmin) / h) / ((appXmax - appXmin) / w);
		center = (appXmax + appXmin) / 2;
		winXmin = center - (center - appXmin)*scale;
		winXmax = center + (appXmax - center)*scale;
		winYmin = appYmin;
		winYmax = appYmax;
	}
	else {
		scale = ((appXmax - appXmin) / w) / ((appYmax - appYmin) / h);
		center = (appYmax + appYmin) / 2;
		winYmin = center - (center - appYmin)*scale;
		winYmax = center + (appYmax - center)*scale;
		winXmin = appXmin;
		winXmax = appXmax;
	}

	// Now we use glOrtho to set up our viewing frustum
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(winXmin, winXmax, winYmin, winYmax, -1, 1);
}


/**
	Menu code
**/
// draw square menu button code
Point pnt( -0.925, -0.875 );
Point spnt( -0.9, -0.9, 0.5, 0, 0.5 );
Square sqr( &spnt, 0.05f );
void drawSquareClck() {

	sqr.invertColor();
	brush = SQUARE;

}

// draw point menu button code
Point pnt1( -0.8, -0.875 );
Point pnt_label( -0.75, -0.925, 0.8, 0.5, 0 );
void drawPointClck() {

	pnt_label.invertColor();
	brush = POINT;

}

/**
	Creates the menu button the user can click to change the brush
**/	
void createMenu() {

	// draw square menu button
	Button draw_square_btn( &pnt, &sqr, SQUARE, &drawSquareClck );
	buttons.push_front( draw_square_btn );
	
	// draw point menu button
	Button draw_point_btn( &pnt1, &pnt_label, POINT, &drawPointClck );
	buttons.push_front( draw_point_btn );

}

/**
	Draws a shape when the mouse clicks the canvas
**/
void drawOnClick( Point * mouse ) {
    
    if( brush == POINT )
        // Add a point with with coordinates matching the
        // current mouse position, and the current color values
        points.push_front( *mouse );
    else if( brush == SQUARE )
        // Draw a squares
        squares.push_front( Square( mouse ) );

}


//-------------------------------------------------------
// A function to handle mouse clicks
// Called every time the mouse button goes up or down
// Arguments: 	
//	b    - mouse button that was clicked, left or right
//	s 	 - state, either mouse-up or mouse-down
//	x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appMouseFunc(int b, int s, int x, int y) {
	// Convert from Window to Scene coordinates
	float mx = (float)x;
	float my = (float)y;

	windowToScene(mx, my);

	Point point = Point(mx, my, red, green, blue);
	bool btn_clicked = false;

	// check if any of our buttons are clicked
	for( int n = 0; n < buttons.size(); n++ ) {

		btn_clicked = buttons[n].isClicked( &point, true );
		
		// only evalute one click for one button
		if( btn_clicked ) break;

	}

	// don't draw when button is clicked
	if( !btn_clicked )
		drawOnClick( &point );

	// Redraw the scene by calling appDrawScene above
	// so that the point we added above will get painted
	glutPostRedisplay();
}


//-------------------------------------------------------
// A function to handle mouse dragging
// Called every time mouse moves while button held down
// Arguments: 	
//	x, y - current coordinates of the mouse
//-------------------------------------------------------
void appMotionFunc(int x, int y) {
	// Convert from Window to Scene coordinates
	float mx = (float)x;
	float my = (float)y;

	windowToScene(mx, my);

	if( brush == POINT)
		// Similar behavior to click handler. This function
		// allows us to paint free hand with the mouse.
		points.push_front(Point(mx, my, red, green, blue));

	// Again, we redraw the scene
	glutPostRedisplay();
}

//-------------------------------------------------------
// A function to handle keyboard events
// Called every time a key is pressed on the keyboard
// Arguments: 	
//	key  - the key that was pressed
//	x, y - coordinates of the mouse when key is pressed
//-------------------------------------------------------
void appKeyboardFunc(unsigned char key, int x, int y) {
	// Define what should happen for a given key press 
	switch (key) {
		// Space was pressed. Erase all points
	case ' ':
		points.clear();
		break;

		// Escape was pressed. Quit the program
	case 27:
		exit(0);
		break;

		// The "r" key was pressed. Set global color to red
	case 'r':
		red = 1.0;
		green = 0.0;
		blue = 0.0;
		break;

		// The "g" key was pressed. Set global color to green
	case 'g':
		red = 0.0;
		green = 1.0;
		blue = 0.0;
		break;

		// The "b" key was pressed. Set global color to blue
	case 'b':
		red = 0.0;
		green = 0.0;
		blue = 1.0;
		break;

		// The "k" key was pressed. Set global color to black
	case 'k':
		red = 0.0;
		green = 0.0;
		blue = 0.0;
		break;

		// The "w" key was pressed. Set global color to white
	case 'w':
		red = 1.0;
		green = 1.0;
		blue = 1.0;
		break;

		// The 's' key was pressed. Draw squares on mouse click
	case 's':
	case 'S':
		brush = SQUARE;
		break;

		// The 'p' key was pressed. Draw squares on mouse click
	case 'p':
	case 'P':
		brush = POINT;
		break;
	}

	// After all the state changes, redraw the scene
	glutPostRedisplay();
}


int main(int argc, char** argv) {
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	// Setup window position, size, and title
	glutInitWindowPosition(20, 60);
	glutInitWindowSize(width, height);
	glutCreateWindow("CSE165 OpenGL Demo");

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);


	// Set callback for drawing the scene
	glutDisplayFunc(appDrawScene);

	// Set callback for resizing th window
	glutReshapeFunc(appReshapeFunc);

	// Set callback to handle mouse clicks
	glutMouseFunc(appMouseFunc);

	// Set callback to handle mouse dragging
	glutMotionFunc(appMotionFunc);

	// Set callback to handle keyboad events
	glutKeyboardFunc(appKeyboardFunc);

	// menu init
	createMenu();

	// Start the main loop
	glutMainLoop();
}