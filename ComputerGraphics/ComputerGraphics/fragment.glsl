#version 330
//--- ex_Color: ���ؽ� ���̴����� �Է¹޴� ���� ��
//--- gl_FragColor: ����� ������ ������ ���� ���α׷����� ���� ��.

in vec3 ex_Color; //--- ���ؽ� ���̴����Լ� ���� ����

//out vec4 gl_FragColor; //--- ���� ���

void main(void)
{
	gl_FragColor = vec4(ex_Color,1.0);
}