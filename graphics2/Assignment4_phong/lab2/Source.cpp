


#include <iostream>
#include <windows.h>


#include <gl/glew.h>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <Fl/Fl_Gl_Window.H>

#include "MyGlWindow.h"

//glm 추가

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>



int main()
{
	////연산
	//glm::vec3 p(1,4,-5); glm::vec3 p2(5,1,4);
	//p = p+p2;
	//std::cout << glm::to_string(p) << std::endl;
	//
	//glm::vec3 v1(1,0,0); glm::vec3 v2(0,1,0);
	//v1 = v1 +v2; 
	//std::cout << glm::to_string(v1) << std::endl;

	//glm::vec3 v3(1,3,4); glm::vec3 v4;
	//v4 = v3 * 5.0f;
	//std::cout << glm::to_string(v4) << std::endl;

	//glm::vec3 v5(8,2,5); glm::vec3 v6(1,-1,4);
	//v6 = v6-v5;
	//std::cout << glm::to_string(v6) << std::endl;

	//glm::vec3 v7(1,3,4);
	//v7 = glm::normalize(v7);
	//std::cout << glm::to_string(v7) << std::endl;
	//
	////내적외적
	//float f = glm::dot(p, p2);
	//std::cout << f << std::endl;


	//glm::vec3 n;
	//n = glm::cross(v1, v2);
	//std::cout << glm::to_string(n) << std::endl;

//	const double DEGREES_TO_RADIANS = glm::pi<float>() / 180.0;
//const double RADIANS_TO_DEGREES = 180.0 / glm::pi<float>();
//
//
//	//각도구하기
//	glm::vec3 v(2, -1, 1);
//	glm::vec3 u(1, 1, 2);
//
//	float d = glm::dot(v, u);
//	float c = d / (glm::length(u) * glm::length(v));
//	float deg = glm::acos(c)*RADIANS_TO_DEGREES;
//	std::cout << deg << std::endl;
//

	Fl::scheme("plastic");// plastic
	int width = 800;
	int height = 800;
	Fl_Double_Window* wind = new Fl_Double_Window(100, 100, width, height, "GL 3D FrameWork");

	wind->begin();		// put widgets inside of the window
	MyGlWindow* gl = new MyGlWindow(10, 10, width - 20, height - 50);

	wind->resizable(gl);
	wind->show();	// this actually opens the window


	Fl::run();
	delete wind;

	return 1;

}
