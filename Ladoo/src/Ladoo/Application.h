#pragma once

#include "Core.h"
#include "Ladoo/Events/Event.h"
#include "Ladoo/Events/ApplicationEvent.h"
#include "Window.h"
#include "Ladoo/LayerStack.h"
#include "Ladoo/ImGui/ImGuiLayer.h"


namespace Ladoo {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};
	
	// To be defined in client
	Application* CreateApplication();

}


