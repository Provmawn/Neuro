#ifndef WINDOW_H
#define WINDOW_H
#include "ShaderProgram.h"

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
	const std::array<bool, 1024>& GetKeys() const;

	void SetUniforms(ShaderProgram &shader_program);

	std::tuple<int, int> GetDimensions() const;
	float GetAspectRatio() const;
	std::tuple<double, double> GetCursorPosition() const;

	bool ShouldClose() const;

	void UpdateDeltaTime();
	double GetDeltaTime() const;

	static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void CursorCallback(GLFWwindow *window, double xpos, double ypos);

private:
	int m_width{};
	int m_height{};
	float m_aspect_ratio{};
	double m_cursor_x{};
	double m_cursor_y{};
	double m_cursor_prev_x{};
	double m_cursor_prev_y{};
	std::string m_title{};
	window_ptr m_window{};

	double m_current_delta_time{};
	double m_prev_delta_time{};

	std::array<bool, 1024> m_keys{};
};

#endif