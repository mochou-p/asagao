// asagao/resources/shaders/test.glsl


#stage vertex
#version 460 core

layout (location = 0) in vec4 position;

void main()
{
    gl_Position = position;
}
#endstage

#stage fragment
#version 460 core

out vec4 FragColor;

void main()
{
    FragColor = vec4(0.0, 1.0, 0.0, 1.0);
}
#endstage
