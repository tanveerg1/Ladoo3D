#pragma once

namespace Ladoo {

	class TimeStep
	{
	public:
		TimeStep(float time = 0.0f) 
			: b_Time(time)
		{
		}

		operator float() const { return b_Time; }

		float GetSeconds() const { return b_Time; }
		float GetMilliseconds() const { return b_Time * 1000.0f; }
	private:
		float b_Time;
	};
}