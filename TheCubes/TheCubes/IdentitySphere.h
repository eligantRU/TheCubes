#pragma once

#include "MeshP3NT2.h"
#include "libchapter.h"

class CIdentitySphere final 
	:public ISceneObject
{
public:
	CIdentitySphere(unsigned slices, unsigned stacks, glm::vec3 & position);

	void Update(float) final {}
	void Draw() const final;

private:
	void Tesselate(unsigned slices, unsigned stacks);

	SMeshP3NT2 m_mesh;
};
