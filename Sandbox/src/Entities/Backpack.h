#pragma once

#include "ECS/Entity.h"
#include "Model.h"

class Backpack : public Shue::Entity
{
public:
	Backpack(Shue::Model* model, Shue::Shader& shader);
	Backpack(const std::string& modelPath, Shue::Shader& shader);

	void Update() override;
};