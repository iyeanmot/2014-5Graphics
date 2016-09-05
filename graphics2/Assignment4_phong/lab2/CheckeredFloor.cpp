#include "CheckeredFloor.h"
#include <vector>

CheckeredFloor::CheckeredFloor(int _size, int _nsqure)
{
	this->size = _size;
	this->nsqure = _nsqure;
}

	float floorColor1[3] = { .7f, .7f, .7f }; // Light color
	float floorColor2[3] = { .3f, .3f, .3f }; // Dark color


void CheckeredFloor::setup()
{
		//local coord->world coord->cameara coord  = model view mat
	//(model view Mat) * (projection Mat) = mvp 

	float maxX = (float)this->size/2, maxY = (float)this->size/2;
	float minX =(float) -this->size/2, minY = (float)-this->size/2;


for (int i = minX; i < maxX; i++)
	{
		for (int j = minX; j < maxX; j++)
		{
			floor_vertices.push_back(glm::vec4(i*this->size, 0, j*this->size, 1));
			floor_vertices.push_back(glm::vec4((i + 1)*this->size, 0, j*this->size, 1));
			floor_vertices.push_back(glm::vec4(i*this->size, 0, (j+1)*this->size, 1));
			floor_vertices.push_back(glm::vec4((i+1)*this->size, 0, j*this->size, 1));
			floor_vertices.push_back(glm::vec4(i*this->size, 0, (j+1)*this->size, 1));
			floor_vertices.push_back(glm::vec4((i+1)*this->size, 0, (j+1)*this->size, 1));

		}
	}

	for (int i = 0; i < this->nsqure; i++)
	{
		for (int j = 0; j < this->nsqure; j++)
		{
			if ((i + j) % 2 == 1)
			{
				floor_colors.push_back(glm::vec3(floorColor1[0], floorColor1[1], floorColor1[2]));
				floor_colors.push_back(glm::vec3(floorColor1[0], floorColor1[1], floorColor1[2]));
				floor_colors.push_back(glm::vec3(floorColor1[0], floorColor1[1], floorColor1[2]));
				floor_colors.push_back(glm::vec3(floorColor1[0], floorColor1[1], floorColor1[2]));
				floor_colors.push_back(glm::vec3(floorColor1[0], floorColor1[1], floorColor1[2]));
				floor_colors.push_back(glm::vec3(floorColor1[0], floorColor1[1], floorColor1[2]));
			}
			else
			{
				floor_colors.push_back(glm::vec3(floorColor2[0], floorColor2[1], floorColor2[2]));
				floor_colors.push_back(glm::vec3(floorColor2[0], floorColor2[1], floorColor2[2]));
				floor_colors.push_back(glm::vec3(floorColor2[0], floorColor2[1], floorColor2[2]));
				floor_colors.push_back(glm::vec3(floorColor2[0], floorColor2[1], floorColor2[2]));
				floor_colors.push_back(glm::vec3(floorColor2[0], floorColor2[1], floorColor2[2]));
				floor_colors.push_back(glm::vec3(floorColor2[0], floorColor2[1], floorColor2[2]));
			}
		}
	}


	shaderProgram = new ShaderProgram();

	//load shaders
	shaderProgram->initFromFiles("simple.vert", "simple.frag");
	
	//create vao
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	//add attributes and uniform vars
	shaderProgram->addAttribute("coord3d");
	shaderProgram->addAttribute("v_color");
	shaderProgram->addUniform("mvp");




	//create vbo for vertices
	glGenBuffers(1, &vbo_floor_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_floor_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*floor_vertices.size() * 4, floor_vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(
		shaderProgram->attribute("coord3d"), // attribute
		4,                 // number of elements per vertex, here (x,y,z,1)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		0                  // offset of first element
		);
	glEnableVertexAttribArray(shaderProgram->attribute("coord3d"));


	//create vbo for colors
	glGenBuffers(1, &vbo_floor_colors);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_floor_colors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*floor_colors.size() * 3, floor_colors.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(
		shaderProgram->attribute("v_color"), // attribute
		3,                 // number of elements per vertex, here (R,G,B)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		0                  // offset of first element
		);
	glEnableVertexAttribArray(shaderProgram->attribute("v_color"));


	//unbound the vao
	glBindVertexArray(0);
}
void CheckeredFloor::draw()
{
	shaderProgram->use();
	glBindVertexArray(vaoHandle);
	int size;	
	//glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);	
	glDrawArrays(GL_TRIANGLES, 0, floor_vertices.size() * 3);
	shaderProgram->disable();

}
void CheckeredFloor::draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{

	glm::mat4 mview = view * model;	
	glm::mat4 mvp = projection * view * model;

	shaderProgram->use();

	glUniformMatrix4fv(shaderProgram->uniform("mvp"), 1, GL_FALSE, glm::value_ptr(mvp));

	//draw 
	glBindVertexArray(vaoHandle);
	glDrawArrays(GL_TRIANGLES, 0, floor_vertices.size() * 3);
	shaderProgram->disable();
}