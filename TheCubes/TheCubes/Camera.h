#pragma once

#include <boost/noncopyable.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>


class CCamera 
	:private boost::noncopyable
{
public:
    explicit CCamera(glm::vec3 viewDirection, glm::vec3 eye, glm::vec3 up);

    void Update(float deltaSec);
	void OnScale(const int & zoom);

	void SetPosition(const glm::vec3 & position);
	glm::vec3 GetPosition() const;

	glm::vec3 GetViewDirection() const;

	glm::mat4 GetViewTransform() const;

	void SetRotationFlag(bool flag);
	bool GetRotationFlag() const;

	void Rotate(const glm::vec2);

	void MoveFrontal(const float speed);
	void MoveHorizontal(const float speed);
	void MoveVertical(const float speed);

	void StrafeLeft();
	void StrafeRight();

private:
	bool m_doesRotate = false;
	glm::vec2 m_angle;

	glm::vec3 m_eye;
	glm::vec3 m_viewDirection;
	glm::vec3 m_strafeDirection;
	const glm::vec3 m_up;

	glm::vec2 oldMousePosition;
};
