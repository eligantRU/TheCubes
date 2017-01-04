#pragma once

#include "Blocks.h"

class CCubesSystem
{
public:
	CCubesSystem() = default;
	~CCubesSystem() = default;

	void Advance();
	void Update(const float dt);
	void Draw() const;

private:
	std::vector<std::unique_ptr<CBlaBlock>> m_blocks;
};
