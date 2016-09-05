#include <FL/Fl_Gl_Window.h>
#include <Fl/Fl.h>
#include <Fl/Fl_Value_Slider.H>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <Fl/Fl_Double_Window.h>
#include <iostream>
#include "Vec3f.h"
#include <ctime>
#include "stdio.h"
#include "math.h"
#include "3DUtils.h"
#include "Viewer.h"
#include <vector>


const int NUM_PARTICLES = 1000;

class Particle {
public:
	Vec3f pos;  //위치
	Vec3f velocity; //현재 속도m
	Vec3f color; //색상
	float alpha;
	float timeAlive; //파티클의 현재 까지 살아있는 시간.
	float lifespan;  //파이클의 생명

	Particle();//기본 생성자
	void ParticleStep();
	void ReStartparticle();
};

class ParticleEngine {
public:
   Particle particles[NUM_PARTICLES];  //NUM_PARTICLES = 1000
   Vec3f currentDir();  //현재 설정된 분사방향으로의 벡터 반환
   void createParticle(Particle* p); //새로운 파티클을 생성
   void step(); //한 step 업데이트 함
   
   float dir;  //분사 방향 조절 : (0~360.0)
   float disperse; //분사 범위 조절: (0~1.0)
   float height; //분사 높이 조절 (0~10)
   ParticleEngine();  //생성자
   void draw();  //파티클 draw
   float randRange(float v);
};
