#pragma once
#include <string>

class CCar
{
public:
	CCar();
	~CCar();

	void TurnOnEngine();
	void TurnOffEngine();
	void SetGear(int gear);
	void SetSpeed(int speed);
	bool IsTurnedOn();
	std::string GetDirection();
	int GetSpeed();
	int GetGear();

private:
	int m_gear;
	int m_speed;
	bool m_isEngineTurnedOn;
	std::string m_direction;

	void AssertValidGear(int gear);
	void AssertValidSpeed(int speed);
};
