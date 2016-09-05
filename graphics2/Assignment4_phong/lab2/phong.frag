#version 440

in vec3 Position;
in vec3 Normal;

uniform vec4 LightPosition;
uniform vec3 LightIntensity; //Ia = Id = Is = LightIntensity

uniform vec3 Kd;
uniform vec3 Ka;
uniform vec3 Ks;
uniform float Shiness;

out vec4 FragColor;


void main()
{
	vec3 Diffuse = vec3(0.0);
    vec3 Specular = vec3(0.0);


	//광원 벡터
	vec3 L = vec3(vec3(LightPosition) - Position);
	L = normalize(L);  //L 

	//시선벡터
	vec3 V = vec3(-Position);
	V = normalize(V);

	//반사벡터
	//vec3 R = reflect(-L, Normal);
	//R = normalize(R);

	vec3 H = V+L;
	H = normalize(H);

	vec3 Ambient = LightIntensity * Ka;

	if(dot(L,Normal)>0)
		Diffuse = LightIntensity * Kd * max(dot(L,Normal),0.0) ;
	else
		Diffuse = vec3(0.0);

	if(dot(L,Normal)>0)
		Specular = LightIntensity * Ks * pow(max(dot(H, Normal),0.0), Shiness); //dot에 n제곱해야함 n이뭐지근데

	FragColor = vec4((Ambient + Diffuse + Specular), 1.0);


}