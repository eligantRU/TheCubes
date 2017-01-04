#pragma once

#include "libchapter.h"
#include "Decorators.h"
#include "Camera.h"
#include "KeyboardHandler.h"
#include "CubesSystem.h"

class CWindowClient : public CAbstractWindowClient
{
public:
	CWindowClient(CWindow & window);

protected:
	void OnUpdateWindow(const float dt) override;
	void OnKeyDown(const SDL_KeyboardEvent &) override;
	void OnKeyUp(const SDL_KeyboardEvent &) override;

	void OnDragBegin(const glm::vec2 & pos);
	void OnDragEnd(const glm::vec2 & pos);
	void OnDragMotion(const glm::vec2 & pos);

private:
	void CheckOpenGLVersion();
	void SetupView(const glm::ivec2 & size);

	void DispatchKeyboardEvent();

	CPhongModelMaterial m_material;
	CPositionLightSource m_sunlight;
	CCamera m_camera;
	glm::vec2 m_dragPosition;
	bool m_lineMode = false;
	
	CShaderProgram m_program;

	CCubesSystem m_system;

	CKeyboardHandler m_keyboardHandler;
};
