// the main routine makes the window, and then runs an even loop
// until the window is closed
#include <windows.h>
#include <iostream>

#include <FL/Fl_Gl_Window.h>
#include <Fl/Fl.h>
#include <Fl/Fl_Value_Slider.H>
#include <Fl/Fl_Button.h>
#include <Fl/Fl_Choice.h>
#include <FL/Fl_Box.h>
#include "MyGlWindow.h"
#include "RunButton.H"

using namespace std;

Fl_Group* widgets;

Fl_Button *worldCam;
Fl_Button *driverCam;




//////////////////크레인 CallBack함수//////////////
void Boom_rotationCB(Fl_Widget*w, Fl_Widget* o)
{
	//Boom rotation 
	Fl_Value_Slider * slider = (Fl_Value_Slider *) w;


	MyGlWindow * win = (MyGlWindow *) o;
	win->Crane_Boom_rotation = slider->value();
	win->damage(1);
}

void Box_horizontalCB(Fl_Widget*w, Fl_Widget* o)
{
	//Box horizontal  
	Fl_Value_Slider * slider = (Fl_Value_Slider *) w;

	MyGlWindow * win = (MyGlWindow *) o;
	win->Crane_Box_horizontal = slider->value();
	win->damage(1);
}

void Box_verticalCB(Fl_Widget*w, Fl_Widget* o)
{
	//Box horizontal  
	Fl_Value_Slider * slider = (Fl_Value_Slider *) w;

	MyGlWindow * win = (MyGlWindow *) o;
	win->Crane_Box_vertical = slider->value();
	win->damage(1);
}
////////////////////////////////////////////////////////

//////////////////포크레인 CallBack함수//////////////
void excX_positionCB(Fl_Widget*w, Fl_Widget* o)
{
	//Box horizontal  
	Fl_Value_Slider * slider = (Fl_Value_Slider *) w;

	MyGlWindow * win = (MyGlWindow *) o;
	win->Exc_X = slider->value();
	win->damage(1);
}

void excZ_positionCB(Fl_Widget*w, Fl_Widget* o)
{
	//Box horizontal  
	Fl_Value_Slider * slider = (Fl_Value_Slider *) w;

	MyGlWindow * win = (MyGlWindow *) o;
	win->Exc_Z = slider->value();
	win->damage(1);
}

void excRotationCB(Fl_Widget*w, Fl_Widget* o)
{
	//Box horizontal  
	Fl_Value_Slider * slider = (Fl_Value_Slider *) w;

	MyGlWindow * win = (MyGlWindow *) o;
	win->Exc_Rotation = slider->value();
	win->damage(1);
}

void excSpinCB(Fl_Widget*w, Fl_Widget* o)
{
	//Box horizontal  
	Fl_Value_Slider * slider = (Fl_Value_Slider *) w;

	MyGlWindow * win = (MyGlWindow *) o;
	win->Exc_Spin = slider->value();
	win->damage(1);
}

void excArmCB(Fl_Widget*w, Fl_Widget* o)
{
	//Box horizontal  
	Fl_Value_Slider * slider = (Fl_Value_Slider *) w;

	MyGlWindow * win = (MyGlWindow *) o;
	win->Exc_Arm = slider->value();
	win->damage(1);
}

void excElbowCB(Fl_Widget*w, Fl_Widget* o)
{
	//Box horizontal  
	Fl_Value_Slider * slider = (Fl_Value_Slider *) w;

	MyGlWindow * win = (MyGlWindow *) o;
	win->Exc_Elbow = slider->value();
	win->damage(1);
}

void excBucketCB(Fl_Widget*w, Fl_Widget* o)
{
	//Box horizontal  
	Fl_Value_Slider * slider = (Fl_Value_Slider *) w;

	MyGlWindow * win = (MyGlWindow *) o;
	win->Exc_Bucket = slider->value();
	win->damage(1);
}
////////////////////////////////////////////////////////

//////////////////덤프트럭 CallBack함수//////////////
void DumpX_positionCB(Fl_Widget*w, Fl_Widget* o)
{
	//Box horizontal  
	Fl_Value_Slider * slider = (Fl_Value_Slider *) w;

	MyGlWindow * win = (MyGlWindow *) o;
	win->Dump_X = slider->value();
	win->damage(1);
}

void DumpZ_positionCB(Fl_Widget*w, Fl_Widget* o)
{
	//Box horizontal  
	Fl_Value_Slider * slider = (Fl_Value_Slider *) w;

	MyGlWindow * win = (MyGlWindow *) o;
	win->Dump_Z = slider->value();
	win->damage(1);
}

void DumpRotationCB(Fl_Widget*w, Fl_Widget* o)
{
	//Box horizontal  
	Fl_Value_Slider * slider = (Fl_Value_Slider *) w;

	MyGlWindow * win = (MyGlWindow *) o;
	win->Dump_Rotation = slider->value();
	win->damage(1);
}

void Tip_amountCB(Fl_Widget*w, Fl_Widget* o)
{
	//Box horizontal  
	Fl_Value_Slider * slider = (Fl_Value_Slider *) w;

	MyGlWindow * win = (MyGlWindow *) o;
	win->Dump_Tip_amount = slider->value();
	win->damage(1);
}
///////////////////////////////////////////////////////

void cameraCB(Fl_Button* b, MyGlWindow* csw)
{
	if (worldCam->value())
		csw->camMode = 0;
	else if (driverCam->value())
		csw->camMode = 1;

	csw->damage(1);
}
////////////////////////////////////////////////////////


int main()
{
	Fl::scheme("plastic") ; // plastic "gtk+"
	int width = 800;
	int height = 800;
	Fl_Double_Window* wind = new Fl_Double_Window(100,100,1000,height,"GL 3D FrameWork");

	wind->begin();		// put widgets inside of the window
	MyGlWindow* gl = new MyGlWindow(10,10,width-20,height-50);
	

	widgets = new Fl_Group(820,5,190,590);
	widgets->begin();


	worldCam = new Fl_Button(820, 15, 50, 20, "world");
	worldCam->type(102);
	worldCam->value(1);
	worldCam->selection_color((Fl_Color)3);
	worldCam->callback((Fl_Callback*)cameraCB,gl);

	driverCam = new Fl_Button(870, 15, 60, 20, "driver");
	driverCam->type(102);
	driverCam->selection_color((Fl_Color)3);
	driverCam->callback((Fl_Callback*)cameraCB,gl);



	//크레인
    Fl_Value_Slider * Boom_rotation = new Fl_Value_Slider(820,50,150,20, "Boom rotation");
 	Boom_rotation->type(5);
	Boom_rotation->minimum(0);
	Boom_rotation->maximum(360);
	Boom_rotation->callback((Fl_Callback*) Boom_rotationCB, gl);

	Fl_Value_Slider * Box_horizontal = new Fl_Value_Slider(820,90,150,20, "Box horizontal");
	Box_horizontal->type(5);
	Box_horizontal->minimum(0);
	Box_horizontal->maximum(100);
	Box_horizontal->callback((Fl_Callback*) Box_horizontalCB, gl);

	Fl_Value_Slider * Box_vertical = new Fl_Value_Slider(820,130,150,20, "Box vertical");
	Box_vertical->type(5);
	Box_vertical->minimum(0);
	Box_vertical->maximum(100);
	Box_vertical->callback((Fl_Callback*) Box_verticalCB, gl);


	//포크레인
	Fl_Value_Slider * ExcX = new Fl_Value_Slider(820,170,150,20, "X position");
	ExcX->type(5);
	ExcX->minimum(-100);
	ExcX->maximum(100);
	ExcX->callback((Fl_Callback*) excX_positionCB, gl);

	Fl_Value_Slider * ExcZ = new Fl_Value_Slider(820,210,150,20, "Z position");
	ExcZ->type(5);
	ExcZ->minimum(-100);
	ExcZ->maximum(100);
	ExcZ->callback((Fl_Callback*) excZ_positionCB, gl);

	Fl_Value_Slider * ExcRotation = new Fl_Value_Slider(820,250,150,20, "Rotation");
	ExcRotation->type(5);
	ExcRotation->minimum(0);
	ExcRotation->maximum(360);
	ExcRotation->callback((Fl_Callback*) excRotationCB, gl);

	Fl_Value_Slider * ExcSpin = new Fl_Value_Slider(820,290,150,20, "Spin");
	ExcSpin->type(5);
	ExcSpin->minimum(-180);
	ExcSpin->maximum(180);
	ExcSpin->callback((Fl_Callback*) excSpinCB, gl);

	Fl_Value_Slider * ExcArm = new Fl_Value_Slider(820,330,150,20, "Arm");
	ExcArm->type(5);
	ExcArm->value(-30);
	ExcArm->minimum(-90);
	ExcArm->maximum(0);
	ExcArm->callback((Fl_Callback*) excArmCB, gl);

	Fl_Value_Slider * ExcElbow = new Fl_Value_Slider(820,370,150,20, "Elbow");
	ExcElbow->type(5);
	ExcElbow->value(50);
	ExcElbow->minimum(0);
	ExcElbow->maximum(180);
	ExcElbow->callback((Fl_Callback*) excElbowCB, gl);

	Fl_Value_Slider * ExcBucket = new Fl_Value_Slider(820,410,150,20, "Bucket");
	ExcBucket->type(5);
	ExcBucket->value(-30);
	ExcBucket->minimum(-180);
	ExcBucket->maximum(45);
	ExcBucket->callback((Fl_Callback*) excBucketCB, gl);


	//덤프트럭
	Fl_Value_Slider * DumpX_position = new Fl_Value_Slider(820,450,150,20, "X position");
	DumpX_position->type(5);
	DumpX_position->minimum(-100);
	DumpX_position->maximum(100);
	DumpX_position->callback((Fl_Callback*) DumpX_positionCB, gl);

	Fl_Value_Slider * DumpZ_position = new Fl_Value_Slider(820,490,150,20, "Z position");
	DumpZ_position->type(5);
	DumpZ_position->minimum(-100);
	DumpZ_position->maximum(100);
	DumpZ_position->callback((Fl_Callback*) DumpZ_positionCB, gl);

	Fl_Value_Slider * DumpRotation = new Fl_Value_Slider(820,530,150,20, "Rotation");
	DumpRotation->type(5);
	DumpRotation->minimum(0);
	DumpRotation->maximum(360);
	DumpRotation->callback((Fl_Callback*) DumpRotationCB, gl);

	Fl_Value_Slider * Tip_amount = new Fl_Value_Slider(820,570,150,20, "Tip amount");
	Tip_amount->type(5);
	Tip_amount->minimum(-90);
	Tip_amount->maximum(0);
	Tip_amount->callback((Fl_Callback*) Tip_amountCB, gl);

/////////////////////////////////////////////////////////////////////////////////////////



	Fl_Box* resizebox = new Fl_Box(820,595,200,5);
	widgets->resizable(resizebox);
	widgets->end();


	RunSlider* rt = new RunSlider(gl,800,400, height-30,190,20);
	gl->time = rt;
	wind->resizable(gl);

	Fl_Choice *	stepRate = new Fl_Choice(700,height-30, 100, 20);
	stepRate->down_box(FL_BORDER_BOX);
	stepRate->labelsize(10);
	stepRate->textsize(10);
	stepRate->add("60"  ,0,0,(void*)60);
	stepRate->add("30"  ,0,0,(void*)30);
	stepRate->add("15"  ,0,0,(void*)15);
	stepRate->add("10"  ,0,0,(void*)10);
	stepRate->add("5"   ,0,0,(void*)5);
	stepRate->value(1);

	RunButton* rb = new RunButton(rt, stepRate, 600,height-30,80,20);


	wind->end();



	wind->show();	// this actually opens the window


	Fl::run();
	delete wind;

	return 1;
}

