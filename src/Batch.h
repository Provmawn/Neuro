#ifndef BATCH_H
#define BATCH_H

#include "Mesh.h"
#include "ShaderProgram.h"
#include "Texture.h"

#include <memory>
#include <vector>

class Batch
{
public:
	Batch(std::vector<std::unique_ptr<Mesh>> meshes, Texture texture);

	void Render(ShaderProgram &shader_program);
private:
	std::vector<std::unique_ptr<Mesh>> m_meshes{};
	Texture m_texture{};
};
#endif

