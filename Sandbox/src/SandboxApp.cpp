#include <Ladoo.h>

class Sandbox : public Ladoo::Application
{
public: 
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Ladoo::Application* Ladoo::CreateApplication()
{
	return new Sandbox();
}