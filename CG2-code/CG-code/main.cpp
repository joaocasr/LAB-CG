#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <iostream>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

bool translate = false;

float angle1 = 0.0f;
float myx1 = 0.0f;
float myy1 = 1.0f;
float myz1 = 0.0f;

float angle2 = 0.0f;
float myx2 = 0.0f;
float myy2 = 0.0f;
float myz2 = 1.0f;

float tx = 0;
float ty = 0;
float tz = 0;

float ex = 1;
float ey = 1;
float ez = 1;


void changeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you can’t make a window with zero width).
	if (h == 0)
		h = 1;
	// compute window's aspect ratio
	float ratio = w * 1.0f / h;
	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load the identity matrix
	glLoadIdentity();
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// Set the perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void build_pyramid() {
	glBegin(GL_TRIANGLES);
		//firs triangle base in red
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		//second triangle base in red 
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		//first triangle side in green
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, 1.4f, 0.0f);
		//second triangle side in blue
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		glVertex3f(0.0f, 1.4f, 0.0f);
		glVertex3f(1.0f, 0.0f, -1.0f);
		//third triangle side in yellow
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 1.4f, 0.0f);
		glVertex3f(-1.0f, 0.0f, -1.0f);
		//forth triangle side in cyan
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 1.4f, 0.0f);
		glVertex3f(-1.0f, 0.0f, 1.0f);
	glEnd(); 
}



void renderScene(void)
{
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// set camera
	glLoadIdentity();
	gluLookAt(3.0f, 2.0f, 1.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
			// X axis in red
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(100.0f, 0.0f, 0.0f);
			// Y Axis in Green
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex3f(0.0f,-100.0f, 0.0f);
			glVertex3f(0.0f, 100.0f, 0.0f);
			// Z Axis in Blue
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.0f, 0.0f,0.0f);
			glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();

	glRotatef(angle1, myx1, myy1, myz1);
	glRotatef(angle2, myx2, myy2, myz2);

	glTranslatef(tx, ty, tz);
	

	glScalef(ex,ey,ez);

	build_pyramid();

	// End of frame
	glutSwapBuffers();
}

void eventSpecial_func(int keycode, int x, int y) {
	if (keycode == GLUT_KEY_LEFT) {
		printf("LEFT ARROW\n");
		angle1 += 5;
	}
	if (keycode == GLUT_KEY_RIGHT) {
		printf("RIGHT ARROW\n");
		angle1 -= 5;
	}
	if (keycode == GLUT_KEY_UP) {
		printf("UP ARROW\n");
		angle2 += 5;
	}
	if (keycode == GLUT_KEY_DOWN) {
		printf("DOWN ARROW\n");
		angle2 -= 5;
	}
	glutPostRedisplay();
}

void eventKeyboard_func(unsigned char keycode, int x, int y) {
	if (keycode == 'a') {
		translate = true;
		printf("a\n");
		tx += 0.1;
	}
	if (keycode == 'b') {
		printf("b\n");
		tx -= 0.1;
	}
	if (keycode == 'c') {
		printf("c\n");
		ty += 0.1;
	}
	if (keycode == 'd') {
		printf("d\n");
		ty -= 0.1;
	}
	if (keycode == 'e') {
		printf("e\n");
		tz += 0.1;
	}
	if (keycode == 'f') {
		printf("f\n");
		tz -= 0.1;
	}
	if (keycode == '+') {
		printf("+\n");
		ex += 0.5;
		ey += 0.5;
		ez += 0.5;
	}
	if (keycode == '-') {
		printf("-\n");
		ex -= 0.5;
		ey -= 0.5;
		ez -= 0.5;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	// put GLUT’s init here
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG2");
	
	// put callback registry here
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutDisplayFunc(renderScene);
	glutSpecialFunc(eventSpecial_func);
	glutKeyboardFunc(eventKeyboard_func);

	// some OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	// enter GLUT’s main cycle
	glutMainLoop();
	
	return 1;
}