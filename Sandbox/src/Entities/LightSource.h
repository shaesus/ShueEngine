#pragma once

#include "ECS/Entity.h"
#include "Model.h"

class LightSource : public Shue::Entity
{
public:
	LightSource(const std::string& name, Shue::Model* model, Shue::Shader& shader);
	LightSource(const std::string& name, const std::string& modelPath, Shue::Shader& shader);

	void Update() override;
};