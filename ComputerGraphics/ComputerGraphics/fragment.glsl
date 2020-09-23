#version 330
//--- ex_Color: 버텍스 세이더에서 입력받는 색상 값
//--- gl_FragColor: 출력할 색상의 값으로 응용 프로그램으로 전달 됨.

in vec3 ex_Color; //--- 버텍스 세이더에게서 전달 받음

//out vec4 gl_FragColor; //--- 색상 출력

void main(void)
{
	gl_FragColor = vec4(ex_Color,1.0);
}