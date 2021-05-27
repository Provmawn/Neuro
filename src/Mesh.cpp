#include "Mesh.h"

#include <iostream>
#include <random>
#include <utility>

Mesh::Mesh(std::vector<unsigned int> indices, std::vector<float> vertices)
	: m_indices{ std::move(indices) }
	, m_vertices{ std::move(vertices) }
{
	// ###########################################################################
	// # Don't forget that this might break the code if your vertex size changes #
	// ###########################################################################

	constexpr int vertex_length{ 8 };
	constexpr int normal_offset{ 5 };
	ComputeAverageNormal(vertex_length, normal_offset);

	// ###########################################################################

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

	// vertex position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
	glEnableVertexAttribArray(0);
	// texture coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);
	// normals 
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(vertices[0]) * 5));
	glEnableVertexAttribArray(2);


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
	// Update model matrix
	UpdateTransform(shader_program);

	// OpenGL rendering
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glDrawElements(GL_TRIANGLES, m_indices.size() * 3, GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::ComputeAverageNormal(int vertex_length, int normal_offset)
{
	for (int i{ 0 }; i < m_indices.size(); i += 3)
	{
		// Map indices to (x, y, z) in vertices in m_vertices
		unsigned int index_0{ m_indices[i] * vertex_length };
		unsigned int index_1{ m_indices[i + 1] * vertex_length };
		unsigned int index_2{ m_indices[i + 2] * vertex_length };

		// Create vectors using the (x, y, z)
		glm::vec3 vector_0 = glm::vec3(m_vertices[index_1] - m_vertices[index_0], m_vertices[index_1 + 1] - m_vertices[index_0 + 1], m_vertices[index_1 + 2] - m_vertices[index_0 + 2]);
		glm::vec3 vector_1 = glm::vec3(m_vertices[index_2] - m_vertices[index_0], m_vertices[index_2 + 1] - m_vertices[index_0 + 1], m_vertices[index_2 + 2] - m_vertices[index_0 + 2]);

		// Find the axis perpendicular to our vectors and normalize it
		glm::vec3 normal = glm::cross(vector_0, vector_1);
		normal = glm::normalize(normal);

		// Move the indices to the normal variable positions
		index_0 += normal_offset;
		index_1 += normal_offset;
		index_2 += normal_offset;

		m_vertices[index_0] += normal.x;
		m_vertices[index_0 + 1] += normal.y;
		m_vertices[index_0 + 2] += normal.z;

		m_vertices[index_1] += normal.x;
		m_vertices[index_1 + 1] += normal.y;
		m_vertices[index_1 + 2] += normal.z;

		m_vertices[index_2] += normal.x;
		m_vertices[index_2 + 1] += normal.y;
		m_vertices[index_2 + 2] += normal.z;
	}

	// Normalize each of the normal values we created
	for (int i{ 0 }; i < m_vertices.size() / vertex_length; ++i)
	{
		// Start position for each normals
		unsigned int offset = i * vertex_length + normal_offset;

		// Create a vector of the normal values we currently have
		glm::vec3 normals{ m_vertices[offset], m_vertices[offset + 1], m_vertices[offset + 2] };
		
		// Then normalize them
		normals = glm::normalize(normals);

		// Then paste them back into their positions
		m_vertices[offset] = normals.x;
		m_vertices[offset + 1] = normals.y;
		m_vertices[offset + 2] = normals.z;

	}
}

