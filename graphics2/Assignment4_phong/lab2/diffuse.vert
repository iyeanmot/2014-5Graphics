
#version 440

layout (location = 0) in vec4 VertexPosition; //Ư�� attribute ��ȣ�� ������ //VAO�� 0��° attrbute�� �޾Ƽ� VertexPosition�� �־��
layout (location = 1) in vec3 VertexNormal; //VAO�� 1��° attrbute�� �޾Ƽ� VertexNormal �� �־��

out vec3 LightIntensity;  //������ ����

uniform vec4 LightLocation;
uniform vec3 Kd;
uniform vec3 Ld;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix; 
uniform mat4 MVP;

void main()
{
   vec3 N = normalize( NormalMatrix * VertexNormal);
   vec4 P = ModelViewMatrix * VertexPosition;   //�̰��� �ٷ� projection�ϱ� ���� ������Ʈ ǥ���� 3���� P

   vec3 L= normalize(vec3(LightLocation - P));  //L
   LightIntensity = Ld * Kd * max(dot(L,N),0.0);

   gl_Position = MVP * VertexPosition; //vertexnormal�� �����Ҵ�� ���������
}
