#pragma once

#include "Ladoo/Core.h"
#include "Ladoo/Events/Event.h"

namespace Ladoo {

	class LADOO_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};
	
	// To be defined in client
	Application* CreateApplication();

}


