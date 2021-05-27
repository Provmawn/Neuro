#ifndef LIGHT_H
#define LIGHT_H

#include "RGBA.h"
#include "ShaderProgram.h"

#include <glm/glm.hpp>

class Light
{
public:
	Light() = default;
	Light(RGBA color, glm::vec3 direction, GLfloat ambient_intensity, GLfloat diffuse_intensity);

	void SetUniforms(ShaderProgram &shader_program);
private:
	RGBA m_color{};
	glm::vec3 m_direction{};
	GLfloat m_ambient_intensity{};
	GLfloat m_diffuse_intensity{};
};
#endif

