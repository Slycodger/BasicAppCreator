#version 460 core
layout(location=0) in vec3 pos;
layout(location=1) in vec3 normal;
layout(location=2) in vec3 tangent;
layout(location=3) in vec2 uv;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;


out VS_OUT {
  vec3 fragNormal;
  vec3 fragPos;
  vec2 uvCoord;
  mat3 TBN;
};



void main() {
		gl_Position = projection * view * transform * vec4(pos, 1);

		fragPos = vec3(transform * vec4(pos, 1.0));
  fragNormal = mat3(transpose(inverse(transform))) * normal;

		uvCoord = uv;


  vec3 T = normalize(vec3(transform * vec4(tangent, 0.0)));
  vec3 N = normalize(vec3(transform * vec4(normal, 0.0)));
  T = normalize(T - dot(T, N) * N);
  vec3 B = cross(N, T);

  TBN = mat3 (T, B, N);
}