#include "Camera3D.h"
#include "Mesh.h"
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
#include <utility>
#include <iostream>
#include <vector>

int main(int argc, const char *argv[])
{
	// #####################
	// TODO: SEPARATE THREAD
	// #####################
	// Create Window 
	constexpr int WIDTH{ 1080 };
	constexpr int HEIGHT{ 720 };
	constexpr std::string_view TITLE{ "NEURO Engine" };
	Window window{WIDTH, HEIGHT, TITLE};


	// #####################
	// TODO: SEPARATE THREAD
	// #####################
	// Create Shader Program
	ShaderProgram shader_program{ "./src/shaders/shader.vs", "./src/shaders/shader.fs" };

	// ###############
	// TODO: WAIT HERE
	// ###############

	std::vector<unsigned int> indices{
		2, 0, 1, // front face
		2, 1, 3, // right face
		2, 3, 0, // left face
		0, 3, 1 // bottom face
	};

	std::vector<float> vertices{
		// bottom left
		-1.f, -1.f, 0.0f,
		// bottom right
		1.f, -1.f, 0.0f,
		// top middle
		0.0f, 1.f, 0.0f,
		// bottom z-axis
		0.0f, -1.f, -1.f
	};

	Mesh p{ std::move(indices), std::move(vertices) };

	// Get Model and Projection matrices from vertex shader
	GLuint model_uniform{ shader_program.GetUniformLocation("model") };
	GLuint view_uniform{ shader_program.GetUniformLocation("view") };
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

	Camera3D camera{glm::vec3(0.0f,0.0f,-3.0f), glm::vec3(0.0f, 0.0f, -1.0f), 20.f};

	double current_time{};
	double prev_time{};

	// Loop while the window is open
	while (!window.ShouldClose())
	{
		window.PollEvents();
		window.Clear();
		window.UpdateDeltaTime();

		// World Space
		glm::mat4 model_matrix{ 1.0f };

		// Handle Camera Translation
		camera.HandleKeys(window.GetKeys(), window.GetDeltaTime());

		// Handle Camera Rotation
		auto [x_cursor_offset, y_cursor_offset] { window.GetCursorOffset() };
		camera.AdjustCameraAngle(x_cursor_offset, y_cursor_offset);

		std::cerr << " FUCK \n";
		// Setup View Space
		glm::mat4 view_matrix{ 1.0f };
		view_matrix = camera.CalculateViewMatrix();

		// temporary code used for spinning 3d object
		degrees += 1.f;
		model_matrix = glm::translate(model_matrix, glm::vec3(0.f, 0.f, -5.5f));
		model_matrix = glm::rotate(model_matrix, degrees * to_radians, glm::vec3(1.0f, 0.0f, 0.0f));

		// ###############################
		// BEGIN SHADER PROGRAM OPERATIONS
		// ###############################

		shader_program.Use();

		// sets the resolution, cursor position, and time uniforms
		window.SetUniforms(shader_program);

		// Update Model Matrix in vertex shader
		shader_program.SetUniformMatrix4(model_uniform, model_matrix);

		// Update View Matrix in vertex shader
		shader_program.SetUniformMatrix4(view_uniform, view_matrix);

		// Update Projection Matrix in vertex shader
		shader_program.SetUniformMatrix4(projection_uniform, projection_matrix); 


		// ####################
		// BEGIN DRAWING MESHES
		// ####################

		p.Draw();

		// ##################
		// END DRAWING MESHES
		// ##################

		// #############################
		// END SHADER PROGRAM OPERATIONS
		// #############################

		shader_program.Reset();


		window.SwapBuffers();
	}
	return 0;
}