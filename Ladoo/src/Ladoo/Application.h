#pragma once

#include "Core.h"

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


