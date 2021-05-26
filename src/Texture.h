#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

#include <string>
#include <string_view>

class Texture
{
public:
	Texture();
	Texture(std::string_view path);

	void Load();
	void Use();
	void Clear();

private:
	GLuint m_ID{};
	int m_width{};
	int m_height{};
	int m_bit_depth{};
	std::string m_path{};
};

#endif

