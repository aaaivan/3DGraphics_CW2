#include "Lighting.h"

const GLfloat Lighting::m_ambientAndDiffuse[4] = { 1,1,1,1 };
const GLfloat Lighting::m_specular[4] = { 0,0,0,1 };
const GLfloat Lighting::m_specularBall[4] = { 1,1,1,1 };
const GLfloat Lighting::shininess_ball = 50;

const GLfloat Lighting::l_ambient[4] = { 0.5f,0.4f, 0.3f, 1 };
const GLfloat Lighting::spot_diffuse[4] = { 0.4f,0.4f,0.4f,1 };
const GLfloat Lighting::spot_specular[4] = { 1,1,1,1 };
const GLfloat Lighting::spot_position[4] = { 0,2,0,1 };
const GLfloat Lighting::spot_direction[4] = { 0, -0.9f,-1 };
const GLfloat Lighting::spot_angle = 60;
const GLfloat Lighting::spot_quadAtten = 0;