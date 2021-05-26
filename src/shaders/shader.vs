#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex_coords;

out vec4 vertex_color;
out vec2 vertex_tex_coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main () {
	vertex_color = vec4(clamp(pos, 0.0, 1.0), 1.0);

	gl_Position = projection * view * model * vec4(pos, 1.0);

	vertex_tex_coords = tex_coords;
}