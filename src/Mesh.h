#ifndef MESH_H
#define MESH_H

#include "ShaderProgram.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

class Mesh
{
protected:
	glm::mat4 m_model_matrix{ 1.0f };
public:
	Mesh(std::vector<unsigned int> indices, std::vector<float> vertices);
	virtual void Transform();
	void UpdateTransform(ShaderProgram &shader_program);
	void Render();
private:
	GLuint m_VAO{};
	GLuint m_EBO{};
	GLuint m_VBO{};
	std::vector<unsigned int> m_indices{};
	std::vector<float> m_vertices{};
};

#endif