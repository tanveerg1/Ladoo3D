#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Ladoo/Events/ApplicationEvent.h"
#include "Window.h"
#include "Ladoo/LayerStack.h"


namespace Ladoo {

	class LADOO_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};
	
	// To be defined in client
	Application* CreateApplication();

}


