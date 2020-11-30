#pragma once
#include "stdafx.h"
class Object;

class GlobalUtility
{
public:
	//--- 싱글톤 디자인
	GlobalUtility(const GlobalUtility&) = delete;
	GlobalUtility& operator=(const GlobalUtility&) = delete;

	/// <summary>
	/// 싱글톤 인스턴스를 얻습니다.
	/// *없는 경우 새로 만들어서 반환해줄 것입니다.
	/// </summary>
	/// <returns>싱글톤 인스턴스</returns>
	static GlobalUtility& GetInstance();
private:
	GlobalUtility();
public:

	int presentWinSize_X;
	int presentWinSize_Y;
public:

	//--- StaticMethod
	static char* Filetobuf(const char* file)
	{
		FILE* fptr;
		long length;
		char* buf;
		fptr = fopen(file, "rb"); // Open file for reading
		if (!fptr) // Return NULL on failure
			return NULL;
		fseek(fptr, 0, SEEK_END); // Seek to the end of the file
		length = ftell(fptr); // Find out how many bytes into the file we are
		buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator
		fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file
		fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer
		fclose(fptr); // Close the file
		buf[length] = 0; // Null terminator
		return buf; // Return the buffer
	}

	static glm::vec3 Lerp(glm::vec3 from, glm::vec3 to, float factor);

	static void PrintVec3(std::string name, glm::vec3 value);
};

