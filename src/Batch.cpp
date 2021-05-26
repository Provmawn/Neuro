#include "Batch.h"

Batch::Batch(std::vector<std::unique_ptr<Mesh>> meshes, Texture texture)
	: m_meshes{ std::move(meshes) }
	, m_texture{ std::move(texture) }
{
}

void Batch::Render(ShaderProgram &shader_program)
{
	m_texture.Use();
	for (const auto& mesh : m_meshes)
	{
		mesh->Transform();
		mesh->Render(shader_program);
	}
}
