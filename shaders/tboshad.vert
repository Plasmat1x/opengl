#version 450 core
layout (location = 0) in vec2 vertex;	// <vec2 position>
layout (location = 1) in vec2 texCoord; // <vec2 texCoords> in frag shader

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    gl_Position = projection * model * vec4(vertex, 0.0, 1.0);
    //gl_Position = projection * view * model * vec4(vertex, 0.0, 1.0);
    TexCoords = texCoord;
}