#version 330
//--- ex_Color: ���ؽ� ���̴����� �Է¹޴� ���� ��
//--- gl_FragColor: ����� ������ ������ ���� ���α׷����� ���� ��.

in vec3 ex_Color; //--- ���ؽ� ���̴����Լ� ���� ����
in vec3 ex_Normal;
in vec2 ex_UV; 

uniform sampler2D tex;
uniform vec3 ambientLightColor;
uniform float ambientLightStrength;

void main(void)
{
	vec3 ambient = ambientLightStrength * ambientLightColor;

	vec3 result = ambient * ex_Color;
	gl_FragColor = vec4(result,1.0);
}