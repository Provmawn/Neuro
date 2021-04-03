#include "ShaderProgram.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

GLuint VAO{};
GLuint VBO{};

	GLfloat vertices[]{
		// bottom left
		-0.5f, -0.5f, 0.0f,
		// bottom right
		0.5f, -0.5f, 0.0f,
		// top middle
		0.0f, 0.5f, 0.0f
	};
void CreateTriangle()
{

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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

	// loop while window is open
	while (!glfwWindowShouldClose(window))
	{
		// handle events / user input
		glfwPollEvents();

		glClearColor(.8f, .6f, .8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader_program.Use();

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		shader_program.Reset();

		glfwSwapBuffers(window);
	}
	return 0;
}