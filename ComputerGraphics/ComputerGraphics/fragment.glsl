#version 330
//--- ex_Color: ���ؽ� ���̴����� �Է¹޴� ���� ��
//--- gl_FragColor: ����� ������ ������ ���� ���α׷����� ���� ��.

in vec3 ex_Color; //--- ���ؽ� ���̴����Լ� ���� ����
in vec3 ex_Normal;
in vec2 ex_UV; 

//out vec4 gl_FragColor; //--- ���� ���
uniform sampler2D tex;

void main(void)
{
	//gl_FragColor = vec4(ex_Color,1.0);
	gl_FragColor = texture(tex,  ex_UV);
}