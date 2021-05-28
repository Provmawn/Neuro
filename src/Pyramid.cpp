#include "Pyramid.h"

#include <utility>

// The Mesh class takes a std::vector of indices and vertices but this pyramid class
// has an std::array of indices and vertices
// so this constructor turns the std::array into a std::vector in the base class
Pyramid::Pyramid(const glm::vec3 &position)
	: Mesh(std::move(std::vector<unsigned int>(s_indices.begin(), s_indices.end()))
		, std::move(std::vector<float>(s_vertices.begin(), s_vertices.end())))
	, degrees(rand())
{
	m_position = position;
}

// this is a transform
void Pyramid::Transform()
{
	//++degrees;
	m_model_matrix = glm::translate(m_model_matrix, m_position);
	//m_model_matrix = glm::rotate(m_model_matrix, glm::radians(degrees), glm::vec3(1.0f, 0.0f, 0.0f));
}
