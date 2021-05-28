#version 330

in vec3 vertex_position;
in vec4 vertex_color;
in vec2 vertex_tex_coords;
in vec3 vertex_normal;
in vec3 vertex_fragment_position;
out vec4 color;


// Directional lighting / ambient lighting
struct DirectionalLight {
    vec3 color;
    vec3 direction;
    float ambient_intensity;
    float diffuse_intensity;
};

struct Material {
    float specular_intensity;
    float shine;
};

// texture
uniform sampler2D my_texture;

// ambient/diffuse lighting
uniform DirectionalLight directional_light;

// specular lighting
uniform Material material;

uniform vec3 eye_position;

uniform vec2 resolution;
uniform vec2 cursor;
uniform float time;

float n_sin(float value) {
	return sin(value) / 2.0f + 0.5f;
}

void main () {
    // Ambient lighting
    vec4 ambient_color = vec4(directional_light.color, 1.0f) * directional_light.ambient_intensity;

    // Diffuse Lighting
    float diffuse_factor = max(dot(normalize(vertex_normal), normalize(directional_light.direction)), 0.0f);
    vec4 diffuse_color = vec4(directional_light.color, 1.0f) * directional_light.diffuse_intensity * diffuse_factor;

    // Specular Lighting
    vec4 specular_color = vec4(0.0f, 0.0f, 0.0f, 0.0f);

    if (diffuse_factor > 0.0f) {
        vec3 fragment_lookat = normalize(eye_position - vertex_fragment_position);
        vec3 reflection = normalize(reflect(directional_light.direction, normalize(vertex_normal)));
        float specular_factor = dot(fragment_lookat, reflection);
        if (specular_factor > 0.0f) {
            specular_factor = pow(specular_factor, material.shine);
            specular_color = vec4(directional_light.color * material.specular_intensity * specular_factor, 1.0f);
        }
    }

    // Set the fragment color
	color = texture(my_texture, vertex_tex_coords) * (ambient_color + diffuse_color + specular_color);
}