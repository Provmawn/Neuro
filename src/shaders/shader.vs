#version 330

layout (location = 0) in vec3 pos;
out vec4 vertex_color;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main () {
	vertex_color = vec4(clamp(pos, 0.0, 1.0), 1.0);
	gl_Position = projection * model * vec4(pos, 1.0);
}