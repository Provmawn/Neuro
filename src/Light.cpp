#include "Light.h"

#include <utility>

Light::Light(RGBA color, glm::vec3 direction, GLfloat ambient_intensity, GLfloat diffuse_intensity)
	: m_color{ std::move(color) }
	, m_direction{ std::move(direction) }
	, m_ambient_intensity{ ambient_intensity }
	, m_diffuse_intensity{ diffuse_intensity }
{
}

void Light::SetUniforms(ShaderProgram &shader_program)
{
	// TODO: move this into shader along with any other use of uniforms (Window.cpp and Main.cpp)
	GLuint color_uniform{ shader_program.GetUniformLocation("directional_light.color") };
	GLuint direction_uniform{ shader_program.GetUniformLocation("directional_light.direction") };
	GLuint ambient_intensity_uniform{ shader_program.GetUniformLocation("directional_light.ambient_intensity") };
	GLuint diffuse_intensity_uniform{ shader_program.GetUniformLocation("directional_light.diffuse_intensity") };

	shader_program.SetUniformFloat3(color_uniform, m_color.m_red, m_color.m_green, m_color.m_green);
	shader_program.SetUniformFloat3(direction_uniform, m_direction.x, m_direction.y, m_direction.z);
	shader_program.SetUniformFloat(ambient_intensity_uniform, m_ambient_intensity);
	shader_program.SetUniformFloat(diffuse_intensity_uniform, m_diffuse_intensity);
}
