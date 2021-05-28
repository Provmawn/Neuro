#include "Camera3D.h"

Camera3D::Camera3D(glm::vec3 position, glm::vec3 camera_front, float move_speed, float sensitivity)
	: m_position{ position }
	, m_camera_front{ camera_front }
	, m_move_speed{ move_speed }
	, m_up{ glm::vec3(0.0f, 1.0f, 0.0f) }
	, m_sensitivity{ sensitivity }
{
}

glm::mat4 Camera3D::CalculateViewMatrix()
{
	return glm::lookAt(m_position, m_position + m_camera_front, m_up);
}

void Camera3D::SetUniforms(ShaderProgram& shader_program)
{
	GLuint eye_position{ shader_program.GetUniformLocation("eye_position") };

	shader_program.SetUniformFloat3(eye_position, m_position.x, m_position.y, m_position.z);
}

void Camera3D::HandleKeys(const std::array<bool, 1024>& keys, double delta_time)
{
	if (keys[GLFW_KEY_W])
		m_position += m_camera_front * m_move_speed * static_cast<float>(delta_time);
	if (keys[GLFW_KEY_A])
		m_position -= glm::cross(m_camera_front, m_up) * m_move_speed * static_cast<float>(delta_time);
	if (keys[GLFW_KEY_S])
		m_position -= m_camera_front * m_move_speed * static_cast<float>(delta_time);
	if (keys[GLFW_KEY_D])
		m_position += glm::cross(m_camera_front, m_up) * m_move_speed * static_cast<float>(delta_time);
	if (keys[GLFW_KEY_X])
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (keys[GLFW_KEY_C])
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Camera3D::AdjustCameraAngle(double x_cursor_offset, double y_cursor_offset)
{
	glm::vec3 direction{};
	direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	direction.y = sin(glm::radians(m_pitch));
	direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_camera_front = glm::normalize(direction);

	m_yaw += x_cursor_offset * m_sensitivity;
	m_pitch += y_cursor_offset * m_sensitivity;

	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;
}
