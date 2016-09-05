#version 400

//attributes
in vec3 VertexPosition;
in vec3 VertexNormal;
out vec3 LightIntensity;

//uniforms
uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix; 
uniform mat4 MVP;

//uniform����
struct LightInfo {
  vec4 Position; // Light position in eye coords.
  vec3 La;       // Ambient light intensity
  vec3 Ld;       // Diffuse light intensity
  vec3 Ls;       // Specular light intensity
};

uniform LightInfo Light;

struct MaterialInfo {
  vec3 Ka;            // Ambient reflectivity
  vec3 Kd;            // Diffuse reflectivity
  vec3 Ks;            // Specular reflectivity
  float Shiness;    // Specular shininess factor (phong exponent)
};
uniform MaterialInfo Material;

void main()
{
	vec3 Diffuse = vec3(0.0);
    vec3 Specular = vec3(0.0);
    //����
    vec4 P = ModelViewMatrix * vec4(VertexPosition,1);

	//���� ����
	vec3 L = vec3(Light.Position - P);
	L = normalize(L);  //L
   
	//�븻����
	vec3 N = normalize(NormalMatrix * VertexNormal);

	//�ü�����
	vec3 V = vec3(-P);
	V = normalize(V);

	//�ݻ纤��
	vec3 R = reflect(-L, N);
	R = normalize(R);

	vec3 Ambient = Light.La * Material.Ka;
	if(dot(L,N)>0)
		Diffuse = Light.Ld * Material.Kd * max(dot(L,N),0.0) ;
	else
		Diffuse = vec3(0.0);
	if(dot(L,N)>0)
		Specular = Light.Ls * Material.Ks * pow(max(dot(R, V),0.0), Material.Shiness); //dot�� n�����ؾ��� n�̹����ٵ�

	LightIntensity = Ambient + Diffuse + Specular;

	gl_Position = MVP * vec4(VertexPosition, 1.0); //vertexnormal�� �����Ҵ�� ���������
}

