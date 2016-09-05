#version 400

//qualifier(in: vertex attribute(속성), out:출력)
in vec4 coord3d; 
in vec3 v_color;
in vec3 v_normal;

out vec3 f_color; //
//uniform : 어플리케이션으로부터 넘겨받은 전역 데이터, 
//			쉐이더 안에서 변경불가, 오직 reading만
uniform mat4 mvp; //model view projection Matrix


void main(void)

{
   gl_Position =  mvp * coord3d;
   f_color = v_color;
  
}