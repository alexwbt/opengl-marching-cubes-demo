#include "light.h"
#include "shader.h"

#include <string>


std::vector<Light*> Light::lights;

void Light::update(Shader* shader)
{
	int sizes[3] = { 0, 0, 0 };
	for (int i = 0; i < lights.size(); i++)
	{
		int type = (int)lights[i]->type;
		lights[i]->useLight(shader, sizes[type]);
		sizes[type]++;
	}
	shader->setInt("sunLights_size", sizes[0]);
	shader->setInt("lights_size", sizes[1]);
	shader->setInt("spotLights_size", sizes[2]);
}


Light::Light(glm::vec3 direction, LightColor color)
{
	type = LightType::SUN;

	this->position = glm::vec3(0);
	this->direction = direction;

	ambient = color.ambient;
	diffuse = color.diffuse;
	specular = color.specular;

	constant = 0;
	linear = 0;
	quadratic = 0;

	this->cutOff = 0;
	this->outerCutOff = 0;
}

Light::Light(glm::vec3 position, LightColor color, LightStrength strength)
{
	type = LightType::POINT;

	this->position = position;
	this->direction = glm::vec3(0);

	ambient = color.ambient;
	diffuse = color.diffuse;
	specular = color.specular;

	constant = strength.constant;
	linear = strength.linear;
	quadratic = strength.quadratic;

	this->cutOff = 0;
	this->outerCutOff = 0;
}

Light::Light(glm::vec3 position, glm::vec3 direction, LightColor color, LightStrength strength, float cutOff, float outerCutOff)
{
	type = LightType::SPOT;

	this->position = position;
	this->direction = direction;

	ambient = color.ambient;
	diffuse = color.diffuse;
	specular = color.specular;

	constant = strength.constant;
	linear = strength.linear;
	quadratic = strength.quadratic;

	this->cutOff = glm::cos(glm::radians(cutOff));
	this->outerCutOff = glm::cos(glm::radians(outerCutOff));
}

void Light::useLight(Shader* shader, int i)
{
	switch (type)
	{
	case LightType::SUN:
		shader->setVec3(("sunLights[" + std::to_string(i) + "].direction").c_str(), direction);
		shader->setVec3(("sunLights[" + std::to_string(i) + "].ambient").c_str(), ambient);
		shader->setVec3(("sunLights[" + std::to_string(i) + "].diffuse").c_str(), diffuse);
		shader->setVec3(("sunLights[" + std::to_string(i) + "].specular").c_str(), specular);
		break;
	case LightType::POINT:
		shader->setVec3(("lights[" + std::to_string(i) + "].position").c_str(), position);
		shader->setVec3(("lights[" + std::to_string(i) + "].ambient").c_str(), ambient);
		shader->setVec3(("lights[" + std::to_string(i) + "].diffuse").c_str(), diffuse);
		shader->setVec3(("lights[" + std::to_string(i) + "].specular").c_str(), specular);
		shader->setFloat(("lights[" + std::to_string(i) + "].constant").c_str(), constant);
		shader->setFloat(("lights[" + std::to_string(i) + "].linear").c_str(), linear);
		shader->setFloat(("lights[" + std::to_string(i) + "].quadratic").c_str(), quadratic);
		break;
	case LightType::SPOT:
		shader->setVec3(("spotLights[" + std::to_string(i) + "].direction").c_str(), direction);
		shader->setVec3(("spotLights[" + std::to_string(i) + "].position").c_str(), position);
		shader->setVec3(("spotLights[" + std::to_string(i) + "].ambient").c_str(), ambient);
		shader->setVec3(("spotLights[" + std::to_string(i) + "].diffuse").c_str(), diffuse);
		shader->setVec3(("spotLights[" + std::to_string(i) + "].specular").c_str(), specular);
		shader->setFloat(("spotLights[" + std::to_string(i) + "].constant").c_str(), constant);
		shader->setFloat(("spotLights[" + std::to_string(i) + "].linear").c_str(), linear);
		shader->setFloat(("spotLights[" + std::to_string(i) + "].quadratic").c_str(), quadratic);
		shader->setFloat(("spotLights[" + std::to_string(i) + "].cutOff").c_str(), cutOff);
		shader->setFloat(("spotLights[" + std::to_string(i) + "].outerCutOff").c_str(), outerCutOff);
		break;
	}
}

void Light::setPosition(glm::vec3 position)
{
	this->position = position;
}

void Light::setDirection(glm::vec3 direction)
{
	this->direction = direction;
}

void Light::setColor(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
}

void Light::setStrength(float constant, float linear, float quadratic)
{
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}

void Light::setCutOff(float cutOff, float outerCutOff)
{
	this->cutOff = cutOff;
	this->outerCutOff = outerCutOff;
}