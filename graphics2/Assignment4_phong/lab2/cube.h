//#define  FREEGLUT_LIB_PRAGMAS  0

#pragma warning(push)
#pragma warning(disable:4311)		// convert void* to long
#pragma warning(disable:4312)		// convert long to void*


#include <windows.h>
#include <iostream>


#include "GL/glew.h"
#include <GL/gl.h>
#include <string>
#include <vector>


#include <FL/Fl_Gl_Window.h>
#include <Fl/Fl.h>

#include "glm/glm.hpp"
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <glm/gtc/constants.hpp>

#include "Loader.h"

class ColorCube
{

private:

	GLuint vaoHandle;
	ShaderProgram *shaderProgram;
	GLuint vbo_cube_vertices, vbo_cube_colors,vbo_cube_normals;
	GLuint ibo_cube_elements;



public:
	std::vector<glm::vec4> cube_vertices;
	std::vector<glm::vec3> cube_colors;
	std::vector<glm::vec3> cube_normals;

	void draw();
	void draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
	void setup();
	glm::vec3 computeNormal(glm::vec4 p[], int a, int b, int c, int d);
	void quad();

};

