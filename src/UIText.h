#pragma once

#include <GL/freeglut.h> 
#include <string>

class UIText {
public:
	UIText(){}
	~UIText(){}

	void display(std::string string, float posX, float posY)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor3f(1.0f, 1.0f, 1.0f);
		glRasterPos2f(posX, posY);

		for (unsigned int i = 0; i < string.length(); ++i) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
		}

		glutPostRedisplay();
	}
};