#include "Material.h"

Material::Material(GLfloat specular_intensity, GLfloat shine)
	: m_specular_intensity{ specular_intensity }
	, m_shine{ shine }
{
}

void Material::SetUniforms(ShaderProgram& shader_program)
{
	GLuint specular_intensity_uniform{ shader_program.GetUniformLocation("material.specular_intensity") };
	GLuint shine_uniform{ shader_program.GetUniformLocation("material.shine") };

	shader_program.SetUniformFloat(specular_intensity_uniform, m_specular_intensity);
	shader_program.SetUniformFloat(shine_uniform, m_shine);

}
