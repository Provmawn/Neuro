#ifndef RGBA_H
#define RGBA_H
#include <cstdint>
#include <GL/glew.h>
class RGBA
{
public:
	RGBA() = default;
	RGBA(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	GLfloat m_red{};
	GLfloat m_green{};
	GLfloat m_blue{};
	GLfloat m_alpha{};
};
#endif