
#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 3) in vec2 uv;

out vec2 uvCoord;

void main() {
  uvCoord = uv;
	 gl_Position = vec4(pos, 1.0);
}

