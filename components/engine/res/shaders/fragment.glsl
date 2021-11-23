#version 330 core

out vec4 fragColor;

uniform vec3 u_color;
uniform vec3 u_light_position;
uniform vec3 u_light_color;
uniform sampler2D u_texture;

in vec3 v_frag_position;
in vec3 v_normal;
in vec2 v_textureCoords;

void main()
{
  float ambient_strength = 0.1;
  vec3 ambient = ambient_strength * u_light_color;

  vec3 norm = normalize(v_normal);
  vec3 light_dir = normalize(u_light_position - v_frag_position);
  float diff = max(dot(v_normal, light_dir), 0.0);
  vec3 diffuse = diff * u_light_color;

  vec3 result = (ambient + diffuse) * u_color;
  fragColor = texture(u_texture, v_textureCoords) * vec4(result, 1.0);
}
