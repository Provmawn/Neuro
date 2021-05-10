#include "Mesh.h"

#include <iostream>
#include <random>
#include <utility>

Mesh::Mesh(std::vector<unsigned int> indices, std::vector<float> vertices)
	: m_indices{ std::move(indices) }
	, m_vertices{ std::move(vertices) }
{
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	// Make sure unbind EBO after VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// this is a transform comment
void Mesh::Transform()
{
	m_model_matrix = glm::mat4(1.0f);
}

void Mesh::Rotate(float degrees, glm::vec3 direction)
{
	m_model_matrix = glm::rotate(m_model_matrix, glm::radians(degrees), direction);
}

void Mesh::RotateX(float degrees)
{
	m_model_matrix = glm::rotate(m_model_matrix, glm::radians(degrees), glm::vec3(1.f, 0.f, 0.f));
}

void Mesh::RotateY(float degrees)
{
	m_model_matrix = glm::rotate(m_model_matrix, glm::radians(degrees), glm::vec3(0.f, 1.f, 0.f));
}

void Mesh::RotateZ(float degrees)
{
	m_model_matrix = glm::rotate(m_model_matrix, glm::radians(degrees), glm::vec3(0.f, 0.f, 1.f));
}

void Mesh::Translate(glm::vec3 position)
{
	m_model_matrix = glm::translate(m_model_matrix, position);
}

void Mesh::TranslateX(float units)
{
	m_model_matrix = glm::translate(m_model_matrix, glm::vec3(units, 0.f, 0.f));
}

void Mesh::TranslateY(float units)
{
	m_model_matrix = glm::translate(m_model_matrix, glm::vec3(0.f, units, 0.f));
}

void Mesh::TranslateZ(float units)
{
	m_model_matrix = glm::translate(m_model_matrix, glm::vec3(0.f, 0.f, units));
}

void Mesh::Scale(glm::vec3 scale)
{
	m_model_matrix = glm::scale(m_model_matrix, scale);
}

void Mesh::ScaleX(float factor)
{
	m_model_matrix = glm::scale(m_model_matrix, glm::vec3(factor, 1.f, 1.f));
}

void Mesh::ScaleY(float factor)
{
	m_model_matrix = glm::scale(m_model_matrix, glm::vec3(1.f, factor, 1.f));
}

void Mesh::ScaleZ(float factor)
{
	m_model_matrix = glm::scale(m_model_matrix, glm::vec3(1.f, 1.f, factor));
}

void Mesh::UpdateTransform(ShaderProgram &shader_program)
{
	GLuint model_uniform{ shader_program.GetUniformLocation("model") };
	shader_program.SetUniformMatrix4(model_uniform, m_model_matrix);
	m_model_matrix = glm::mat4(1.0f);
}

void Mesh::Render(ShaderProgram &shader_program)
{
	UpdateTransform(shader_program);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glDrawElements(GL_TRIANGLES, m_indices.size() * 3, GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

