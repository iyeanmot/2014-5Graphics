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
	Vec3f pos;  //��ġ
	Vec3f velocity; //���� �ӵ�m
	Vec3f color; //����
	float alpha;
	float timeAlive; //��ƼŬ�� ���� ���� ����ִ� �ð�.
	float lifespan;  //����Ŭ�� ����

	Particle();//�⺻ ������
	void ParticleStep();
	void ReStartparticle();
};

class ParticleEngine {
public:
   Particle particles[NUM_PARTICLES];  //NUM_PARTICLES = 1000
   Vec3f currentDir();  //���� ������ �л���������� ���� ��ȯ
   void createParticle(Particle* p); //���ο� ��ƼŬ�� ����
   void step(); //�� step ������Ʈ ��
   
   float dir;  //�л� ���� ���� : (0~360.0)
   float disperse; //�л� ���� ����: (0~1.0)
   float height; //�л� ���� ���� (0~10)
   ParticleEngine();  //������
   void draw();  //��ƼŬ draw
   float randRange(float v);
};
