#version 330
//--- in_Position: attribute index 0
//--- in_Color: attribute index 1

in vec3 in_Position; //--- ��ġ �Ӽ�
in vec3 in_Color; //--- ���� �Ӽ�
in vec3 in_Normal;
in vec2 in_UV;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 proj;

out vec3 ex_Color; // �����׸�Ʈ ���̴����� ����
out vec3 ex_Normal;
out vec2 ex_UV;

void main(void)
{
	gl_Position = proj*view*transform * vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
	ex_Color = in_Color;
	ex_Normal = in_Normal;
	ex_UV = in_UV;
}