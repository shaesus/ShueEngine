#pragma once

#include "ECS/Entity.h"
#include "Model.h"

class Container : public Shue::Entity
{
public:
	Container(const std::string& name, Shue::Model* model, Shue::Shader& shader);
	Container(const std::string& name, const std::string& modelPath, Shue::Shader& shader);

	void Update() override;
};