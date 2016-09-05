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

#include <ctime>
#include <Fl/Fl_Choice.h>

Fl_Group* widgets;



long lastRedraw;
int frameRate = 30;

void changeFrameCB(Fl_Widget * w, void* data)
{	
	Fl_Choice * widget = (Fl_Choice *) w;
	int i = widget->value();
	const char * menu = widget->text(i);
	frameRate = atoi(menu);

	MyGlWindow * win = (MyGlWindow *) data;
	win->redraw();
}


void idleCB(void* w)
{	
	MyGlWindow * win = (MyGlWindow *) w;
	if (clock() - lastRedraw > CLOCKS_PER_SEC/frameRate) {
		win->particleEngine.step();
		lastRedraw = clock();

		
	}
	win->redraw();
}
////////////////////// 사용자 인터페이스
void DirCB(Fl_Widget * w, void* data)
{
 MyGlWindow * win = (MyGlWindow *) data;
 Fl_Value_Slider * slider = (Fl_Value_Slider *) w;
 float value = slider->value();

 win->particleEngine.dir = value;
 std::printf("%f\n",slider->value());
 win->damage(1);
}

void DisperseCB(Fl_Widget * w, void* data)
{
 MyGlWindow * win = (MyGlWindow *) data;
 Fl_Value_Slider * slider = (Fl_Value_Slider *) w;

 win->particleEngine.disperse = slider->value();
 win->damage(1);
}

void HeightCB(Fl_Widget * w, void* data)
{
 MyGlWindow * win = (MyGlWindow *) data;
 Fl_Value_Slider * slider = (Fl_Value_Slider *) w;

 win->particleEngine.height = slider->value();
 win->damage(1);
}
///////////////////////////////////////




int main()
{
	Fl::scheme("plastic") ;// plastic
	int width = 800;
	int height = 800;
	Fl_Double_Window* wind = new Fl_Double_Window(100,100,width,height,"GL 3D FrameWork");

	
	wind->begin();		// put widgets inside of the window
		MyGlWindow* gl = new MyGlWindow(10,10,width-20,height-50);
	

		widgets = new Fl_Group(820,5,190,590);
		widgets->begin();
			Fl_Box* resizebox = new Fl_Box(820,595,200,5);
			widgets->resizable(resizebox);
		widgets->end();


		Fl_Choice* choice;
		choice = new Fl_Choice(100,height-40,50,20,"FrameRate"); 
		choice->add("15");
		choice->add("30");
		choice->add("60");
		choice->value(1);

		// 	Fl_Button* but = new Fl_Button(300,300,50,50,"Selected");
		choice->callback((Fl_Callback*)changeFrameCB, gl);
		Fl::add_idle((void (*)(void*)) idleCB, gl);  //
		////////////////////// 사용자 인터페이스
  //분사방향 조절
  Fl_Value_Slider * SliderDir = new Fl_Value_Slider(200,height-40, 100, 20,"dir");
  //Fl_Slider * Slider2 = new Fl_Slider(200,height-40, 100, 20);
  SliderDir->minimum(0);
  SliderDir->maximum(360);
  SliderDir->type(FL_HORIZONTAL);
  SliderDir->value(0);
  SliderDir->callback((Fl_Callback*)DirCB,gl); //콜백함수호출

  //분사정도 조절
  Fl_Value_Slider * SliderDisperse = new Fl_Value_Slider(350,height-40, 100, 20,"Disperse");
  SliderDisperse->minimum(0);
  SliderDisperse->maximum(1.0);
  SliderDisperse->type(FL_HORIZONTAL);
  SliderDisperse->value(0.2);
  SliderDisperse->callback(DisperseCB,gl);

  //분사높이 조절
  Fl_Value_Slider * SliderHeight = new Fl_Value_Slider(500,height-40, 100, 20,"Height");
  SliderHeight->minimum(0);
  SliderHeight->maximum(10);
  SliderHeight->type(FL_HORIZONTAL);
  SliderHeight->value(2);
  SliderHeight->callback(HeightCB,gl);

  //////////////////////////////////////



	wind->end();

	wind->show();	// this actually opens the window

	Fl::run();
	delete wind;

	return 1;
}

