#include <Ladoo.h>

class ExampleLayer : public Ladoo::Layer 
{
public:
	ExampleLayer() : Layer("Example")
	{
	}

	void OnUpdate() override
	{
		LD_INFO("ExampleLayer::Update");
	}

	void OnEvent(Ladoo::Event& event) override
	{
		LD_TRACE("{0}", event);
	}
};

class Sandbox : public Ladoo::Application
{
public: 
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Ladoo::Application* Ladoo::CreateApplication()
{
	return new Sandbox();
}