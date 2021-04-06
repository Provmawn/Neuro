#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

class Mesh
{
public:
	Mesh(std::vector<unsigned int> indices, std::vector<float> vertices);
	void Draw();
private:
	GLuint m_VAO{};
	GLuint m_EBO{};
	GLuint m_VBO{};
	std::vector<unsigned int> m_indices{};
	std::vector<float> m_vertices{};
};

#endif