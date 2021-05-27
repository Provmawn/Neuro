#include "Light.h"

#include <utility>

Light::Light(RGBA color, GLfloat ambient_intensity)
	: m_color{ std::move(color) }
	, m_ambient_intensity{ambient_intensity}
{
}

void Light::SetUniforms(ShaderProgram &shader_program)
{
	// TODO: move this into shader along with any other use of uniforms (Window.cpp and Main.cpp)
	GLuint ambient_intensity_uniform{ shader_program.GetUniformLocation("directional_light.ambient_intensity") };
	GLuint color_uniform{ shader_program.GetUniformLocation("directional_light.color") };

	shader_program.SetUniformFloat(ambient_intensity_uniform, m_ambient_intensity);
	shader_program.SetUniformFloat3(color_uniform, m_color.m_red, m_color.m_green, m_color.m_green);
}
