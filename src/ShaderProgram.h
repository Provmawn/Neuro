#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <string_view>

class ShaderProgram
{
public:
	ShaderProgram() = default;
	ShaderProgram(std::string_view vertex_shader_path, std::string_view fragment_shader_path);
	void Use() const;
	void Reset() const;
private:
	GLuint m_shader_program{};

	GLuint CompileShader(const std::string &source, GLuint shader_type);
	std::string GetFileContents(std::string_view path);
};
#endif