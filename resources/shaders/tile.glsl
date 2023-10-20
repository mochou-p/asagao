// asagao/resources/shaders/tile.glsl


#stage vertex
#version 460 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texcoord;

uniform mat4 u_mvp;
uniform vec2 u_uv_frac;
uniform vec2 u_tile_uv;

out vec2 v_texcoord;

void main()
{
    gl_Position = u_mvp * position;
    v_texcoord  = (texcoord + u_tile_uv) * u_uv_frac;
}
#endstage


#stage fragment
#version 460 core

in vec2 v_texcoord;

uniform sampler2D u_texture;

void main()
{
    gl_FragColor = texture(u_texture, v_texcoord);
}
#endstage
