#include "RuntimeError.h"
#include "ShaderProgram.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

ShaderProgram::ShaderProgram(std::string_view vertex_shader_path, std::string_view fragment_shader_path)
{

	GLuint vertex_shader{ CompileShader(GetFileContents(vertex_shader_path), GL_VERTEX_SHADER) };
	GLuint fragment_shader{ CompileShader(GetFileContents(fragment_shader_path), GL_FRAGMENT_SHADER) };

	m_shader_program = glCreateProgram();
	glAttachShader(m_shader_program, vertex_shader);
	glAttachShader(m_shader_program, fragment_shader);
	glLinkProgram(m_shader_program);

	GLint linked{ 0 };
	glGetProgramiv(m_shader_program, GL_LINK_STATUS, &linked);
	if (linked == GL_FALSE)
	{
		GLint max_len{};
		glGetProgramiv(m_shader_program, GL_INFO_LOG_LENGTH, &max_len);
		std::vector<GLchar> infolog(max_len);
		glGetProgramInfoLog(m_shader_program, max_len, &max_len, &infolog[0]);
		glDeleteProgram(m_shader_program);
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
	}
	glDetachShader(m_shader_program, vertex_shader);
	glDetachShader(m_shader_program, fragment_shader);

}

void ShaderProgram::Use() const
{
	glUseProgram(m_shader_program);
}

void ShaderProgram::Reset() const
{
	glUseProgram(0);
}

GLuint ShaderProgram::GetUniformLocation(std::string_view name)
{
	return glGetUniformLocation(m_shader_program, name.data());

}

void ShaderProgram::SetUniformMatrix4(GLuint location, glm::mat4 &matrix)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void ShaderProgram::SetUniformVector2(GLuint location, glm::vec2 &vector)
{
	glUniform2fv(location, 1, glm::value_ptr(vector));
}

void ShaderProgram::SetUniformFloat(GLuint location, GLfloat value)
{
	glUniform1f(location, value);
}

void ShaderProgram::SetUniformFloat3(GLuint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
	glUniform3f(location, v0, v1, v2);
}

GLuint ShaderProgram::CompileShader(const std::string &source, GLuint shader_type)
{
	GLuint shader{ glCreateShader(shader_type) };
	const char *c_source{ source.c_str() };
	glShaderSource(shader, 1, &c_source, 0);
	glCompileShader(shader);
	GLint compiled{ 0 };
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE)
	{
		GLint max_len{};
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_len);
		std::vector<GLchar> infolog(max_len);
		glGetShaderInfoLog(shader, max_len, &max_len, &infolog[0]);
		glDeleteShader(shader);

		switch (shader_type)
		{
		case GL_VERTEX_SHADER:
			std::cerr << "FAILED to compile VERTEX SHADER: \n";
			break;
		case GL_FRAGMENT_SHADER:
			std::cerr << "FAILED to compile FRAGMENT SHADER: \n";
			break;
		}
		for (auto element : infolog)
			std::cerr << element;
		std::cerr << '\n';
	}
	return shader;
}


std::string ShaderProgram::GetFileContents(std::string_view path) 
{
	std::fstream file{ path.data() };
	if (!file)
		std::cerr << "ShaderProgram.cpp::GetFileContents:: FAILED to open file: " << path.data() << '\n';
	std::stringstream contents{};
	contents << file.rdbuf();
	return contents.str();
}

