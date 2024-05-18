#pragma once

#include "ECS/Entity.h"
#include "Model.h"

class Backpack : public Shue::Entity
{
public:
	Backpack(const std::string& name, Shue::Model* model, Shue::Shader& shader);
	Backpack(const std::string& name, const std::string& modelPath, Shue::Shader& shader);

	void Update() override;
};