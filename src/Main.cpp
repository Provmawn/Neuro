#include "Batch.h"
#include "Camera3D.h"
#include "Mesh.h"
#include "Pyramid.h"
#include "RuntimeError.h"
#include "ShaderProgram.h"
#include "Window.h"
#include "Texture.h"	// TODO: move this into mesh class


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>
#include <memory>
#include <numbers>
#include <random>
#include <utility>
#include <vector>


std::vector<std::unique_ptr<Mesh>> meshes{};

/*
void Fractal()
{
	static int count = 0;
	for (int i = 0; i < 120; ++i)
	{
		float scale = 15.f;
		float move = 15.f;
		float degrees = 45.f;

		// create start branch
		meshes[i]->ScaleY(scale);
		meshes[i]->Render(shader_program);

		if (count < 120)
		{
			// create left branch
			meshes[i]->TranslateY(move);
			meshes[i]->RotateZ(-degrees);
			meshes[i]->ScaleY(scale);
			meshes[i]->TranslateY(1.f);
			meshes[i]->Render(shader_program);
			Fractal()
			++count;

			// create right branch
			meshes[i]->TranslateY(move);
			meshes[i]->RotateZ(degrees);
			meshes[i]->ScaleY(scale);
			meshes[i]->TranslateY(1.f);
			meshes[i]->Render(shader_program);
			++count;
		}
	}
}
*/

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

	// Get Model and Projection matrices from vertex shader
	GLuint model_uniform{ shader_program.GetUniformLocation("model") };
	GLuint view_uniform{ shader_program.GetUniformLocation("view") };
	GLuint projection_uniform{ shader_program.GetUniformLocation("projection") };

	// Create Perspective Frustum
	glm::mat4 projection_matrix = glm::mat4{ 1.0f };
	constexpr float Y_FOV{ 45.0f };
	constexpr float INNER{ 0.1f };
	constexpr float OUTTER{ 200.0f };
	projection_matrix = glm::perspective(Y_FOV, window.GetAspectRatio(), INNER, OUTTER);

	// Create a 3D Camera
	constexpr glm::vec3 position{ glm::vec3(0.0f, 0.0f, -3.0f) };
	constexpr glm::vec3 front{ glm::vec3(0.0f, 0.0f, -1.0f) };
	constexpr float move_speed{ 20.f };
	constexpr float sensitvity{ 0.7f };
	Camera3D camera{ position, front, move_speed, sensitvity };

	std::uniform_real_distribution<float> die(-25.0f, 25.0f);
	std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	for (int i{ 0 }; i < 1000; ++i)
		meshes.emplace_back(std::make_unique<Pyramid>(glm::vec3(die(mersenne), die(mersenne), die(mersenne))));

	Texture texture{ "C:\\dev\\neuro\\Neuro\\src\\texture1.png" };
	texture.Load();

	Batch batch{ std::move(meshes), std::move(texture) };

	// Loop while the window is open
	while (!window.ShouldClose())
	{
		window.PollEvents();
		window.Clear();
		window.UpdateDeltaTime();

		// Handle Camera Translation
		camera.HandleKeys(window.GetKeys(), window.GetDeltaTime());

		// Handle Camera Rotation
		auto [x_cursor_offset, y_cursor_offset] { window.GetCursorOffset() };
		camera.AdjustCameraAngle(x_cursor_offset, y_cursor_offset);

		// Setup View Space
		glm::mat4 view_matrix{ 1.0f };
		view_matrix = camera.CalculateViewMatrix();

		// ###############################
		// BEGIN SHADER PROGRAM OPERATIONS
		// ###############################

		shader_program.Use();

		// sets the resolution, cursor position, and time uniforms
		window.SetUniforms(shader_program);

		// Update View Matrix in vertex shader
		shader_program.SetUniformMatrix4(view_uniform, view_matrix);

		// Update Projection Matrix in vertex shader
		shader_program.SetUniformMatrix4(projection_uniform, projection_matrix); 

		// ####################
		// BEGIN DRAWING MESHES
		// ####################

		batch.Render(shader_program);

		shader_program.Reset();

		window.SwapBuffers();
	}
	return 0;
}