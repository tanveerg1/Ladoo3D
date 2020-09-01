#pragma once

#include "Core.h"
#include "Ladoo/Events/Event.h"
#include "Ladoo/Events/ApplicationEvent.h"
#include "Window.h"
#include "Ladoo/Base/LayerStack.h"
#include "Ladoo/ImGui/ImGuiLayer.h"
#include "Ladoo/Base/TimeStep.h"

int main(int argc, char** argv);

namespace Ladoo {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
		friend int::main(int argc, char** argv);
	};
	
	// To be defined in client
	Application* CreateApplication();

}


