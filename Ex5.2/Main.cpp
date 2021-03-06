#include <stdlib.h>
#include <iostream>
#include "glut.h"
#include "Sphere.h"

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

Sphere sp_1(30, 20, 20);
Sphere sp_2(30, 20, 20);
static float lineColor[] = { 0.2f, 0.2f, 0.2f, 1 };

GLfloat lightPos_1[] = { 0.0f, 0.0f, 75.0f, 1.0f };
GLfloat lightPos_2[] = { 0.0f, 0.0f, 100.0f, 1.0f };
GLfloat specular_1[] = { 0.0f, 1.0f, 1.0f, 1.0f };
GLfloat specular_2[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat ambientLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat spotDir[] = { 0.0f, 0.0f, -1.0f };
GLfloat DIFFUSElight_1[] = { 0,1,1,1 };
GLfloat DIFFUSElight_2[] = { 1,0,0,1 };
void ChangeSize(int w, int h);
void SpecialKeys(int key, int x, int y);
void RenderScene();
void SetupRC();
void idle();
int main() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,400);
	glutCreateWindow("Spot Light");

	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);

	glutDisplayFunc(RenderScene);
	glutIdleFunc(idle);
	SetupRC();
	
	
	glutMainLoop();
}

void ChangeSize(int w, int h)
{
	GLfloat fAspect;

	// Prevent a divide by zero
	if (h == 0)
		h = 1;

	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish viewing volume
	fAspect = (GLfloat)w / (GLfloat)h;
	gluPerspective(35.0f, fAspect, 1.0f, 500.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -250.0f);
}

void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;

	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;

	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;

	if (key > 356.0f)
		xRot = 0.0f;

	if (key < -1.0f)
		xRot = 355.0f;

	if (key > 356.0f)
		yRot = 0.0f;

	if (key < -1.0f)
		yRot = 355.0f;

	// Refresh the Window

	glutPostRedisplay();
}

void RenderScene()
{
	
	glShadeModel(GL_SMOOTH);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//light 0
	glPushMatrix();
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	//glRotatef(xRot, 1.0f, 0.0f, 0.0f);

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos_1);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
	glColor3ub(0, 0, 255);
	glTranslatef(lightPos_1[0], lightPos_1[1], lightPos_1[2]);
	//glutSolidCone(4.0f, 6.0f, 15, 15);
	glPushAttrib(GL_LIGHTING_BIT);

	//glDisable(GL_LIGHTING);
	//glColor3ub(255, 255, 0);
	//glutSolidSphere(3.0f, 20, 20);

	// Restore lighting state variables
	glPopAttrib();

	// Restore coordinate transformations
	glPopMatrix();

	//light 1
	glPushMatrix();
	//glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);

	glLightfv(GL_LIGHT1, GL_POSITION, lightPos_2);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir);
	glColor3ub(0, 0, 255);
	glTranslatef(lightPos_2[0], lightPos_2[1], lightPos_2[2]);
	//glutSolidCone(4.0f, 6.0f, 15, 15);
	glPushAttrib(GL_LIGHTING_BIT);

	/*glDisable(GL_LIGHTING);
	glColor3ub(255, 255, 0);
	glutSolidSphere(3.0f, 20, 20);*/

	// Restore lighting state variables
	glPopAttrib();

	// Restore coordinate transformations
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, 40, 0);
	glColor3ub(125, 125, 125);
	sp_1.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -40, 0);
	glColor3ub(125, 125, 0);
	sp_2.draw();
	glPopMatrix();
	
	glutSwapBuffers();
}

void SetupRC()
{
	glEnable(GL_DEPTH_TEST); // Hidden surface removal
	glFrontFace(GL_CCW);     // Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);  // Do not try to display the back sides

	// Enable lighting
	glEnable(GL_LIGHTING);

	// Setup and enable light 0
	// Supply a slight ambient light so the objects can be seen
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	// The light is composed of just a diffuse and specular components
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DIFFUSElight_1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular_1);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos_1);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, DIFFUSElight_2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular_2);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos_2);

	// Specific spot effects
	// Cut off angle is 60 degrees
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 50.0f);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 50.0f);
	// Enable this light in particular
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);

	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// All materials hereafter have full specular reflectivity
	// with a high shine
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void idle()
{
	yRot += 0.07;
	xRot += 0.10;
	glutPostRedisplay();
}
