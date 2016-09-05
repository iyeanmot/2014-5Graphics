#include "vbotorus.h"

#include <GL/glew.h>
#include <GL/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <string>
#include "Viewer.h"
#include "Model.h"

#include <cstdio>
#include <cmath>

//1 바깥족 반지름 ,0.5 안쪽 반지름,50,50
VBOTorus::VBOTorus(float outerRadius, float innerRadius, int nsides, int nrings) :
        rings(nrings), sides(nsides)
{
    faces = sides * rings;
    int nVerts  = sides * (rings+1);   // One extra ring to duplicate first ring

    // Verts
	GLfloat * v = new GLfloat[3 * nVerts];
    // Normals
	GLfloat * n = new GLfloat[3 * nVerts];
	// Index
    unsigned int * el = new unsigned int[6 * faces]; 

    // Generate the vertex data
    generateVerts(v, n, el, outerRadius, innerRadius);


	setup(v,n,el);

	
    shaderProgram = new ShaderProgram();

	//load shaders
	shaderProgram->initFromFiles("gouraud.vert", "gouraud.frag");

	//create vao
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	shaderProgram->addAttribute("VertexPosition"); //vbo의 속성 =  정점의 속성
	shaderProgram->addAttribute("VertexNormal");

	shaderProgram->addUniform("Light.Position");
	shaderProgram->addUniform("Light.La");
	shaderProgram->addUniform("Light.Ld");
	shaderProgram->addUniform("Light.Ls");

	shaderProgram->addUniform("Material.Ka");
	shaderProgram->addUniform("Material.Kd");
	shaderProgram->addUniform("Material.Ks");
	shaderProgram->addUniform("Material.Shiness");

	shaderProgram->addUniform("ModelViewMatrix"); //View * model
	shaderProgram->addUniform("NormalMatrix"); //반드시 있어야함 
	shaderProgram->addUniform("MVP");


		//create vbo for vertices
	//position
	glGenBuffers(1, &vbo_torus_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_torus_vertices);
	glBufferData(GL_ARRAY_BUFFER, (nVerts * 3) * sizeof(GLfloat), v, GL_STATIC_DRAW);
	glVertexAttribPointer(
		shaderProgram->attribute("VertexPosition"), // attribute
		3,                 // number of elements per vertex, here (x,y,z,1)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		0                  // offset of first element
		);
	glEnableVertexAttribArray(shaderProgram->attribute("VertexPosition"));

	//normal
	glGenBuffers(1, &vbo_torus_normals);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_torus_normals);
	glBufferData(GL_ARRAY_BUFFER, (nVerts * 3) * sizeof(GLfloat), n, GL_STATIC_DRAW);
	glVertexAttribPointer(
		shaderProgram->attribute("VertexNormal"), // attribute
		3,                 // number of elements per vertex, here (R,G,B)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		0                  // offset of first element
		);
	glEnableVertexAttribArray(shaderProgram->attribute("VertexNormal"));

	//index
	glGenBuffers(1, &ibo_torus_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_torus_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * faces * sizeof(unsigned int), el, GL_STATIC_DRAW);

	glBindVertexArray(0);

		
    delete [] v;
    delete [] n;
    delete [] el;
}


VBOTorus::~VBOTorus()
{


}

void VBOTorus::setup(GLfloat * v, GLfloat *n, unsigned int * el)
{


	
}


void VBOTorus::draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection) const 
{
	glm::mat4 mview = view * model;
	glm::mat4 mvp = projection * view * model;
	glm::vec4 lightPos(10, 10, 0, 1);
	glm::vec3 Ka(0.1, 0.1, 0.1);
	glm::vec3 Kd(1, 0, 1);
	glm::vec3 Ks(1, 1, 0);

	GLfloat shiness = 10;

	glm::vec3 La(0.1, 0.1, 0.1);
	glm::vec3 Ld(0.5, 0.5, 0.5);
	glm::vec3 Ls(0.2, 0.2, 0.2);

	glm::mat4 imvp = glm::inverse(mview);
	glm::mat3 nmat = glm::mat3(glm::transpose(imvp));

	

	shaderProgram->use();

	glUniform4fv(shaderProgram->uniform("Light.Position"), 1, glm::value_ptr(lightPos));
	glUniform3fv(shaderProgram->uniform("Light.La"), 1, glm::value_ptr(La));
	glUniform3fv(shaderProgram->uniform("Light.Ld"), 1, glm::value_ptr(Ld));
	glUniform3fv(shaderProgram->uniform("Light.Ls"), 1, glm::value_ptr(Ls));

	glUniform3fv(shaderProgram->uniform("Material.Ka"), 1, glm::value_ptr(Ka));
	glUniform3fv(shaderProgram->uniform("Material.Kd"), 1, glm::value_ptr(Kd));
	glUniform3fv(shaderProgram->uniform("Material.Ks"), 1, glm::value_ptr(Ks));
	glUniform1fv(shaderProgram->uniform("Material.Shiness"), 1, &shiness);

	glUniformMatrix4fv(shaderProgram->uniform("ModelViewMatrix"), 1, GL_FALSE, glm::value_ptr(mview));
	glUniformMatrix3fv(shaderProgram->uniform("NormalMatrix"), 1, GL_FALSE, glm::value_ptr(nmat));
	glUniformMatrix4fv(shaderProgram->uniform("MVP"), 1, GL_FALSE, glm::value_ptr(mvp));

	
	glBindVertexArray(vaoHandle);
	int size;	
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);	
	glDrawElements(GL_TRIANGLES, 6 * faces, GL_UNSIGNED_INT, 0);

	shaderProgram->disable();

}

void VBOTorus::generateVerts(GLfloat * verts, GLfloat * norms, unsigned int * el,
	float outerRadius, float innerRadius)
{
	float TWOPI = 2 * glm::pi<float>();

	float ringFactor  = (float)(TWOPI / rings);
	float sideFactor = (float)(TWOPI / sides);
	int idx = 0, tidx = 0;
	for( int ring = 0; ring <= rings; ring++ ) {
		float u = ring * ringFactor;
		float cu = cos(u);
		float su = sin(u);
		for( int side = 0; side < sides; side++ ) {
			float v = side * sideFactor;
			float cv = cos(v);
			float sv = sin(v);
			float r = (outerRadius + innerRadius * cv);
			verts[idx] = r * cu;
			verts[idx + 1] = r * su;
			verts[idx + 2] = innerRadius * sv;

			norms[idx] = cv * cu * r;
			norms[idx + 1] = cv * su * r;
			norms[idx + 2] = sv * r;

			// Normalize
			float len = sqrt( norms[idx] * norms[idx] +
				norms[idx+1] * norms[idx+1] +
				norms[idx+2] * norms[idx+2] );
			norms[idx] /= len;
			norms[idx+1] /= len;
			norms[idx+2] /= len;
			idx += 3;
		}
	}

	idx = 0;
	for( int ring = 0; ring < rings; ring++ ) {
		int ringStart = ring * sides;
		int nextRingStart = (ring + 1) * sides;
        for( int side = 0; side < sides; side++ ) {
            int nextSide = (side+1) % sides;
            // The quad
            el[idx] = (ringStart + side);
            el[idx+1] = (nextRingStart + side);
            el[idx+2] = (nextRingStart + nextSide);
            el[idx+3] = ringStart + side;
            el[idx+4] = nextRingStart + nextSide;
            el[idx+5] = (ringStart + nextSide);
            idx += 6;
        }
    }


}


