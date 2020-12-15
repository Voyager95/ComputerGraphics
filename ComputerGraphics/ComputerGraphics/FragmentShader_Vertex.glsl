#version 330
//--- ex_Color: 버텍스 세이더에서 입력받는 색상 값
//--- gl_FragColor: 출력할 색상의 값으로 응용 프로그램으로 전달 됨.

in vec3 ex_Color; //--- 버텍스 세이더에게서 전달 받음
in vec3 ex_Normal;
in vec2 ex_UV; 
in vec3 ex_FragPos;
in vec3 ex_ViewPos;

uniform sampler2D tex;
uniform vec3 ambientLightColor;
uniform float ambientLightStrength;
uniform vec3 lightPos;

void main(void)
{
	vec3 ambient = ambientLightStrength * ambientLightColor;

	vec3 normalVector = normalize(ex_Normal);
	vec3 lightDir = normalize(lightPos - ex_FragPos);
	float diffuseLight = max(dot(normalVector,lightDir),0.0);
	vec3 diffuse = diffuseLight * ambientLightColor;

	int shininess = 128;
	vec3 viewDir = normalize(ex_ViewPos - ex_FragPos);
	vec3 reflectDir = reflect(-lightDir, normalVector);
	float specularLight = max(dot(viewDir,reflectDir),0.0);
	specularLight = pow(specularLight, shininess);


	vec3 result = (ambient + diffuse + lightPos) * ex_Color;
	gl_FragColor = vec4(result,1.0);
}