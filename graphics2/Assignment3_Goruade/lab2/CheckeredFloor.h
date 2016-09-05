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
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"
#include "glm/gtc/type_ptr.hpp"


#include "Loader.h"

class CheckeredFloor
{
private:
	GLuint vaoHandle;
	ShaderProgram *shaderProgram;
	GLuint vbo_floor_vertices, vbo_floor_colors;

public:
	int size;
	int nsqure;
	CheckeredFloor(int _size, int _nsqure);
	std::vector<glm::vec4> floor_vertices;
	std::vector<glm::vec3> floor_colors;

	void draw();
	void draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
	void setup();

};