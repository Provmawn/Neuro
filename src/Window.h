#ifndef WINDOW_H
#define WINDOW_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <array>
#include <memory>
#include <string>
#include <string_view>
#include <tuple>

class Window
{
private:
	// C++ Smart Pointer Deleter for unique_ptr<GLFWwindow>
	struct GLFWwindowDeleter
	{
		void operator()(GLFWwindow *window)
		{
			glfwDestroyWindow(window);
		}
	};
public:
	using window_ptr = std::unique_ptr<GLFWwindow, Window::GLFWwindowDeleter> ;

	Window() = delete;
	Window(int width, int height, std::string_view title);

	void PollEvents();
	void Clear();
	void SwapBuffers();

	std::tuple<int, int> GetDimensions() const;
	float GetAspectRatio() const;

	bool ShouldClose() const;

	static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

private:
	int m_width{};
	int m_height{};
	float m_aspect_ratio{};
	std::string m_title{};
	window_ptr m_window{};

	std::array<bool, 1024> keys{};
};

#endif