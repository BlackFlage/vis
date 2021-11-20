#version 330 core

layout (location = 0) in vec3 in_position;

uniform mat4 u_model;
uniform mat4 u_view;

void main()
{
  gl_Position = u_view * u_model * vec4(in_position, 1.0);
}
