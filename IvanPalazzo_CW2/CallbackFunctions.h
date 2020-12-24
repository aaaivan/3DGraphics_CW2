#ifndef CALLBACK_FUNCTIONS_H
#define CALLBACK_FUNCTIONS_H
#include <GL\freeglut.h>

void display(void);
void reshape(GLint width, GLint height);
void keyboard(unsigned char key, GLint x, GLint y);
void special(GLint key, GLint x, GLint y);
void setup(void);
void update(GLint index);
void createMenu(void);
void mainMenu(GLint option);

#endif // !CALLBACK_FUNCTIONS_H
