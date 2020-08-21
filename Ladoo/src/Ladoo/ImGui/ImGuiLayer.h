#pragma once

#include "Ladoo/Base/Layer.h"
#include "Ladoo/Events/MouseEvent.h"
#include "Ladoo/Events/KeyEvent.h"
#include "Ladoo/Events/ApplicationEvent.h"

namespace Ladoo {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}