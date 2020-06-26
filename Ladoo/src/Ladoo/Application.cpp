#include "Application.h"

#include "Ladoo/Events/ApplicationEvent.h"
#include "Ladoo/Log.h"

namespace Ladoo {

	Application::Application() 
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280,720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			LD_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			LD_TRACE(e);
		}
		

		while (true);
	}
}