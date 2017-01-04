#include "stdafx.h"

#include "Window.h"
#include "IdentitySphere.h"

namespace
{

const glm::vec3 INITIAL_VIEW_DIRECTION = { -1, 0, 0 };
const glm::vec3 INITIAL_EYE_POSITION = { 8, 2, 0 };
const glm::vec3 INITIAL_UP_DIRECTION = { 0, 0, 1 };

const glm::vec4 BLACK_RGBA = { 0, 0, 0, 1 };
const glm::vec4 WHITE_RGBA = { 1, 1, 1, 1 };
const glm::vec4 GRAY_RGBA = { 0.f, 0.0f, 0.f, 1.f };

const float AMBIENT_SCALE = 0.5f;
const float MATERIAL_SHININESS = 50.f;
const glm::vec3 SUNLIGHT_DIRECTION = glm::normalize(glm::vec3(-1, -1, -1));

void SetupOpenGLState()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glDepthMask(GL_TRUE);

	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);

	glEnable(GL_TEXTURE_2D);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}

void SetupLineMode(const bool flag)
{
	if (flag)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void SetupModelViewProjection(const glm::mat4 & modelView, const glm::mat4 & projection)
{
	glLoadMatrixf(glm::value_ptr(modelView));
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(projection));
	glMatrixMode(GL_MODELVIEW);
}

}

CWindowClient::CWindowClient(CWindow & window)
	:CAbstractWindowClient(window)
	,m_sunlight(GL_LIGHT0)
	,m_camera(INITIAL_VIEW_DIRECTION, INITIAL_EYE_POSITION, INITIAL_UP_DIRECTION)
{
	window.SetBackgroundColor(BLACK_RGBA);
	CheckOpenGLVersion();
	SetupOpenGLState();

	m_sunlight.SetDirection(SUNLIGHT_DIRECTION);
	m_sunlight.SetDiffuse(WHITE_RGBA);
	m_sunlight.SetAmbient(AMBIENT_SCALE * WHITE_RGBA);
	m_sunlight.SetSpecular(WHITE_RGBA);
	m_sunlight.SetDirection(INITIAL_VIEW_DIRECTION);

	m_material.SetShininess(MATERIAL_SHININESS);
	m_material.SetSpecular(WHITE_RGBA);
	m_material.SetDiffuse(GRAY_RGBA);
	m_material.SetAmbient(AMBIENT_SCALE * GRAY_RGBA);

	m_camera.SetRotationFlag(true);
}

void CWindowClient::OnUpdateWindow(float dt)
{
	m_camera.Update(dt);
	SetupView(GetWindow().GetWindowSize());
	
	m_sunlight.Setup();
	m_material.Setup();

	m_system.Update(dt);
	m_system.Draw();
}

void CWindowClient::OnDragBegin(const glm::vec2 & pos)
{
	m_dragPosition = pos;
}

void CWindowClient::OnDragMotion(const glm::vec2 & pos)
{
	if (m_camera.GetRotationFlag())
	{
		auto lastPos = m_dragPosition;
		if (lastPos.x && lastPos.y)
		{
			m_camera.Rotate(pos - lastPos);
		}
		m_dragPosition = pos;
	}
}

void CWindowClient::OnDragEnd(const glm::vec2 & pos)
{
	(void)&pos;
}

void CWindowClient::OnKeyDown(const SDL_KeyboardEvent & event)
{
	m_keyboardHandler.OnKeyDown(event.keysym.sym);
}

void CWindowClient::OnKeyUp(const SDL_KeyboardEvent & event)
{
	m_keyboardHandler.OnKeyUp(event.keysym.sym);
	if (event.keysym.sym == SDLK_TAB)
	{
		m_lineMode = !m_lineMode;
	}
	SetupLineMode(m_lineMode);

	if (event.keysym.sym == SDLK_SPACE)
	{
		m_system.Advance();
	}

	if (event.keysym.sym == SDLK_ESCAPE)
	{
		std::exit(0);
	}
}

void CWindowClient::CheckOpenGLVersion()
{
	if (!GLEW_VERSION_2_0)
	{
		throw std::runtime_error("Sorry, but OpenGL 3.2 is not available");
	}
}

void CWindowClient::SetupView(const glm::ivec2 & size)
{
	glViewport(0, 0, size.x, size.y);
	const glm::mat4 mv = m_camera.GetViewTransform();
	glLoadMatrixf(glm::value_ptr(mv));

	const float fieldOfView = glm::radians(179.f);
	const float aspect = float(size.x) / float(size.y);
	const float zNear = 0.01f;
	const float zFar = 100.f;
	const glm::mat4 proj = glm::perspective(fieldOfView, aspect, zNear, zFar);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(proj));
	glMatrixMode(GL_MODELVIEW);
}
