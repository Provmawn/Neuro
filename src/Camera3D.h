#ifndef CAMERA3D_H
#define CAMERA3D_h

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <array>

class Camera3D
{
public:
	Camera3D(glm::vec3 position, glm::vec3 m_camera_front, float move_speed);
	glm::mat4 CalculateViewMatrix();
	void HandleKeys(const std::array<bool, 1024> &keys, double delta_time);
private:
	glm::vec3 m_up{};
	glm::vec3 m_local_x{};
	glm::vec3 m_local_y{};
	glm::vec3 m_local_z{};
	glm::vec3 m_position{};
	glm::vec3 m_camera_front{};
	float m_move_speed;
};
#endif
