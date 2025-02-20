#version 460 core

layout(location=0) in vec3 pos;
layout(location=3) in vec2 uv;


uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

out vec2 uvCoord;

void main() {
				gl_Position = projection * view * transform * vec4(pos, 1);
				uvCoord = uv;
}