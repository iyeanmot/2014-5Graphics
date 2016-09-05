//#define  FREEGLUT_LIB_PRAGMAS  0

#pragma warning(push)
#pragma warning(disable:4311)		// convert void* to long
#pragma warning(disable:4312)		// convert long to void*


#include <windows.h>
#include <iostream>


#include "GL/glew.h"
#include <GL/gl.h>
#include <string>


#include <FL/Fl_Gl_Window.h>
#include <Fl/Fl.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"


#include "Loader.h"
#include "cube.h"
#include "Viewer.h"
#include "Model.h"
#include "CheckeredFloor.h"
#include "vbotorus.h"

#pragma warning(pop)


class MyGlWindow : public Fl_Gl_Window {
public:
	MyGlWindow(int x, int y, int w, int h);
	void initialize();
private:
	void draw();		
	void setupBuffer();
	int handle(int);	
	int first;

	ColorCube * m_cube;
	Viewer *m_viewer;
	Model m_model;
	CheckeredFloor *m_floor;
	VBOTorus *m_torus;

};
