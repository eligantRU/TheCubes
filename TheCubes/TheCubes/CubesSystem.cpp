#include "stdafx.h"

#include "CubesSystem.h"

namespace
{

static const float CUBE_SIZE = 2.f;

}

void CCubesSystem::Update(const float dt)
{
	for (auto & block : m_blocks)
	{
		block->Update(dt);
	}
}

void CCubesSystem::Draw() const
{
	for (const auto & block: m_blocks)
	{
		block->Draw();
	}
}

void CCubesSystem::Advance()
{
	auto block = std::make_unique<CBlaBlock>(glm::vec3(0, 0, 0), CUBE_SIZE);
	m_blocks.push_back(std::move(block));
}
