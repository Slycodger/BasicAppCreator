#version 460 core
layout(location=0) in vec3 pos;

out vec3 cubeCoords;

uniform mat4 projection;
uniform mat4 view;

void main() {
  mat4 rotView = mat4(mat3(view));
		gl_Position = projection * rotView * vec4(pos, 1);
		gl_Position = gl_Position.xyww;
		cubeCoords = pos;
}
