#pragma once

#include "libchapter.h"
#include "MeshP3NT2.h"
#include "Cube.h"

class CBlock
	:public ISceneObject
{
public:
	CBlock() = default;
	CBlock(const glm::vec3 & center, const float size) { (void)center; (void)size; };
	virtual ~CBlock() = default;

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() const = 0;

private:
};

class CBlaBlock // TODO: rename
	:public CBlock
{
public:
	CBlaBlock(const glm::vec3 & center, const float size);
	~CBlaBlock() = default;

	void Update(float dt) override;
	void Draw() const override;

private:
	CCube m_cube;
	CTexture2DAtlas m_atlas;
	std::pair<glm::vec3, glm::vec3> m_position;
};
