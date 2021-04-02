#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

GLuint VAO{};
GLuint VBO{};
GLuint shader_program{};

// vertex shader
static const char* vertexsource{
"#version 330\n"
"layout (location = 0) in vec3 pos;\n"
"void main () {\n"
"gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);\n"
"}\n"
};

static const char* fragsource{
"#version 330\n"
"out vec4 color;\n"
"void main () {\n"
"color = vec4(1.0, 0.0, 0.0, 1.0);\n"
"}\n"
 };

void CompileShaders()
{
	GLuint vertexshader{ glCreateShader(GL_VERTEX_SHADER) };
	glShaderSource(vertexshader, 1, &vertexsource, 0);
	glCompileShader(vertexshader);
	GLint compiled{ 0 };
	glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE)
	{
		GLint max_len{};
		glGetShaderiv(vertexshader, GL_INFO_LOG_LENGTH, &max_len);
		std::vector<GLchar> infolog(max_len);
		glGetShaderInfoLog(vertexshader, max_len, &max_len, &infolog[0]);
		glDeleteShader(vertexshader);

		std::cout << "Failed to compile vertex shader: \n";
		for (auto element : infolog)
			std::cout << element;
		std::cout << '\n';
	}
	std::cout << "vertex shader compilation successful!\n";


	GLuint fragshader{ glCreateShader(GL_FRAGMENT_SHADER) };
	glShaderSource(fragshader, 1, &fragsource, 0);
	glCompileShader(fragshader);
	glGetShaderiv(fragshader, GL_COMPILE_STATUS, &compiled);
	if (compiled == GL_FALSE)
	{
		GLint max_len{};
		glGetShaderiv(fragshader, GL_INFO_LOG_LENGTH, &max_len);
		std::vector<GLchar> infolog(max_len);
		glGetShaderInfoLog(fragshader, max_len, &max_len, &infolog[0]);
		glDeleteShader(fragshader);

		std::cout << "Failed to compile fragment shader: \n";
		for (auto element : infolog)
			std::cout << element;
		std::cout << '\n';
	}
	std::cout << "fragment shader compilation successful!\n";
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertexshader);
	glAttachShader(shader_program, fragshader);
	glLinkProgram(shader_program);

	GLint linked{ 0 };
	glGetProgramiv(shader_program, GL_LINK_STATUS, &linked);
	if (linked == GL_FALSE)
	{
		GLint max_len{};
		glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &max_len);
		std::vector<GLchar> infolog(max_len);
		glGetProgramInfoLog(shader_program, max_len, &max_len, &infolog[0]);
		glDeleteProgram(shader_program);
		glDeleteShader(vertexshader);
		glDeleteShader(fragshader);
	}
	glDetachShader(shader_program, vertexshader);
	glDetachShader(shader_program, fragshader);
}

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
	CompileShaders();

	// loop while window is open
	while (!glfwWindowShouldClose(window))
	{
		// handle events / user input
		glfwPollEvents();

		glClearColor(.8f, .6f, .8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shader_program);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glUseProgram(0);

		glfwSwapBuffers(window);
	}
	return 0;
}