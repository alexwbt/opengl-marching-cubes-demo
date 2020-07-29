#pragma once

#include <glm/glm.hpp>
#include <vector>

class Shader;

enum class LightType {
	SUN, POINT, SPOT
};

struct LightColor {
	glm::vec3 ambient, diffuse, specular;
};

struct LightStrength {
	float constant, linear, quadratic;
};

class Light
{
public:
	static std::vector<Light*> lights;
	static void update(Shader* shader);

	Light(glm::vec3 direction, LightColor color);
	Light(glm::vec3 position, LightColor color, LightStrength strength);
	Light(glm::vec3 position, glm::vec3 direction, LightColor color, LightStrength strength, float cutOff, float outerCutOff);

	void setPosition(glm::vec3 position);
	void setDirection(glm::vec3 direction);
	void setColor(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	void setStrength(float constant, float linear, float quadratic);
	void setCutOff(float cutOff, float outerCutOff);

	void useLight(Shader* shader, int i);
private:
	LightType type;

	glm::vec3 position, direction, ambient, diffuse, specular;
	float constant, linear, quadratic, cutOff, outerCutOff;
};
