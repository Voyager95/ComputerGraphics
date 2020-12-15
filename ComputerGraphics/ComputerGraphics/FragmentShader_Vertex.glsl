#version 330
//--- ex_Color: 버텍스 세이더에서 입력받는 색상 값
//--- gl_FragColor: 출력할 색상의 값으로 응용 프로그램으로 전달 됨.

in vec3 ex_Color; //--- 버텍스 세이더에게서 전달 받음
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