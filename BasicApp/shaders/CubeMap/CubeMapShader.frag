#version 460 core

out vec4 fragColor;
in vec3 cubeCoords;

uniform samplerCube texTarget;

void main() {
				fragColor = texture(texTarget, cubeCoords);
}