#version 440

in vec3 VertexPosition;
in vec3 VertexNormal;

out vec3 Position;
out vec3 Normal;


uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix; 
uniform mat4 MVP;

void main()
{
	//정점
    Position = vec3(ModelViewMatrix * vec4(VertexPosition,1));

	//노말벡터
	Normal = normalize(NormalMatrix * VertexNormal);

	gl_Position = MVP * vec4(VertexPosition, 1.0); //vertexnormal를 적용할대는 곱해줘야함
}