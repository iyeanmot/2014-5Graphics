//#define GLM_SWIZZLE

#include "cube.h"
#include "glm\gtc\type_ptr.hpp"
#include <string>
#include "Viewer.h"
#include "Model.h"

void ColorCube ::setup()
{
	//local coord->world coord->cameara coord  = model view mat
	//(model view Mat) * (projection Mat) = mvp 

	////local coord
	//GLfloat cube_vertices[] = {
	//	// front
	//	-1.0, -1.0, 1.0,
	//	1.0, -1.0, 1.0,
	//	1.0, 1.0, 1.0,
	//	-1.0, 1.0, 1.0,
	//	// back
	//	-1.0, -1.0, -1.0,
	//	1.0, -1.0, -1.0,
	//	1.0, 1.0, -1.0,
	//	-1.0, 1.0, -1.0,
	//};




	//GLfloat cube_colors[] = {
	//	// front colors
	//	1.0, 0.0, 0.0,
	//	0.0, 1.0, 0.0,
	//	0.0, 0.0, 1.0,
	//	1.0, 0.0, 1.0,
	//	// back colors
	//	1.0, 0.0, 0.0,
	//	0.0, 1.0, 1.0,
	//	0.0, 0.0, 1.0,
	//	1.0, 0.0, 1.0,
	//};

	glm::vec4 Position[] = {
		glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f),
		glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f),
		glm::vec4(0.5f, 0.5f, 0.5f, 1.0f),
		glm::vec4(0.5f, -0.5f, 0.5f, 1.0f), 
		glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f),
		glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f),
		glm::vec4(0.5f, 0.5f, -0.5f, 1.0f), 
		glm::vec4(0.5f, -0.5f, -0.5f, 1.0f)
	};
	//cube_vertices.push_back(glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f)); //0
	//cube_vertices.push_back(glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f)); //1
	//cube_vertices.push_back(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)); //2
	//cube_vertices.push_back(glm::vec4(0.5f, -0.5f, 0.5f, 1.0f)); //3
	//cube_vertices.push_back(glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f));  //4
	//cube_vertices.push_back(glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f)); //5
	//cube_vertices.push_back(glm::vec4(0.5f, 0.5f, -0.5f, 1.0f)); //6
	//cube_vertices.push_back(glm::vec4(0.5f, -0.5f, -0.5f, 1.0f)); //7



	computeNormal(Position, 0 ,1 , 2, 3);
	computeNormal(Position, 2 ,3 , 7, 6);
	computeNormal(Position, 3 ,0 , 4, 7);
	computeNormal(Position, 6 ,5 , 1, 2);
	computeNormal(Position, 4 ,5 , 6, 7);
	computeNormal(Position, 5 ,4 , 0, 1);

	//0123
	//2376
	//	3047
	//	6512
	//	4567
	//	5401

	/*for(int i=0; i<8 ;i++)
		std::cout <<"좌표" <<glm::to_string(cube_vertices[i]) << std::endl;*/

	//cube_colors.push_back(glm::vec3(1, 0, 0));
	//cube_colors.push_back(glm::vec3(0, 1, 0));
	//cube_colors.push_back(glm::vec3(0, 0, 1));
	//cube_colors.push_back(glm::vec3(1, 1, 1));
	//cube_colors.push_back(glm::vec3(1, 0, 0));
	//cube_colors.push_back(glm::vec3(0, 1, 0));
	//cube_colors.push_back(glm::vec3(0, 0, 1));
	//cube_colors.push_back(glm::vec3(1, 1, 1));

	//GLushort cube_elements[] = {		
	//	0, 1, 2,		2, 3, 0,		1, 5, 6,	
	//	6, 2, 1,		7, 6, 5,		5, 4, 7,	
	//	4, 0, 3,		3, 7, 4,		4, 5, 1,	
	//	1, 0, 4,		3, 2, 6,		6, 7, 3,	
	//};


	shaderProgram = new ShaderProgram();

	//load shaders
	shaderProgram->initFromFiles("diffuse.vert", "diffuse.frag");

		//create vao
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	//add attributes and uniform vars
	//shaderProgram->addAttribute("coord3d");
	//shaderProgram->addAttribute("v_color");
	//shaderProgram->addAttribute("v_normal");

	shaderProgram->addAttribute("VertexPosition"); //vbo의 속성 =  정점의 속성
	shaderProgram->addAttribute("VertexNormal");

	//global한 mat의 형태는 uniform, 정점 정보 X
	//일종의 선언 -> 쉐이더 안에있는 변수를 사용
	shaderProgram->addUniform("LightLocation");  //빛의 위치
	shaderProgram->addUniform("Kd");  //오브젝트 색상
	shaderProgram->addUniform("Ld"); //빛의 색상
	shaderProgram->addUniform("ModelViewMatrix"); //View * model
	shaderProgram->addUniform("NormalMatrix"); //반드시 있어야함 
	shaderProgram->addUniform("MVP");
	//shaderProgram->addUniform("mvp");




	//create vbo for vertices
	glGenBuffers(1, &vbo_cube_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*cube_vertices.size() * 4, cube_vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(
		shaderProgram->attribute("VertexPosition"), // attribute
		4,                 // number of elements per vertex, here (x,y,z,1)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		0                  // offset of first element
		);
	glEnableVertexAttribArray(shaderProgram->attribute("VertexPosition"));


	////create vbo for colors
	//glGenBuffers(1, &vbo_cube_colors);
	//glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_colors);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float)*cube_colors.size() * 3, cube_colors.data(), GL_STATIC_DRAW);
	//glVertexAttribPointer(
	//	shaderProgram->attribute("v_color"), // attribute
	//	3,                 // number of elements per vertex, here (R,G,B)
	//	GL_FLOAT,          // the type of each element
	//	GL_FALSE,          // take our values as-is
	//	0,                 // no extra data between each position
	//	0                  // offset of first element
	//	);
	//glEnableVertexAttribArray(shaderProgram->attribute("v_color"));

	//로컬 좌표계에서의 normal
	//create vbo for colors
	glGenBuffers(1, &vbo_cube_normals);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_normals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*cube_normals.size() * 3, cube_normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(
		shaderProgram->attribute("VertexNormal"), // attribute
		3,                 // number of elements per vertex, here (R,G,B)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		0                  // offset of first element
		);
	glEnableVertexAttribArray(shaderProgram->attribute("VertexNormal"));

	//glGenBuffers(1, &ibo_cube_elements);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);


	//unbound the vao
	glBindVertexArray(0);
}

void ColorCube ::draw()
{
	//원래 드로우 찾아서 넣기
	shaderProgram->use();
	//glBindVertexArray(vaoHandle);
	//int size;	
	//glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);	
	////glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, sizeof(float)*cube_vertices.size() * 4);


	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size()*3);

	shaderProgram->disable();


}
void ColorCube ::draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
	//tnstjwnddy
	glm::mat4 mview = view * model;
	glm::mat4 mvp = projection * view * model;
	glm::vec4 lightPos(10, 10, 10, 0);
	glm::vec3 Kd(1, 1, 0); //색상
	glm::vec3 Ld(1, 1, 1); //색상
	glm::mat4 imvp = glm::inverse(mview);
	glm::mat3 nmat = glm::mat3(glm::transpose(imvp));

	shaderProgram->use();

	////Shader로 값을 넘기는 부분
	//glUniformMatrix4fv(shaderProgram->uniform("MVP"), 1, GL_FALSE, glm::value_ptr(mvp));
	//glBindVertexArray(vaoHandle);
	//int size;	
	//glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);	
	//glDrawArrays(GL_TRIANGLES, 0, sizeof(float)*cube_vertices.size() * 4);
	////glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	////draw 

	////Shader로 값을 넘기는 부분
	glUniform4fv(shaderProgram->uniform("LightLocation"), 1, glm::value_ptr(lightPos));  
	glUniform3fv(shaderProgram->uniform("Kd"), 1,  glm::value_ptr(Kd));
	glUniform3fv(shaderProgram->uniform("Ld"), 1,  glm::value_ptr(Ld));

	glUniformMatrix4fv(shaderProgram->uniform("ModelViewMatrix"), 1, GL_FALSE, glm::value_ptr(mview));
	glUniformMatrix3fv(shaderProgram->uniform("NormalMatrix"), 1, GL_FALSE, glm::value_ptr(nmat));
	glUniformMatrix4fv(shaderProgram->uniform("MVP"), 1, GL_FALSE, glm::value_ptr(mvp));

	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size()*3);
	shaderProgram->disable();

}

glm::vec3 ColorCube ::computeNormal(glm::vec4 p[], int a, int b, int c, int d)
{
	glm::vec4 p1(p[a]);
	glm::vec4 p2(p[b]);
	glm::vec4 p3(p[c]);
	glm::vec4 p4(p[d]);

	cube_vertices.push_back(p1);
	cube_vertices.push_back(p2);
	cube_vertices.push_back(p4);

	//std::cout <<"룰루" <<glm::to_string(p1) << std::endl;

	glm::vec3 v1; 
	glm::vec3 v2;
	glm::vec3 n1;
	glm::vec3 n2;

	v1 = (glm::vec3)p2-(glm::vec3)p1;
	v2 = (glm::vec3)p3-(glm::vec3)p1;
	n1 = glm::cross(v1, v2);
	glm::normalize(n1);
	//std::cout <<"까꿍" <<glm::to_string(n1) << std::endl;
	this->cube_normals.push_back(n1);
	this->cube_normals.push_back(n1);
	this->cube_normals.push_back(n1);

	cube_vertices.push_back(p2);
	cube_vertices.push_back(p3);
	cube_vertices.push_back(p4);

	v1 = (glm::vec3)p3-(glm::vec3)p1;
	v2 = (glm::vec3)p4-(glm::vec3)p1;
	n1 = glm::cross(v1, v2);
	glm::normalize(n1);

	this->cube_normals.push_back(n1);
	this->cube_normals.push_back(n1);
	this->cube_normals.push_back(n1);
	//std::cout <<"까꿍2" <<glm::to_string(n1) << std::endl;
	return n1;

}

