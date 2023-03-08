#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <iostream>
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;

float alfa_angle = 0.0f;
float beta_angle = 0.0f;
float poscamx = 1.0f;
float poscamy = 1.0f;
float poscamz = 1.0f;

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


void build_cilindro(float radius, float height, int slices) {
	int i;
	float angle = (2 * M_PI / slices)  ;

	glBegin(GL_TRIANGLES);
	//printf("eNTROU");
	glColor3f(1, 1, 1);
	for (i = 0;i < slices;i+=1) {
		/*
		cout << "iteracao "<< endl;
		cout << i << endl;

		cout << "\n" << endl;
		*/
		float xm1 = sin(i * angle) * radius;
		float xm2 = sin((i+1) * angle) * radius;
		float zm1 = cos(i * angle) * radius;
		float zm2 = cos((i + 1) * angle) * radius;

		glVertex3f(0.0f, (height/2), 0.0f);
		glVertex3f(xm1, (height / 2), zm1);
		glVertex3f(xm2, (height / 2), zm2);
		
		/*
		cout << xm1 << endl;
		cout << zm1 << endl;
		cout << "\n" << endl;

		cout << xm2 << endl;
		cout << zm2 << endl;
		cout << "\n" << endl;
		*/
	
		glVertex3f(sin(i * angle) * radius, (height / 2), cos(i * angle) * radius);
		glVertex3f(sin(i * angle) * radius, (-height / 2), cos(i * angle) * radius);
		glVertex3f(sin((i + 1) * angle) * radius, (height / 2), cos((i + 1) * angle) * radius);
		
		glVertex3f(sin((i + 1) * angle) * radius, (height / 2), cos((i + 1) * angle) * radius);
		glVertex3f(sin(i * angle) * radius, (-height / 2), cos(i * angle) * radius);
		glVertex3f(sin((i+1) * angle) * radius, (-height / 2), cos((i+1) * angle) * radius);

		glVertex3f(sin(i * angle) * radius, -(height / 2), cos(i * angle) * radius);
		glVertex3f(0.0f, -(height / 2), 0.0f);
		glVertex3f(sin((i + 1) * angle) * radius, -(height / 2), cos((i + 1) * angle) * radius);
	}
	glEnd();

}



void renderScene(void)
{
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// set camera
	glLoadIdentity();
	gluLookAt(poscamx, poscamy, poscamz,
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
	

	build_cilindro(1.0f,2.0f,10.0f);

	// End of frame
	glutSwapBuffers();
}
//alfa : angulo base beta:angulo altura
void eventSpecial_func(int keycode, int x, int y) {
	if (keycode == GLUT_KEY_LEFT) {
		alfa_angle -= 0.01;
	}
	if (keycode == GLUT_KEY_RIGHT) {
		alfa_angle += 0.01;
	}
	if (keycode == GLUT_KEY_UP) {
		beta_angle += 0.01;
	}
	if (keycode == GLUT_KEY_DOWN) {
		beta_angle -= 0.01;
	}
	if (beta_angle > M_PI/2) { beta_angle = M_PI / 2; }
	if (beta_angle < 0) { beta_angle = 0; }
	poscamx = 4 * cos(beta_angle) * sin(alfa_angle);
	poscamz = 4 * cos(beta_angle) * cos(alfa_angle);
	poscamy = 4 * sin(beta_angle);
	glutPostRedisplay();
}

void eventKeyboard_func(unsigned char keycode, int x, int y) {
	
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	// put GLUT’s init here
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 1200);
	glutCreateWindow("CG3");
	
	// put callback registry here
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutDisplayFunc(renderScene);
	glutSpecialFunc(eventSpecial_func);

	// some OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glPolygonMode(GL_FRONT, GL_LINE);

	
	// enter GLUT’s main cycle
	glutMainLoop();
	
	return 1;
}