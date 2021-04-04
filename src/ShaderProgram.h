#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

class ShaderProgram
{
public:
	enum class UniformType
	{
		FLOAT_1,
		FLOAT_2,
		FLOAT_3,
		FLOAT_4,
		INT_1,
		INT_2,
		INT_3,
		INT_4,
		UINT_1,
		UINT_2,
		UINT_3,
		UINT_4,

		MAX_ELEMENTS
	};
	ShaderProgram() = default;
	ShaderProgram(std::string_view vertex_shader_path, std::string_view fragment_shader_path);
	void Use() const;
	void Reset() const;

	GLuint GetUniformLocation(std::string_view name);

// ################################
// FIND A BETTER WAY TO SET UNIFORM
// ################################
	template<typename T>
	void SetUniform(std::string_view name, UniformType type, std::vector<T> values);

private:
	GLuint m_shader_program{};

	GLuint CompileShader(const std::string &source, GLuint shader_type);
	std::string GetFileContents(std::string_view path);
};

// ################################
// FIND A BETTER WAY TO SET UNIFORM
// ################################
template <typename T>
void ShaderProgram::SetUniform(std::string_view name, ShaderProgram::UniformType type, std::vector<T> values)
{
	GLint location{ glGetUniformLocation(m_shader_program, name.data()) };
	switch (type)
	{
	case ShaderProgram::UniformType::FLOAT_1:
		glUniform1f(location, values[0]);
		break;
	case ShaderProgram::UniformType::FLOAT_2:
		glUniform2f(location, values[0], values[1]);
		break;
	case ShaderProgram::UniformType::FLOAT_3:
		glUniform3f(location, values[0], values[1], values[2]);
		break;
	case ShaderProgram::UniformType::FLOAT_4:
		glUniform4f(location, values[0], values[1], values[2], values[3]);
		break;
	case ShaderProgram::UniformType::INT_1:
		glUniform1i(location, values[0]);
		break;
	case ShaderProgram::UniformType::INT_2:
		glUniform2i(location, values[0], values[1]);
		break;
	case ShaderProgram::UniformType::INT_3:
		glUniform3i(location, values[0], values[1], values[2]);
		break;
	case ShaderProgram::UniformType::INT_4:
		glUniform4i(location, values[0], values[1], values[2], values[3]);
		break;
	case ShaderProgram::UniformType::UINT_1:
		glUniform1ui(location, values[0]);
		break;
	case ShaderProgram::UniformType::UINT_2:
		glUniform2ui(location, values[0], values[1]);
		break;
	case ShaderProgram::UniformType::UINT_3:
		glUniform3ui(location, values[0], values[1], values[2]);
		break;
	case ShaderProgram::UniformType::UINT_4:
		glUniform4ui(location, values[0], values[1], values[2], values[3]);
		break;
	default:
		std::cerr << "Invalid uniform type\n";
	}
}
#endif