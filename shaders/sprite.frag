#version 330 core
in vec2 TexCoords;
out vec4 Color;

uniform sampler2D image;
uniform vec4 color;

void main()
{    
    Color = (color * texture(image, TexCoords));
}  