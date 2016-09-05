

#include "MyGlWindow.h"

ShaderProgram *shaderProgram;


MyGlWindow::MyGlWindow(int x, int y, int w, int h)
: Fl_Gl_Window(x, y, w, h)
//==========================================================================
{

	mode(FL_RGB | FL_ALPHA | FL_DOUBLE | FL_STENCIL);
	first = 0;
}



GLuint vaoHandle;
GLuint vbo_cube_vertices, vbo_cube_colors;
GLuint ibo_cube_elements;

// GLuint ibo_cube_elements;
// GLint attribute_coord3d, attribute_v_colo


void MyGlWindow::setupBuffer()
{


GLfloat cube_vertices[] = {
// front
-1.0, -1.0, 1.0,
1.0, -1.0, 1.0,
1.0, 1.0, 1.0,
-1.0, 1.0, 1.0,
// back
-1.0, -1.0, -1.0,
1.0, -1.0, -1.0,
1.0, 1.0, -1.0,
-1.0, 1.0, -1.0,
};

GLfloat cube_colors[] = {
// front colors
1.0, 0.0, 0.0,
0.0, 1.0, 0.0,
0.0, 0.0, 1.0,
1.0, 1.0, 1.0,
// back colors
1.0, 0.0, 0.0,
0.0, 1.0, 0.0,
0.0, 0.0, 1.0,
1.0, 1.0, 1.0,
};
GLushort cube_elements[] = {		
0, 1, 2,		2, 3, 0,		1, 5, 6,	
6, 2, 1,		7, 6, 5,		5, 4, 7,	
4, 0, 3,		3, 7, 4,		4, 5, 1,	
1, 0, 4,		3, 2, 6,		6, 7, 3,	
};


	shaderProgram = new ShaderProgram();
	
	//load shaders
	shaderProgram->initFromFiles("simple.vert", "simple.frag");

	
	

	//create vao
	glGenVertexArrays(1, &vaoHandle);
	glBindVertexArray(vaoHandle);

	//add attributes and uniform vars
	shaderProgram->addAttribute("coord3d");
	shaderProgram->addAttribute("v_color");



	//create vbo for vertices
	glGenBuffers(1, &vbo_cube_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* 3 * 8, &cube_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(
		shaderProgram->attribute("coord3d"), // attribute
		3,                 // number of elements per vertex, here (x,y,z,1)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		0                  // offset of first element
		);
    glEnableVertexAttribArray(shaderProgram->attribute("coord3d"));


	//create vbo for colors
	glGenBuffers(1, &vbo_cube_colors);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_colors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* 3 * 8, &cube_colors, GL_STATIC_DRAW);
	glVertexAttribPointer(
		shaderProgram->attribute("v_color"), // attribute
		3,                 // number of elements per vertex, here (R,G,B)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		0                  // offset of first element
		);
	glEnableVertexAttribArray(shaderProgram->attribute("v_color"));

	glGenBuffers(1, &ibo_cube_elements);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);


	//unbound the vao
	glBindVertexArray(0);

}

void MyGlWindow::draw(void)
{
	
	glClearColor(0.2f, 0.2f, .2f, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glEnable(GL_DEPTH_TEST);

	
	if (!first) {
		glewInit();
		first = 1;


		setupBuffer();
		
	}
	

	glViewport(0, 0, w(), h());

	
	shaderProgram->use();
	
		glBindVertexArray(vaoHandle);
		int size;	
		glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE,&size); 
		glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

	shaderProgram->disable();


}

int MyGlWindow::handle(int e)
//==========================================================================
{
	switch (e) {
	case FL_SHOW:		// you must handle this, or not be seen!
		show();
		return 1;
	case FL_PUSH:
	{

	}
		damage(1);
		return 1;
	case FL_RELEASE:
		damage(1);
		return 1;
	}

	return 0;
}