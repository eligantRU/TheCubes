#include "stdafx.h"

#include "Blocks.h"

namespace
{

const char COBBLESTONE_TEXTURE_ATLAS[] = "res/cobblestone_block/cobblestone_block.plist";
const std::pair<CubeFace, const char *> COBBLESTONE_FRAME_MAPPING[] = {
	{ CubeFace::Front, "cobblestone_block_front.png" },
	{ CubeFace::Back, "cobblestone_block_back.png" },
	{ CubeFace::Top, "cobblestone_block_top.png" },
	{ CubeFace::Bottom, "cobblestone_block_bottom.png" },
	{ CubeFace::Left, "cobblestone_block_left.png" },
	{ CubeFace::Right, "cobblestone_block_right.png" }
};

CTexture2DLoader MakeTextureLoader()
{
	CTexture2DLoader loader;
	loader.SetWrapMode(TextureWrapMode::CLAMP_TO_EDGE);
	return loader;
}

}

CBlaBlock::CBlaBlock(const glm::vec3 & center, const float size)
	:m_atlas(CFilesystemUtils::GetResourceAbspath(COBBLESTONE_TEXTURE_ATLAS), MakeTextureLoader())
	,m_cube(center, size)
	,m_position(glm::vec3(center.x - size, center.y - size, center.z - size), glm::vec3(center.x + size, center.y + size, center.z + size))
{
	for (const auto &pair : COBBLESTONE_FRAME_MAPPING)
	{
		auto texRect = m_atlas.GetFrameRect(pair.second);
		m_cube.SetFaceTextureRect(pair.first, texRect);
	}
}

void CBlaBlock::Update(float dt)
{
	m_cube.Update(dt);
}

void CBlaBlock::Draw() const
{
	m_atlas.GetTexture().DoWhileBinded([this] {
		m_cube.Draw();
	});
}
