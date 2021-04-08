#include "Camera3D.h"
Camera3D::Camera3D(glm::vec3 position, glm::vec3 camera_front, float move_speed)
	: m_position{ position }
	, m_camera_front{ camera_front }
	, m_move_speed{ move_speed }
	, m_up{ glm::vec3(0.0f, 1.0f, 0.0f) }
{

}

glm::mat4 Camera3D::CalculateViewMatrix()

{
	return glm::lookAt(m_position, m_position + m_camera_front, m_up);

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
}
