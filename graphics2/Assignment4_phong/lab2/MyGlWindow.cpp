

#include "MyGlWindow.h"

ShaderProgram *shaderProgram;
static double DEFAULT_VIEW_POINT[3] = { 5, 5, 5 };
static double DEFAULT_VIEW_CENTER[3] = { 0, 0, 0 };
static double DEFAULT_UP_VECTOR[3] = { 0, 1, 0 };



MyGlWindow::MyGlWindow(int x, int y, int w, int h)
: Fl_Gl_Window(x, y, w, h)
//==========================================================================
{

	mode(FL_RGB | FL_ALPHA | FL_DOUBLE | FL_STENCIL);
    first = 0;
    m_cube = 0;

    MathVec3D<double> viewPoint(DEFAULT_VIEW_POINT);
    MathVec3D<double> viewCenter(DEFAULT_VIEW_CENTER);
    MathVec3D<double> upVector(DEFAULT_UP_VECTOR);
    double aspect = (w / h);
    m_viewer = new Viewer(viewPoint, viewCenter, upVector, 45, aspect);

}

void MyGlWindow::initialize()
{
   //m_cube = new ColorCube();
   m_floor = new CheckeredFloor(8,8);
   m_torus = new VBOTorus(1, 0.5, 50, 50);
   glm::mat4 m = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,0));
   m_teapot = new VBOTeapot(64, m);

}



void MyGlWindow::setupBuffer()
{
}

void MyGlWindow::draw(void)
{
	
	glClearColor(0.2f, 0.2f, .2f, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glEnable(GL_DEPTH_TEST);


	/////클래스
	if (!first) {
		glewExperimental = TRUE;
		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			//Problem: glewInit failed, something is seriously wrong.
			std::cout << "glewInit failed, aborting." << std::endl;
		}

		first = 1;

		initialize();
		//m_cube->setup();
		m_floor->setup();
	}

	glViewport(0, 0, w(), h());

	//view M
	glm::vec3 eye(m_viewer->getViewPoint().x(), m_viewer->getViewPoint().y(), m_viewer->getViewPoint().z()); 	
	glm::vec3 look(m_viewer->getViewCenter().x(), m_viewer->getViewCenter().y(), m_viewer->getViewCenter().z());
	glm::vec3 up(m_viewer->getUpVector().x(), m_viewer->getUpVector().y(), m_viewer->getUpVector().z());	
	glm::mat4 view = glm::lookAt(eye, look, up);   //현재의 m_viewer로부터 카메라 view 행렬을 구함
	//projection V
	glm::mat4 projection = glm::perspective(45.0f,((float) w() / h()), 0.1f, 500.0f);  //projection행렬을 구함


	m_model.glPushMatrix();
		glm::mat4 model = m_model.getMatrix();  //현재의 모델 행렬을 구함
		if (m_floor) m_floor->draw(model,view,projection);
		m_model.glTranslate(0,0.5f,0);
		m_model.glRotate(90,1,0,0);
		//model M
		//if (m_cube) m_cube->draw();
		
		//if (m_cube) m_cube->draw(m_model.getMatrix(),view,projection);
		//m_model.glTranslate(0,-5,0);
		if(m_torus) m_torus->draw(m_model.getMatrix(),view,projection);
		m_model.glRotate(180,1,0,0);
		m_model.glTranslate(5.0f, 0, 0);
		if(m_teapot) m_teapot->draw(m_model.getMatrix(),view,projection);
	
	m_model.glPopMatrix();

}

int m_pressedMouseButton;
int m_lastMouseX;
int m_lastMouseY;

int MyGlWindow::handle(int e)
{
	switch(e) {
	case FL_SHOW:// you must handle this, or not be seen!
		show();
		return 1;
	case FL_PUSH:
		{
			m_pressedMouseButton = Fl::event_button();
			m_lastMouseX = Fl::event_x();
			m_lastMouseY = Fl::event_y();
		}
		damage(1);
		return 1;
	case FL_RELEASE:
		m_pressedMouseButton = -1;
		damage(1);
		return 1;
	case FL_DRAG: // if the user drags the mouse
		{
			double fractionChangeX = static_cast<double>(Fl::event_x() - m_lastMouseX) / static_cast<double>(this->w());
			double fractionChangeY = static_cast<double>(m_lastMouseY - Fl::event_y()) / static_cast<double>(this->h());
			if( m_pressedMouseButton == 1 ) {
				m_viewer->rotate( fractionChangeX, fractionChangeY );
			} else if( m_pressedMouseButton == 2 ) {
				m_viewer->zoom( fractionChangeY );
			} else if( m_pressedMouseButton == 3 ) {
				m_viewer->translate( -fractionChangeX, -fractionChangeY,                   
					(Fl::event_key(FL_Shift_L) == 0) || (Fl::event_key(FL_Shift_R) == 0));
			} else {
				std::cout << "Warning: dragging with unknown mouse button!  Nothing will be done" << std::endl;
			}

			m_lastMouseX = Fl::event_x();
			m_lastMouseY = Fl::event_y();
			redraw();
		}

		return 1;

	case FL_KEYBOARD:
		return 0;

	default:
		return 0;
	}
}
