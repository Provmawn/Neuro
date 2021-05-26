#include "Texture.h"
#include "RuntimeError.h"

#include <stb_image.h>

#include <iostream>

Texture::Texture()
	: m_ID{ 0 }
	, m_width{ 0 }
	, m_height{ 0 }
	, m_bit_depth{ 0 }
	, m_path{}
{
}

Texture::Texture(std::string_view path)
	: m_path{ static_cast<std::string>(path) }
	, m_ID{ 0 }
	, m_width{ 0 }
	, m_height{ 0 }
	, m_bit_depth{ 0 }
{

}

void Texture::Load()
{
	static int i = 0;
	// Load our image
	unsigned char* texture_data{ stbi_load(m_path.data(), &m_width, &m_height, &m_bit_depth, 0) };
	std::cout << m_path << i++ << '\n';
	if (!texture_data)
		throw RuntimeError("Failed to find " + m_path);

	// Generate and bind our texture
	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);

	// Set texture wrapping on S/X and T/Y axes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set the texture min and mag filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Set the texture image for our texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);

	// Autogenerate a mipmap
	glGenerateMipmap(GL_TEXTURE_2D);

	// Unbind and free
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(texture_data);


}

void Texture::Use()
{
	// Set the texture unit for our sampler (GL_TEXTURE0 is usually enabled by default)
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::Clear()
{
	glDeleteTextures(1, &m_ID);
	m_ID = m_width = m_height = m_bit_depth = 0;
	m_path = "";
}
