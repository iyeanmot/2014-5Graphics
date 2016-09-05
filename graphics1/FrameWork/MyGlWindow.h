
#include <FL/Fl_Gl_Window.h>
#include <Fl/Fl.h>
#include <Fl/Fl_Value_Slider.H>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <Fl/Fl_Double_Window.h>

#include "stdio.h"
#include "math.h"
#include "3DUtils.h"

#include "Vec3f.h"
#include "Viewer.h"
#include <vector>

class MyGlWindow : public Fl_Gl_Window {
	public:
		MyGlWindow(int x, int y, int w, int h);
		

		std::vector<Vec3f *> history;

		//크레인
		float Crane_Boom_rotation;
		float Crane_Box_horizontal;
		float Crane_Box_vertical;
		//포크레인
		float Exc_X;
		float Exc_Y;
		float Exc_Z;				
		float Exc_Rotation;
		float Exc_Spin;
		float Exc_Arm;
		float Exc_Elbow;
		float Exc_Bucket;
		//덤프트럭
		float Dump_X;
		float Dump_Z;
		float Dump_Rotation;
		float Dump_Tip_amount;


		Fl_Slider* time;	
		int run;
		int camMode;
		
		void drawStuff();
		void drawCrane();
		void drawExcavator(float r1,float r2, float R);
		void drawDump(float T1,float T2, float R, float Tip);

	private:
		void draw();					// standard FlTk
		int handle(int);				// standard FlTk
		
		float fieldOfView;
		Viewer *m_viewer;
		void setProjection(int clearProjection = 1);
		void getMouseNDC(float& x, float& y);
		void setupLight();
};

