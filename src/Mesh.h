#ifndef MESH_H
#define MESH_H

#include "ShaderProgram.h"
#include "Texture.h"

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
	void Rotate(float degrees, glm::vec3 direction);
	void RotateX(float degrees);
	void RotateY(float degrees);
	void RotateZ(float degrees);
	void Translate(glm::vec3 position);
	void TranslateX(float units);
	void TranslateY(float units);
	void TranslateZ(float units);
	void Scale(glm::vec3 scale);
	void ScaleX(float factor);
	void ScaleY(float factor);
	void ScaleZ(float factor);
	void UpdateTransform(ShaderProgram& shader_program);
	void Render(ShaderProgram& shader_program);
	void ComputeAverageNormal(int vertex_length, int normal_offset);
private:
	GLuint m_VAO{};
	GLuint m_EBO{};
	GLuint m_VBO{};
	std::vector<unsigned int> m_indices{};
	std::vector<float> m_vertices{};
};

#endif