#include "stdafx.h"

#include "CubesSystem.h"

namespace
{

static const float CUBE_SIZE = 2.f;

}

CCubesSystem::CCubesSystem()
{
	for (size_t i = 0; i <= 728; ++i)
	{
		m_system.push_back(std::vector<std::vector<bool>>(728));
	}
	for (auto & row : m_system)
	{
		row.push_back(std::vector<bool>(728));
	}
	for (auto & row : m_system)
	{
		for (auto & column : row)
		{
			for (size_t i = 0; i <= 728; ++i)
			{
				column.push_back(false);
			}
		}
	}
}

void CCubesSystem::Update(const float dt)
{
	/*for (auto & block : m_blocks)
	{
		block->Update(dt);
	}*/
}

void CCubesSystem::Draw() const
{
	/*for (const auto & block: m_blocks)
	{
		block->Draw();
	}*/
}

void CCubesSystem::Advance()
{
	/*auto block = std::make_unique<CBlaBlock>(glm::vec3(0, 0, 0), CUBE_SIZE);
	m_blocks.push_back(std::move(block));*/
}
