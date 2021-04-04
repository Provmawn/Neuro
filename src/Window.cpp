#include "Window.h"
#include "RuntimeError.h"

Window::Window(int width, int height, std::string_view title)
	: m_width{ width }
	, m_height{ height }
	, m_aspect_ratio{ static_cast<float>(width) / height }
	, m_title{ title }
{
	// initialze glfw
	if (!glfwInit())
		throw RuntimeError("Window.cpp::Window::Window GLFW failed to initialize!\n");

	// enable opengl depth
	glEnable(GL_DEPTH_TEST);

	// use opengl version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// use core profile (not backwards compatible)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create a GLFW window
	window_ptr window{ glfwCreateWindow(m_width, m_height, m_title.data(), NULL, NULL) };
	m_window = std::move(window);
	if (!m_window)
	{
		glfwTerminate();
		throw RuntimeError("Window.cpp::Window::Window GLFW failed create a window!\n");
	}

	// get buffer dimensions
	glfwGetFramebufferSize(m_window.get(), &m_width, &m_height);

	// set the context to the window
	glfwMakeContextCurrent(m_window.get());


	// allow access to extensions
	glewExperimental = GL_TRUE;

	// initialize glew
	if (glewInit() != GLEW_OK)
	{
		m_window.reset();
		glfwTerminate();
		throw RuntimeError("Window.cpp::Window::Window GLEW failed to initialize!\n");
	}

	// setup viewport dimensions
	glViewport(0, 0, m_width, m_height);
}

// Check for events, keyboard, mouse, etc...
void Window::PollEvents()
{
	glfwPollEvents();
}

void Window::Clear()
{
	glClearColor(.8f, .6f, .8f, 1.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

// Swap buffers, usually at the end of main loop
void Window::SwapBuffers()
{
	glfwSwapBuffers(m_window.get());
}

// Used in while loop to constantly check conditions to close window
bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(m_window.get());
}

// Use structured bindings for this function
std::tuple<int, int> Window::GetDimensions() const
{
	return std::make_tuple(m_width, m_height);
}

// Calculated aspect ratio, can be used for projection matrix
float Window::GetAspectRatio() const
{
	return m_aspect_ratio;
}
