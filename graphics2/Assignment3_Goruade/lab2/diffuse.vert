
#version 440

layout (location = 0) in vec4 VertexPosition; //특정 attribute 번호를 세팅함 //VAO의 0번째 attrbute를 받아서 VertexPosition에 넣어라
layout (location = 1) in vec3 VertexNormal; //VAO의 1번째 attrbute를 받아서 VertexNormal 에 넣어라

out vec3 LightIntensity;  //정점의 색상

uniform vec4 LightLocation;
uniform vec3 Kd;
uniform vec3 Ld;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix; 
uniform mat4 MVP;

void main()
{
   vec3 N = normalize( NormalMatrix * VertexNormal);
   vec4 P = ModelViewMatrix * VertexPosition;   //이것이 바로 projection하기 전의 오브젝트 표면의 3차원 P

   vec3 L= normalize(vec3(LightLocation - P));  //L
   LightIntensity = Ld * Kd * max(dot(L,N),0.0);

   gl_Position = MVP * VertexPosition; //vertexnormal를 적용할대는 곱해줘야함
}
