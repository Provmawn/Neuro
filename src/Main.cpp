#include "RuntimeError.h"
#include "ShaderProgram.h"
#include "Window.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <memory>
#include <numbers>

GLuint VAO{};
GLuint VBO{};
GLuint EBO{};

unsigned int indices[]
{
	0, 1, 2, // front face
	1, 3, 2, // right face
	2, 0, 3, // left face
	3, 1, 0, // bottom face
};

GLfloat vertices[]{
	// bottom left
	-1.f, -1.f, 0.0f,
	// bottom right
	1.f, -1.f, 0.0f,
	// top middle
	0.0f, 1.f, 0.0f,
	// bottom z-axis
	0.0f, -1.f, -1.f
};

void CreateTriangle()
{

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	// IMPORTANT!: you should take care to unbind EBO after VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

int main()
{
	// Create Window
	constexpr int WIDTH{ 1080 };
	constexpr int HEIGHT{ 720 };
	constexpr std::string_view TITLE{ "NEURO Engine" };
	Window window{WIDTH, HEIGHT, TITLE};

	CreateTriangle();

	// Create Shader Program
	ShaderProgram shader_program{ "./src/shaders/shader.vs", "./src/shaders/shader.fs" };

	// Get Model and Projection matrices from vertex shader
	GLuint model_uniform{ shader_program.GetUniformLocation("model") };
	GLuint projection_uniform{ shader_program.GetUniformLocation("projection") };

	// Create Perspective Frustum
	glm::mat4 projection_matrix = glm::mat4{ 1.0f };
	constexpr float Y_FOV{ 45.0f };
	constexpr float INNER{ 0.1f };
	constexpr float OUTTER{ 100.0f };
	projection_matrix = glm::perspective(Y_FOV, window.GetAspectRatio(), INNER, OUTTER);

	// temporary code used for spinning 3d object
	int degrees{ 0 };
	constexpr float to_radians{ std::numbers::pi / 180.0 };

	// loop while window is open
	while (!window.ShouldClose())
	{
		window.PollEvents();
		window.Clear();

		// temporary code used for spinning 3d object
		degrees += 1.f;

		// view space

		// world space
		glm::mat4 model_matrix{ 1.0f };

		// temporary code used for spinning 3d object
		model_matrix = glm::translate(model_matrix, glm::vec3(0.f, 0.f, -5.5f));
		model_matrix = glm::rotate(model_matrix, degrees * to_radians, glm::vec3(1.0f, 0.0f, 0.0f));

		shader_program.Use();

		// Update Model Matrix in vertex shader
		glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model_matrix));

		// Update Projection Matrix in vertex shader
		glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, glm::value_ptr(projection_matrix));

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		shader_program.Reset();

		window.SwapBuffers();
	}
	return 0;
}