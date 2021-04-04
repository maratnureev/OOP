#include "CCar.h"
#include <map>
#include <vector>
#include <string>

CCar::CCar()
	:m_speed(0),
	m_gear(0),
	m_isEngineTurnedOn(false)
{
}

CCar::~CCar()
{
}

struct SpeedLimit {
	int minSpeed;
	int maxSpeed;
};

static const std::map<int, SpeedLimit> carGearSpeedMap = {
	{-1, {-20, 0}},
	{0, {-20, 150}},
	{1, {0, 30}},
	{2, {20, 50}},
	{3, {30, 60}},
	{4, {40, 90}},
	{5, {50, 150}},
};

void CCar::TurnOnEngine()
{
	m_isEngineTurnedOn = true;
}

void CCar::TurnOffEngine()
{
	if (m_gear != 0 || m_speed != 0 )
	{
		throw "Can not turn engine of with speed: '" + std::to_string(m_speed) + "' and gear: '" + std::to_string(m_gear) + "'";
	}
	m_isEngineTurnedOn = false;
}
void CCar::SetGear(int gear)
{
	AssertValidGear(gear);
	m_gear = gear;
}

void CCar::SetSpeed(int speed)
{
	if (m_gear == -1 || m_speed < 0)
		speed = speed * -1;
	AssertValidSpeed(speed);
	m_speed = speed;
}

bool CCar::IsTurnedOn()
{
	return m_isEngineTurnedOn;
}

std::string CCar::GetDirection()
{
	if (m_speed > 0)
		return "forward";
	if (m_speed == 0)
		return "stay";
	return "backward";
}

int CCar::GetSpeed()
{
	if (m_speed < 0)
		return m_speed * -1;
	return m_speed;
}

int CCar::GetGear()
{
	return m_gear;
}

void CCar::AssertValidGear(int gear)
{
	if (gear < -1 || gear > 5)
	{
		std::string message = "Invalid gear: '" + std::to_string(gear) + "'";
		throw message;
	}
	if (!m_isEngineTurnedOn)
	{
		std::string message = "Can not set gear with engine turned off";
		throw message;
	}
	if ((m_speed < carGearSpeedMap.at(gear).minSpeed || m_speed > carGearSpeedMap.at(gear).maxSpeed) || (gear == -1 && m_speed != 0))
	{
		std::string message = "Invalid gear: '" + std::to_string(gear) + "' for speed: '" + std::to_string(m_speed) + "'";
		throw message;
	}
}

void CCar::AssertValidSpeed(int speed)
{
	int minSpeed = carGearSpeedMap.at(m_gear).minSpeed;
	int maxSpeed = carGearSpeedMap.at(m_gear).maxSpeed;
	if (!m_isEngineTurnedOn)
	{
		std::string message = "Can not set gear with engine turned off";
		throw message;
	}
	if (m_gear == 0 && (abs(speed) > abs(m_speed)))
	{
		std::string message = "Can not speed up on gear: '0'";
		throw message;
	}
	if (speed < minSpeed || speed > maxSpeed)
	{
		std::string message = "Invalid speed: '" + std::to_string(speed) + "' for gear: '" + std::to_string(m_gear) + "'";
		throw message;
	}
}

