#include "particle.h"


const float GRAVITY = 2.9;

Particle::Particle()
{
}

void Particle::ParticleStep()
{
	float time_step = 0.05f;
	Vec3f acceleration = Vec3f(0.0f, -GRAVITY*time_step, 0.0f);

	velocity = velocity + acceleration;
	pos = pos + (velocity * time_step);
	timeAlive += time_step*0.5f;	
}

void Particle::ReStartparticle()
{
	pos = Vec3f(0,2,0);
	color = Vec3f(0.7f,0.6f,0.4f);
	alpha = 1.0f;
	timeAlive = 0;
	lifespan = (float)rand()/(float)RAND_MAX;
}

ParticleEngine::ParticleEngine()
{
	this->dir = 0;
	this->disperse = 0.2f;
	this->height = 2;

	for (int i=0; i<NUM_PARTICLES; i++) {
		Particle * p = &particles[i];
		createParticle(p);
	}
}

Vec3f ParticleEngine::currentDir()
{
	//라디안 값으로 줘야함
	float x, z;
	float dir = (this->dir*3.14)/180;

	x = cos(dir) -sin(dir);
	z = sin(dir) -cos(dir);
	Vec3f v = Vec3f(x, this->height, z);
	v.normalize();
	return v;
}

void ParticleEngine::createParticle(Particle* p)
{
	Vec3f v = this->currentDir();
	p->velocity  = v + Vec3f( randRange(disperse), randRange(disperse), randRange(disperse));
	p->ReStartparticle();
	//std::cout<<randRange(disperse)<<std::endl;
}

float ParticleEngine::randRange(float v)
{

	//rand() -> (0, RAND_MAX) -> (0,1) -> 2v * (0,2v) -> -v 
	float result;
	result = (float)rand()/(float)RAND_MAX;
	result *= 2*v;
	result -= v;
	//std::cout<<v<<std::endl;
	return result; 
}

void ParticleEngine::step()
{

	for(int i=0; i<NUM_PARTICLES; i++)
	{
		Particle * p = &particles[i];
		p->ParticleStep();

		if(p->timeAlive > p->lifespan)
		{
			createParticle(p);
		}
	}
}

void ParticleEngine::draw()
{

	glPointSize(3.0);
	glBegin(GL_POINTS);
		
	for(int i=0; i<NUM_PARTICLES; i++)
	{
		
		Particle *p = &particles[i];
		glColor4f(p->color.x(),p->color.y(),p->color.z(),1.0f-p->timeAlive);
		glVertex3f(p->pos.x(), p->pos.y(),p->pos.z());
		
	}
	glEnd();
}