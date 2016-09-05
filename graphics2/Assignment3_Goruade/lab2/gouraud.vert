#version 400

//attributes
in vec3 VertexPosition;
in vec3 VertexNormal;
out vec3 LightIntensity;

//uniforms
uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix; 
uniform mat4 MVP;

//uniform변수
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
    //정점
    vec4 P = ModelViewMatrix * vec4(VertexPosition,1);

	//광원 벡터
	vec3 L = vec3(Light.Position - P);
	L = normalize(L);  //L
   
	//노말벡터
	vec3 N = normalize(NormalMatrix * VertexNormal);

	//시선벡터
	vec3 V = vec3(-P);
	V = normalize(V);

	//반사벡터
	vec3 R = reflect(-L, N);
	R = normalize(R);

	vec3 Ambient = Light.La * Material.Ka;
	if(dot(L,N)>0)
		Diffuse = Light.Ld * Material.Kd * max(dot(L,N),0.0) ;
	else
		Diffuse = vec3(0.0);
	if(dot(L,N)>0)
		Specular = Light.Ls * Material.Ks * pow(max(dot(R, V),0.0), Material.Shiness); //dot에 n제곱해야함 n이뭐지근데

	LightIntensity = Ambient + Diffuse + Specular;

	gl_Position = MVP * vec4(VertexPosition, 1.0); //vertexnormal를 적용할대는 곱해줘야함
}

