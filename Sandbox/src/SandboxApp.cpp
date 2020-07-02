#include <Ladoo.h>

class ExampleLayer : public Ladoo::Layer 
{
public:
	ExampleLayer() : Layer("Example")
	{
	}

	void OnUpdate() override
	{
		//LD_INFO("ExampleLayer::Update");

		if (Ladoo::Input::IsKeyPressed(LD_KEY_TAB))
		{
			LD_INFO("Tab key is pressed");
		}
	}

	void OnEvent(Ladoo::Event& event) override
	{
		//LD_TRACE("{0}", event);
		if (event.GetEventType() == Ladoo::EventType::KeyPressed)
		{
			Ladoo::KeyPressedEvent& e = (Ladoo::KeyPressedEvent&)event;
			LD_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Ladoo::Application
{
public: 
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Ladoo::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Ladoo::Application* Ladoo::CreateApplication()
{
	return new Sandbox();
}