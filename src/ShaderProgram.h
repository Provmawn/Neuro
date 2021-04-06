#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

class ShaderProgram
{
public:
	ShaderProgram() = default;
	ShaderProgram(std::string_view vertex_shader_path, std::string_view fragment_shader_path);
	void Use() const;
	void Reset() const;

	GLuint GetUniformLocation(std::string_view name);
	void SetUniformMatrix4(GLuint location, glm::mat4 &matrix);
	void SetUniformVector2(GLuint location, glm::vec2 &vector);
	void SetUniformFloat(GLuint location, GLfloat value);

// ################################
// FIND A BETTER WAY TO SET UNIFORM
// ################################

private:
	GLuint m_shader_program{};

	GLuint CompileShader(const std::string &source, GLuint shader_type);
	std::string GetFileContents(std::string_view path);
};

#endif