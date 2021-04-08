#ifndef PYRAMID_H
#define PYRAMID_H

#include "Mesh.h"
#include <array>

class Pyramid : public Mesh
{
public:
	Pyramid(const glm::vec3 &position);
	virtual void Transform();
	float degrees{};
private:
	glm::vec3 m_position{};

	// Shape of mesh
	static constexpr std::array<unsigned int, 12> s_indices{
		2, 0, 1, // front face
		2, 1, 3, // right face
		2, 3, 0, // left face
		0, 3, 1 // bottom face
	};
	static constexpr std::array<float, 12> s_vertices{
		// bottom left
		-1.f, -1.f, 0.0f,
		// bottom right
		1.f, -1.f, 0.0f,
		// top middle
		0.0f, 1.f, 0.0f,
		// bottom z-axis
		0.0f, -1.f, -1.f
	};
};
#endif