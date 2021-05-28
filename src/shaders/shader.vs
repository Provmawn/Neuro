#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex_coords;
layout (location = 2) in vec3 normal;

out vec4 vertex_color;
out vec2 vertex_tex_coords;
out vec3 vertex_normal;
out vec3 vertex_fragment_position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main () {
	vertex_color = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);

	gl_Position = projection * view * model * vec4(pos, 1.0f);

	vertex_tex_coords = tex_coords;
	vertex_normal = mat3(transpose(inverse(model))) * normal;

	// Get world coordinates
	vertex_fragment_position = (model * vec4(pos, 1.0f)).xyz;
}