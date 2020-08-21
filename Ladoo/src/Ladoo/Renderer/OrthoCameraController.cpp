#include "ldpch.h"
#include "OrthoCameraController.h"

#include "Ladoo/Base/Input.h"
#include "Ladoo/Base/KeyCodes.h"

namespace Ladoo {

	OrthoCameraController::OrthoCameraController(float aspectRatio, bool rotation)
		: c_AspectRatio(aspectRatio), camera(-c_AspectRatio * c_ZoomLevel, c_AspectRatio * c_ZoomLevel, -c_ZoomLevel, c_ZoomLevel), c_Rotation(rotation)
	{
	}
	
	void OrthoCameraController::OnUpdate(TimeStep timeStep)
	{
		if (Input::IsKeyPressed(LD_KEY_A))
		{
			c_CameraPosition.x -= c_CameraTranslationSpeed * timeStep;
		}
		else if (Input::IsKeyPressed(LD_KEY_D))
		{
			c_CameraPosition.x += c_CameraTranslationSpeed * timeStep;
		}

		if (Input::IsKeyPressed(LD_KEY_W))
		{
			c_CameraPosition.y += c_CameraTranslationSpeed * timeStep;
		}
		else if (Input::IsKeyPressed(LD_KEY_S))
		{
			c_CameraPosition.y -= c_CameraTranslationSpeed * timeStep;
		}

		if (c_Rotation)
		{
			if (Input::IsKeyPressed(LD_KEY_R))
			{
				c_CameraRotation += c_CameraRotationSpeed * timeStep;
			}
			if (Input::IsKeyPressed(LD_KEY_F))
			{
				c_CameraRotation -= c_CameraRotationSpeed * timeStep;
			}
			camera.SetRotation(c_CameraRotation);
		}
		
		camera.SetPostion(c_CameraPosition);

		c_CameraTranslationSpeed = c_ZoomLevel;
	}

	void OrthoCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispacther(e);
		dispacther.Dispatch<MouseScrolledEvent>(LD_BIND_EVENT_FN(OrthoCameraController::OnMouseScrolled));
		dispacther.Dispatch<WindowResizeEvent>(LD_BIND_EVENT_FN(OrthoCameraController::OnWindowResized));
	}

	bool OrthoCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		c_ZoomLevel -= e.GetYOffset() * 0.25f;
		c_ZoomLevel = std::max(c_ZoomLevel, 0.25f);
		camera.SetProjection(-c_AspectRatio * c_ZoomLevel, c_AspectRatio * c_ZoomLevel, -c_ZoomLevel, c_ZoomLevel);
		return false;
	}

	bool OrthoCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		c_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		camera.SetProjection(-c_AspectRatio * c_ZoomLevel, c_AspectRatio * c_ZoomLevel, -c_ZoomLevel, c_ZoomLevel);
		return false;
	}
}