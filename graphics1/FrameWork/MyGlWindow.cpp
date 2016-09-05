 
 
#include "MyGlWindow.h"
#include "MathVec3D.h"
#include <iostream>
#include "drawUtils.h"

using namespace std;
 
//**************************************************************************
//
// Implementation of MyGLWindow
//==========================================================================
 
 
static double DEFAULT_VIEW_POINT[3] = {10, 10, 10};
static double DEFAULT_VIEW_CENTER[3] = {0, 0, 0};
static double DEFAULT_UP_VECTOR[3] = {0, 1, 0};
 
MyGlWindow::MyGlWindow(int x, int y, int w, int h) :
  Fl_Gl_Window(x,y,w,h)
//==========================================================================
{
    
    mode( FL_RGB|FL_ALPHA|FL_DOUBLE | FL_STENCIL );
 	
	fieldOfView = 45;
 
	MathVec3D<double> viewPoint( DEFAULT_VIEW_POINT );
	MathVec3D<double> viewCenter( DEFAULT_VIEW_CENTER );
	MathVec3D<double> upVector( DEFAULT_UP_VECTOR );
	double aspect = ( w /  h);
	m_viewer = new Viewer( viewPoint, viewCenter, upVector, 45, aspect );
 
 
	//Å©·¹ÀÎ//
	Crane_Boom_rotation = 0;
	Crane_Box_horizontal = 0;
	Crane_Box_vertical = 0; 

	//Æ÷Å©·¹ÀÎ//
	Exc_X = -50;
	Exc_Z = -50;
	Exc_Y = 0;
	Exc_Rotation = 0;
	Exc_Spin = 0;
	Exc_Arm = -30;
	Exc_Elbow = 50;
	Exc_Bucket = -30;

	//Æ®·°//
	Dump_X = 50.5f;
	Dump_Z = 50.5f;
	Dump_Rotation = 0;
	Dump_Tip_amount = 0;


 
	camMode = 0;
}
 
 
  void MyGlWindow::setupLight()
  {
	  // set up the lighting
	  GLfloat lightPosition[] = {50, 200.0, 50, 1.0};
	 
	  GLfloat lightPosition2[] = {-100.0, 10.0, -150.0, 1.0};
	  GLfloat lightPosition3[] = {0, -200, 0, 1.0};
	  GLfloat violetLight[] = {0.5f, 0.1f, .5f, 1.0};
	  GLfloat yellowishLight[] = {1, 1, 1, 1.0};
	  GLfloat blueLight[] = {.1f,.1f,.3f,1.0};
 
 
	  glEnable(GL_COLOR_MATERIAL);
	  glEnable(GL_DEPTH_TEST);
	  glEnable(GL_LIGHTING);
	  glEnable(GL_LIGHT0);
	  glEnable(GL_LIGHT1);
	  glEnable(GL_LIGHT2);
	  glEnable(GL_DEPTH);
 
	  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
 
	  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	  glLightfv(GL_LIGHT0, GL_DIFFUSE, yellowishLight);
 
	  glLightfv(GL_LIGHT1, GL_POSITION, lightPosition2);
	  glLightfv(GL_LIGHT1, GL_DIFFUSE, yellowishLight);
 
	  glLightfv(GL_LIGHT2, GL_POSITION, lightPosition3);
	  glLightfv(GL_LIGHT2, GL_DIFFUSE, blueLight);  
 
	  glEnable (GL_BLEND); 
	  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
  }

  void MyGlWindow::drawCrane()
	  //=================================================================================
  {
 
	
	glPushMatrix();
	glTranslated(0,0.5f,0);

	glColor3f(0,0,0);
	for(int i=0;i<5;i++)
	{
		drawCube2(0,0,0,1.0f);
		glTranslated(0,1.0f,0);
		
	}
	glRotated(Crane_Boom_rotation,0,1,0);
	glTranslated(-2.0f,0,0);
	
	for(int i=0;i<7;i++)
	{
		glTranslated(1.0f,0,0);
		drawCube2(0,0,0,1.0f);
	}

	//Áü
	glPushMatrix();
	glColor3f(0,0.3,0.5);
	glTranslated(-4.0f+(Crane_Box_horizontal/25),-1.0f-Crane_Box_vertical/25,0);
	drawCube(1.0f,1.0f,1.0f);
	glPopMatrix();
	
	glTranslated(-4,0,0);
	glColor3f(1,1,0);
	glBegin(GL_LINES);
	glVertex3f(Crane_Box_horizontal/25,0,0);
	glVertex3f(Crane_Box_horizontal/25,-1.5f-(this->Crane_Box_vertical/25),0);
	glEnd();
	glPopMatrix();
  }
 
  void drawtrigonal(float l,float l2,float l3)
//===============================================================================
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3d( 0,0,1);

	float dx = l*0.5f;
	float dy = l2*0.5f;
	float dz = l3*0.5f;

	glVertex3d( dx, dy, dz);
	glVertex3d(-dx, dy, dz);
	glVertex3d(-dx,-dy, dz);
	glVertex3d( dx,-dy, dz);

	glNormal3d( 0, 0, -1);
	glVertex3d( dx, dy, -dz);
	glVertex3d( dx,-dy, -dz);
	glVertex3d(-dx,-dy, -dz);
	glVertex3d(-dx, dy, -dz);

	//glNormal3d( 0, 1, 0);
	//glVertex3d( dx, dy, dz);
	//glVertex3d( dx, dy,-dz);
	//glVertex3d(-dx, dy,-dz);
	//glVertex3d(-dx, dy, dz);

	glNormal3d( 0,-1,0);
	glVertex3d( dx,-dy, dz);
	glVertex3d(-dx,-dy, dz);
	glVertex3d(-dx,-dy,-dz);
	glVertex3d( dx,-dy,-dz);

	//glNormal3d( 1,0,0);
	//glVertex3d( dx, dy, dz);
	//glVertex3d( dx,-dy, dz);
	//glVertex3d( dx,-dy,-dz);
	//glVertex3d( dx, dy,-dz);

	//glNormal3d(-1,0,0);
	//glVertex3d(-dx, dy, dz);
	//glVertex3d(-dx, dy,-dz);
	//glVertex3d(-dx,-dy,-dz);
	//glVertex3d(-dx,-dy, dz);

	glNormal3d(-.5,.5,-.5);
	glVertex3d(-dx, dy, dz);
	glVertex3d(-dx, dy,-dz);
	glVertex3d(-dx,-dy,-dz);
	glVertex3d(-dx,-dy, dz);

	glEnd();
	glPopMatrix();
}

  void MyGlWindow::drawExcavator(float T1,float T2, float R)
  {
	 glPushMatrix();
	 glTranslated(T1/12.0f,0,T2/12.0f);
	 glRotated(R,0,1,0);
	 

	 glColor3f(0,0,0);
	 ////¹ÙÄû1
	 glPushMatrix();
	 glTranslated(0,.35f,1.0f);
	 drawCube(3.0f,.7f,0.5f);
	 glPopMatrix();

	 ////¹ÙÄû2
	 glPushMatrix();
	 glTranslated(0,.35f,-1.0f);
	 drawCube(3.0f,.7f,0.5f);
	 glPopMatrix();

 	 
	 glRotated(Exc_Spin,0,1,0);
	 glPushMatrix();
	 ////body
	 glColor3f(1,0.8f,0);
	 glPushMatrix();
	 glTranslated(0,1.0f,0);
	 drawCube(3.0f,0.8f,2.0f);
	 glPopMatrix();

	 ///
	 glPushMatrix();
	 glColor3f(1,0.7f,0);
	 glTranslated(-0.7f,1.8f,0);
	 drawCube(1.5f,1.3f,1.8f);
	 glPopMatrix();

	 glRotated(90,0,0,1);
	 ///arm
	 glPushMatrix();
	 glTranslated(2.2f,1.2f,0);
	 glRotated(Exc_Arm,0,0,1);
	 drawCube(0.5f,2.3f,0.5f);
	 glTranslated(0.0f,1.0f,0);

	 //elbow
	 glRotated(Exc_Elbow,0,0,1);
	 glTranslated(0.0f,1.5f,0);
	 drawCube(0.5f,3.0f,0.5f);
	 glTranslated(0.0f,1.5f,0);

	 //busket
	 glColor3f(1,0.8f,0);
	 glRotated(30.0f,0,0,1);
	 glRotated(Exc_Bucket,0,0,1);
	 glTranslated(0,0.1f,0);
	 drawCube(0.2f,0.4f,0.9f);
	 glRotated(90.0f,0,0,1);
	 glTranslatef(0.2f,0.3f,0);
	 drawCube(0.2f,0.6f,0.9f);
	 glPopMatrix();

	 glPopMatrix();
	
	 glPopMatrix();
 
 
  }
 
 void drawCircle(float _x, float _z)
 {
	float r = 0.3f;
	//glColor3f (1.0, 1.0, 1.0);
	glPushMatrix();
		glTranslatef(_x,0.3f,_z);
		glBegin(GL_POLYGON);
		for (int i=0; i<360; i++){
		float degInRad=i*3.14/180;
			glVertex3f(cos(degInRad)*r, sin(degInRad)*r,0);
			//glVertex3f(cos(degInRad)*r, sin(degInRad)*r,0);
		}
		glEnd();
	glPopMatrix();
	//glColor3f (0.3, 0.3, 0.3);
 }

 /////////////////////////////////////////////////////////////´ýÇÁÆ®·°
 void MyGlWindow::drawDump(float x,float z, float DR, float Tip)
 {

	 glPushMatrix();
	 glTranslated(x/12,0,z/12);
	 glRotated(DR,0,1,0);

	 //¹ÙÄû
	 glColor3f (0, 0, 0); //»¡°­
	 drawCircle(1.2f, 0.8f); 
	 glColor3f (0, 0, 0); //ÆÄ¶û
	 drawCircle(-1.2f, 0.8f);
	 glColor3f (0, 0, 0);//ÃÊ·Ï
	 drawCircle(1.2f, -0.8f);
	 glColor3f (0, 0, 0);//³ë¶û
	 drawCircle(-1.2f, -0.8f);

	 //¸öÅë
	 glPushMatrix();
		   
		 //»¡°­ º»Ã¼
		 glPushMatrix();
			glColor3f(1,0.15,0);
			 glTranslated(0,0.5f,0);
			 drawCube(3.0f,0.5f,2.0f);
			 glTranslated(-0.8f,0.5f,0);
			 drawCube(1.0f,1.0f,2.0f);
		 glPopMatrix();

		 glPushMatrix();
			 glColor3f(0.12,0.5,0);		 

			 //ÃÊ·Ï
			 glPushMatrix();
				glTranslated(1.45f, 0.75f,0);
				glRotated(Tip, 0,0,1);
				glTranslated(-0.85f,0.45f,0);
				drawCube(1.8f,0.9f,2.0f);
			 glPopMatrix();
			 
		 glPopMatrix();
	glPopMatrix();
		 

	 glPopMatrix();



 }

void MyGlWindow::drawStuff()
{
//	 polygonf( 4, 20, 0,-25,  20, 0, 25,  20, 30, 25,  20, 30, -25);
   polygonf( -4, 20., 0.,-25.,  20., 0., 25.,  20., 30., 25.,  20., 30., -25.);
}
 
//==========================================================================
void MyGlWindow::draw()
//==========================================================================
{
 
  glViewport(0,0,w(),h());
 
	// clear the window, be sure to clear the Z-Buffer too
  glClearColor(0.2f,0.2f,.2f,0);		// background should be blue
 
 
  glClearStencil(0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glEnable(GL_DEPTH); 
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  
  // now draw the ground plane
  setProjection(); 
  setupFloor(); 
 
  glPushMatrix();
  drawFloor(20,20);
  glPopMatrix();
 
  // now to draw the shadows
 
 
  // Add a sphere to the scene. 
  glBegin(GL_LINES);
  glColor3f(1,0,0);
  glVertex3f(0,0,0);
  glVertex3f(0,100,0);
  glColor3f(0,1,0);
  glVertex3f(0,0,0);
  glVertex3f(100,0,0);
  glColor3f(0,0,1);
  glVertex3f(0,0,0);
  glVertex3f(0,0,100);
  glEnd();
 
 
  setupShadows(); 
     // drawCrane();
      glColor3f(0.2f,0.2f,0.2f);
     // drawExcavator(m_r1,m_r2);

  unsetupShadows();
 
  setupLight(); // ÀÌ°Íµµ ´ÙÀ½ÇÐ±â...
  
  glPushMatrix();
     glColor4f(1,0,0,1);
   drawCrane(); 
	 drawExcavator(Exc_X, Exc_Z, Exc_Rotation);
	 drawDump(Dump_X,Dump_Z,Dump_Rotation, Dump_Tip_amount);
     glColor3f(1,1,0);

	 glTranslated(0,0.5f,0);
	 float mat[16];
	 glGetFloatv(GL_MODELVIEW_MATRIX,mat);
  
 
  glPopMatrix();
 
 
 
 
}
 
void MyGlWindow::setProjection(int clearProjection)
//==========================================================================
{
  glMatrixMode(GL_PROJECTION);
  glViewport(0,0,w(),h());
  if (clearProjection)
	glLoadIdentity();
  // compute the aspect ratio so we don't distort things
  double aspect = ((double) w()) / ((double) h());
  gluPerspective(fieldOfView, aspect, 1, 1000);
 
  // put the camera where we want it to be
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  // use the transformation in the ArcBall
 
 
 	if (camMode == 0) {
		gluLookAt(
			m_viewer->getViewPoint().x(), m_viewer->getViewPoint().y(), m_viewer->getViewPoint().z(), 
			m_viewer->getViewCenter().x(), m_viewer->getViewCenter().y(), m_viewer->getViewCenter().z(), 
			m_viewer->getUpVector().x(), m_viewer->getUpVector().y(), m_viewer->getUpVector().z()
			);
	}
	else {
		float posx=Exc_X/12;
		float posz=Exc_Z/12;

		gluLookAt((posx)-cos((Exc_Rotation+Exc_Spin)*pi/180)*2,		1.0f,	(posz)+sin((Exc_Rotation+Exc_Spin)*pi/180)*2,
			      (posx)-cos((Exc_Rotation+Exc_Spin)*pi/180)*10,	1.0f,	(posz)+sin((Exc_Rotation+Exc_Spin)*pi/180)*10,
			0,1,0);
	}
    
  glDisable (GL_BLEND); 
}
 
static int last_push;
int m_pressedMouseButton;
int m_lastMouseX;
int m_lastMouseY;
 
int MyGlWindow::handle(int e)
//==========================================================================
{
 
  switch(e) {
  case FL_SHOW:		// you must handle this, or not be seen!
	  show();
	  return 1;
  case FL_PUSH:
	  {
		 
		  m_pressedMouseButton = Fl::event_button();
 
	//	  m_viewer->setAspectRatio( static_cast<double>(this->w()) / static_cast<double>(this->h()) );
 
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
			  m_viewer->translate( -fractionChangeX, -fractionChangeY, (Fl::event_key(FL_Shift_L) == 0) || (Fl::event_key(FL_Shift_R) == 0));
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
 
 
//
// get the mouse in NDC
//==========================================================================
void MyGlWindow::getMouseNDC(float& x, float& y)
//==========================================================================
{
	// notice, we put everything into doubles so we can do the math
	  float mx = (float) Fl::event_x();	// remeber where the mouse went down
	  float my = (float) Fl::event_y();
 
	  // we will assume that the viewport is the same as the window size
	  float wd = (float) w();
	  float hd = (float) h();
 
	  // remember that FlTk has Y going the wrong way!
	  my = hd-my;
	  x = (mx / wd) * 2.0f - 1.f;
	  y = (my / hd) * 2.0f - 1.f;
}
 