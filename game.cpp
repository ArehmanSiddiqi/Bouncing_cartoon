//#include <GL/gl.h>
//#include <GL/glut.h>
//============================================================================
// Name        : brickSlayerITC.cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Brick Slayer...
//============================================================================

#ifndef PACMAN_CPP_
#define PACMAN_CPP_
//#include "Board.h"
#include <gl/glew.h>
#include <GL/glut.h>
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
*  that is what dimensions (x and y) your game will have
*  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
* */
void SetCanvasSize(int width, int height) {
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void DrawGhost(int x/*starting x*/, int y/*starting y*/,
	ColorNames color/*color*/, float gw = 6/*Ghost Width in Units*/,
	float gh = 7/*Ghost Height in Units*/) {
	int ogw = 6, ogh = 7;

	glPushMatrix();
	float sx = (float)gw / ogw, sy = (float)gh / ogh;
	glTranslatef(x, y, 1);
	glScalef(sx, sy, 1);

	// Draw ghost
	DrawRoundRect(0, 1, 6, 3, colors[color]);
	DrawCircle(3, 4, 3.01, colors[color]);
	glPushMatrix();
	glScalef(0.9, 1.1, 1);
	//  legs
	DrawCircle(0.75, 1, 0.75, colors[color]);
	DrawCircle(3.25, 1, 0.75, colors[color]);
	DrawCircle(5.85, 1, 0.75, colors[color]);

	glPopMatrix();
	//	glPopMatrix();

	// eyes

	glPushMatrix();
	glScalef(0.9, 1.1, 1);
	DrawCircle(1.85, 3.95, 0.75, colors[WHITE]);
	DrawCircle(4.95, 3.95, 0.75, colors[WHITE]);
	glPopMatrix();

	// eyes
	DrawCircle(1.65, 4.25, 0.45, colors[BLUE]);
	DrawCircle(4.45, 4.25, 0.45, colors[BLUE]);
	glPopMatrix();
}

//Number of Vertices used to draw Pacman Circle...
// x= r cos (theta), y= r sin(theta)
const int npmvertices = 1220;
GLfloat pmvertices[npmvertices][2];
void InitPMVertices(float radius) {

	float hdegree = (M_PI - M_PI / 2.0) / 360.0;
	float angle = M_PI + M_PI / 6.0;
	for (int i = 0; i < npmvertices; ++i) {
		pmvertices[i][0] = radius * cos(angle);
		pmvertices[i][1] = radius * sin(angle);
		angle += hdegree;
	}
}

void DrawPacMan(float sx/*center x*/, float sy/*center y*/,
	float radius/*Radius*/, const ColorNames &colorname/*Pacman Colour*/) {

	glColor3fv(colors[colorname]); // set the circle color
	InitPMVertices(radius);
	glBegin(GL_TRIANGLE_FAN);
	glVertex4f(sx, sy, 0, 1);
	for (int i = 0; i < npmvertices; ++i)
		glVertex4f(sx + pmvertices[i][0], sy + pmvertices[i][1], 0, 1);
	glEnd();
	DrawCircle(sx - radius + radius / 2, sy + (radius - radius / 2),
		radius / 10, colors[BLACK]);
}
/*
* Main Canvas drawing function.
* */
//Board *b;
int balls[8][3];
int xx = 50, yy = 700 - 25;
bool flip[8];


void start()
{
	int x = 50, y = 540;
	int ron = 540;
	for (int i = 0; i < 8; i++)
	{
		balls[i][0] = x;
		balls[i][1] = y;
		balls[i][2] = ron-=10;
		flip[i] = false;
		x += 75;
		y -= 30;
	}
}

/*void bounce(int ron,int xx,int yy)
{
	if (ron <= 10) yy = 30;
	if (yy == 30){ flip = true; ron -= 75; }
	if (yy > ron) flip = false;

	if (flip == false)
	{
		yy -= 5;

	}
	if (flip == true)
	{
		yy += 5;
	}
}*/

void bounce2(int i)
{
	if (balls[i][1] <= 19) balls[i][1] = 15;
	else{
		if (balls[i][1] == 30){ flip[i] = true; balls[i][2] -= 60; }
		if (balls[i][1] > balls[i][2]) flip[i] = false;

		if (flip[i] == false)
		{
			balls[i][1] -= 5;

		}
		if (flip[i] == true)
		{
			balls[i][1] += 5;
		}
	}
}

void Display()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(1.0/*Red Component*/, 1.0/*Green Component*/,
		1.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT); //Update the colors


	for (int i = 0; i < 8; i++)
	{
		DrawCircle(balls[i][0], balls[i][1], 30, colors[BLUE]);
		bounce2(i);
		DrawCircle(balls[i][0] + 10, balls[i][1] + 10, 25, colors[RED]);
		bounce2(i);
		DrawCircle(balls[i][0] + 25, balls[i][1] + 25, 15, colors[GREEN]);
		DrawCircle(balls[i][0] + 20, balls[i][1] + 30, 3, colors[BLACK]);
		DrawCircle(balls[i][0] + 30, balls[i][1] + 30, 3, colors[BLACK]);
		cout <<"x= "<< balls[i][0] <<" y= " <<balls[i][1] << endl;
		bounce2(i);
	}
	
	//bounce(675,50,675);

	//DrawRoundRect(xx+ 50, yy - 50, 30, 30, colors[WHITE], 25);
	//
	//b->Draw();
	//int x, y;
	//b->GetInitPinkyPosition(x, y);
//	cout << x << "  y= " << y << endl << flush;
	//DrawGhost(x, y, PINK, 2 * b->GetCellSize(), 2 * b->GetCellSize());

	//b->GetInitPacmanPosition(x, y);
	//DrawPacMan(x, y, b->GetCellSize() - 2, YELLOW);

	//x = b->GetMidX();
	//cout << " midx= " << x;
	//DrawString(x - 60, 680, "Score = 000", colors[5]);
	//	glPopMatrix();
	glutPostRedisplay();
	glutSwapBuffers(); // do not modify this line..
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
* is pressed from the keyboard
*
* You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
*
* This function has three argument variable key conta ins the ASCII of the key pressed, while x and y tells the
* program coordinates of mouse pointer when key was pressed.
*
* */

void NonPrintableKeys(int key, int x, int y) {
	cout << "Calling" << endl;
	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
		xx-=10;
		cout << "left" << endl;

	}
	else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
		xx+=10;
	}
	else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
		yy+=10;
	}

	else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
		yy-=10;
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	* this function*/
	
	glutPostRedisplay();
	
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
* is pressed from the keyboard
* This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
* program coordinates of mouse pointer when key was pressed.
* */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == KEY_ESC/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}
}

/*
* This function is called after every 1000.0/FPS milliseconds
* (FPS is defined on in the beginning).
* You can use this function to animate objects and control the
* speed of different moving objects by varying the constant FPS.
*
* */
void Timer(int m) {

	// implement your functionality here

	// once again we tell the library to call our Timer function after next 1000/FPS
	//glutPostRedisplay();
	glutTimerFunc(1000.0 / FPS, Timer, 0);
}

/*
* our gateway main function
* */
int main(int argc, char*argv[]) {

	//b = new Board(20, 20); // create a new board object to use in the Display Function ...

	int width = 700, height = 650; // i have set my window size to be 800 x 600
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("CP's Pacman"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...
	
	start();
	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
	glutDisplayFunc(Display); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0 / FPS, Timer, 0);

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* PACMAN_CPP_ */
