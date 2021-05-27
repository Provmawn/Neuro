#version 330

in vec3 vertex_position;
in vec4 vertex_color;
in vec2 vertex_tex_coords;
out vec4 color;

// texture
uniform sampler2D my_texture;

// Directional lighting / ambient lighting
struct DirectionalLight {
    float ambient_intensity;
    vec3 color;
};

uniform DirectionalLight directional_light;

uniform vec2 resolution;
uniform vec2 cursor;
uniform float time;

float n_sin(float value) {
	return sin(value) / 2.0f + 0.5f;
}

void main () {
    vec4 ambient_color = vec4(directional_light.color, 1.0f) * directional_light.ambient_intensity;
	color = texture(my_texture, vertex_tex_coords) * ambient_color;
	//color = vec4(vertex_color.x, vertex_color.y, vertex_color.z, 1.0f);
}