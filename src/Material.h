#ifndef MATERIAL_H
#define MATERIAL_H

#include "ShaderProgram.h"

#include <GL/glew.h>

class Material
{
public:
	Material() = default;
	Material(GLfloat specular_intensity, GLfloat shine);

	void SetUniforms(ShaderProgram& shader_program);
private:
	GLfloat m_specular_intensity{};
	GLfloat m_shine{};
};
#endif
