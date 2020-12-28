#ifndef LIGHTING_H
#define LIGHTING_H
#include <GL/freeglut.h>

class Lighting {
public:
	//material properties
	const static GLfloat m_ambientAndDiffuse[4];
	const static GLfloat m_specular[4];
	const static GLfloat m_specularBall[4];
	const static GLfloat shininess_ball;
	//light properties
	const static GLfloat l_ambient[4];
	const static GLfloat spot_diffuse[4];
	const static GLfloat spot_specular[4];
	const static GLfloat spot_position[4] ;
	const static GLfloat spot_direction[4];
	const static GLfloat spot_angle;
	const static GLfloat spot_quadAtten ;
};
#endif // !LIGHTING_H
