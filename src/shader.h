#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

class Shader
{
public:
	Shader(std::vector<std::string> paths, std::vector<int> types);

	void use();

	void setBool(const char* name, bool value);
	void setInt(const char* name, int value);
	void setFloat(const char* name, float value);
	void setVec2(const char* name, const glm::vec2& value);
	void setVec2(const char* name, float x, float y);
	void setVec3(const char* name, const glm::vec3& value);
	void setVec3(const char* name, float x, float y, float z);
	void setVec4(const char* name, const glm::vec4& value);
	void setVec4(const char* name, float x, float y, float z, float w);
	void setMat2(const char* name, const glm::mat2& value);
	void setMat3(const char* name, const glm::mat3& value);
	void setMat4(const char* name, const glm::mat4& value);
private:
	unsigned int programId;
};
