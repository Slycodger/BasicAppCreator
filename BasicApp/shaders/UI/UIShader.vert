#version 460 core

layout(location=0) in vec3 pos;
layout(location=3) in vec2 uv;

out vec2 uvCoord;

void main() {
				gl_Position = vec4(pos + vec3(0, 0, -0.1f), 1);
				uvCoord = uv;
}