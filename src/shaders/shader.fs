#version 330

in vec3 vertex_position;
in vec4 vertex_color;
in vec2 vertex_tex_coords;
out vec4 color;

uniform sampler2D my_texture;

uniform vec2 resolution;
uniform vec2 cursor;
uniform float time;

float n_sin(float value) {
	return sin(value) / 2.0 + 0.5;
}

void main () {
	color = texture(my_texture, vertex_tex_coords) * vertex_color;
	//color = vec4(vertex_color.x, vertex_color.y, vertex_color.z, 1.0);
}