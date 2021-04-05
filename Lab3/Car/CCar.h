#pragma once
#include <string>

class CCar
{
public:
	CCar();

	void TurnOnEngine();
	void TurnOffEngine();
	void SetGear(int gear);
	void SetSpeed(int speed);
	bool IsTurnedOn() const;
	// Переделать на ENUM
	std::string GetDirection() const;
	int GetSpeed() const;
	int GetGear() const;

private:
	int m_gear;
	int m_speed;
	bool m_isEngineTurnedOn;

	void AssertValidGear(int gear) const;
	void AssertValidSpeed(int speed) const;
};
