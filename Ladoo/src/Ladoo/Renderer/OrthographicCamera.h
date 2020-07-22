#pragma once

#include <glm/glm.hpp>

namespace Ladoo {

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return c_Position; }
		void SetPostion(const glm::vec3& postion) { c_Position = postion;  RecalculateViewMatrix(); }

		float GetRotation() const { return c_Rotation; }
		void SetRotation(float rotation) { c_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return c_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return c_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return c_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 c_ProjectionMatrix;
		glm::mat4 c_ViewMatrix;
		glm::mat4 c_ViewProjectionMatrix;

		glm::vec3 c_Position = {0.0f, 0.0f, 0.0f};
		float c_Rotation = 0.0f;
	};

}

