#ifndef VBOTORUS_H
#define VBOTORUS_H

#include <GL/glew.h>
#include <glm/mat4x4.hpp>

#include "Loader.h"
class VBOTorus 
{
private:
    int faces, rings, sides;
	
    void generateVerts(float * , float * , unsigned int *,
                       float , float);
	void setup(GLfloat * v, GLfloat *n, unsigned int * el);
	ShaderProgram *shaderProgram;

	GLuint vaoHandle;
	GLuint vbo_torus_vertices, vbo_torus_normals;
	GLuint ibo_torus_elements;

public:

	VBOTorus(float, float, int, int);
	virtual ~VBOTorus();
	void draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection) const;
};

#endif // VBOTORUS_H
