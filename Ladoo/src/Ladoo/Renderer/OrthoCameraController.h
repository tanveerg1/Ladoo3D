#pragma once

#include "OrthographicCamera.h"
#include "Ladoo/Base/TimeStep.h"

#include "Ladoo/Events/ApplicationEvent.h"
#include "Ladoo/Events/MouseEvent.h"

namespace Ladoo {

	class OrthoCameraController
	{
	public:
		OrthoCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(TimeStep timeStep);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return camera; }
		const OrthographicCamera& GetCamera() const { return camera; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float c_AspectRatio;
		float c_ZoomLevel = 1.0f;
		OrthographicCamera camera;
		bool c_Rotation;

		glm::vec3 c_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float c_CameraRotation = 0.0f;
		float c_CameraTranslationSpeed = 5.0f, c_CameraRotationSpeed = 180.0f;
	};
}