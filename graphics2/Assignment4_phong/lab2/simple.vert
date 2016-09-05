#version 400

//qualifier(in: vertex attribute(�Ӽ�), out:���)
in vec4 coord3d; 
in vec3 v_color;
in vec3 v_normal;

out vec3 f_color; //
//uniform : ���ø����̼����κ��� �Ѱܹ��� ���� ������, 
//			���̴� �ȿ��� ����Ұ�, ���� reading��
uniform mat4 mvp; //model view projection Matrix


void main(void)

{
   gl_Position =  mvp * coord3d;
   f_color = v_color;
  
}