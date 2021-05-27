#ifndef LIGHT_H
#define LIGHT_H

#include "RGBA.h"
#include "ShaderProgram.h"

class Light
{
public:
	Light() = default;
	Light(RGBA color, GLfloat ambient_intensity);

	void SetUniforms(ShaderProgram &shader_program);
private:
	RGBA m_color{};
	GLfloat m_ambient_intensity{};
};
#endif

