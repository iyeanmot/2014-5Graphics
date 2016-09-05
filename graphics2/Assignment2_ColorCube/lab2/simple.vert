#version 400
in vec3 coord3d;
in vec3 v_color;

out vec3 f_color;

void main(void)

{
   gl_Position =  vec4(coord3d,1.0);
   f_color = v_color;
  
}
