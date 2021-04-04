#include "ShaderProgram.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
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
	
	// initialze glfw
	if (!glfwInit())
	{
		std::cerr << "GFLW Init Failed!\n";
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	// use opengl version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// use core profile (not backwards compatible)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create a GLFW window
	GLFWwindow *window{ glfwCreateWindow(640, 480, "Hello World", NULL, NULL) };
	if (!window)
	{
		std::cerr << "GLFW Window Init Failed!\n";
		glfwTerminate();
		return -1;
	}


	// get buffer dimensions
	int buffer_width{};
	int buffer_height{};
	glfwGetFramebufferSize(window, &buffer_width, &buffer_height);

	// set the context to the window
	glfwMakeContextCurrent(window);

	// allow access to extensions
	glewExperimental = GL_TRUE;

	// initialize glew
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "GLEW Init Failed\n";
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	// setup viewport dimensions
	glViewport(0, 0, buffer_width, buffer_height);

	CreateTriangle();
	ShaderProgram shader_program{ "./src/shaders/shader.vs", "./src/shaders/shader.fs" };
	GLuint model_uniform{ shader_program.GetUniformLocation("model") };
	GLuint projection_uniform{ shader_program.GetUniformLocation("projection") };

	// perspective projection
	glm::mat4 projection_matrix = glm::mat4{ 1.0f };
	projection_matrix = glm::perspective(45.0f, static_cast<GLfloat>(buffer_width) / buffer_height, .1f, 100.0f);

	int degrees{ 0 };
	constexpr float to_radians{ std::numbers::pi / 180.0 };
	// loop while window is open
	while (!glfwWindowShouldClose(window))
	{
		// handle events / user input
		glfwPollEvents();

		glClearColor(.8f, .6f, .8f, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		degrees += 1.f;

		// view space

		// world space
		glm::mat4 model_matrix{ 1.0f };
		model_matrix = glm::translate(model_matrix, glm::vec3(0.f, 0.f, -5.5f));
		model_matrix = glm::rotate(model_matrix, degrees * to_radians, glm::vec3(1.0f, 0.0f, 0.0f));

		shader_program.Use();

		glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model_matrix));
		glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, glm::value_ptr(projection_matrix));

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)0);
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		shader_program.Reset();

		glfwSwapBuffers(window);
	}
	return 0;
}