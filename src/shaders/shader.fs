#version 330

in vec3 vertex_position;
in vec4 vertex_color;
in vec2 vertex_tex_coords;
in vec3 vertex_normal;
out vec4 color;

// texture
uniform sampler2D my_texture;

// Directional lighting / ambient lighting
struct DirectionalLight {
    vec3 color;
    vec3 direction;
    float ambient_intensity;
    float diffuse_intensity;
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

    float diffuse_factor = max(dot(normalize(vertex_normal), normalize(directional_light.direction)), 0.0f);
    vec4 diffuse_color = vec4(directional_light.color, 1.0f) * directional_light.diffuse_intensity * diffuse_factor;
	color = texture(my_texture, vertex_tex_coords) * (ambient_color + diffuse_color);
	//color = vec4(vertex_color.x, vertex_color.y, vertex_color.z, 1.0f);
}