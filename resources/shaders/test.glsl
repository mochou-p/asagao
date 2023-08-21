// asagao/resources/shaders/test.glsl


#stage vertex
#version 460 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 uv;

out vec2 texcoords;

void main()
{
    gl_Position = position;
    texcoords   = uv;
}
#endstage


#stage fragment
#version 460 core

in vec2 texcoords;

out vec4 color;

uniform sampler2D u_texture;

void main()
{
    color = texture(u_texture, texcoords);
}
#endstage
