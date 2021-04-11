#include "CCar.h"
#include "Exceptions.h"
#include <map>
#include <vector>
#include <string>

CCar::CCar()
	:m_speed(0),
	m_gear(0),
	m_isEngineTurnedOn(false)
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
		throw InvalidEngineOffStateException("Can not turn engine of with speed: '" + std::to_string(m_speed) + "' and gear: '" + std::to_string(m_gear) + "'");
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

bool CCar::IsTurnedOn() const
{
	return m_isEngineTurnedOn;
}

CCar::Directions CCar::GetDirection() const
{
	if (m_speed > 0)
		return FORWARD;
	if (m_speed == 0)
		return BACKWARD;
	return STAY;
}

int CCar::GetSpeed() const
{
	if (m_speed < 0)
		return m_speed * -1;
	return m_speed;
}

int CCar::GetGear() const
{
	return m_gear;
}

void CCar::AssertValidGear(int gear) const
{
	if (gear < -1 || gear > 5)
	{
		throw InvalidGearException("Invalid gear: '" + std::to_string(gear) + "'");
	}
	if (!m_isEngineTurnedOn)
	{
		throw InvalidGearException("Can not set gear with engine turned off");
	}
	if ((m_speed < carGearSpeedMap.at(gear).minSpeed || m_speed > carGearSpeedMap.at(gear).maxSpeed) || (gear == -1 && m_speed != 0))
	{
		throw InvalidGearException("Invalid gear: '" + std::to_string(gear) + "' for speed: '" + std::to_string(m_speed) + "'");
	}
}

void CCar::AssertValidSpeed(int speed) const 
{
	int minSpeed = carGearSpeedMap.at(m_gear).minSpeed;
	int maxSpeed = carGearSpeedMap.at(m_gear).maxSpeed;
	if (!m_isEngineTurnedOn)
	{
		throw InvalidSpeedException("Can not set speed with engine turned off");
	}
	if (m_gear == 0 && (abs(speed) > abs(m_speed)))
	{
		throw InvalidSpeedException("Can not speed up on gear: '0'");
	}
	if (speed < minSpeed || speed > maxSpeed)
	{
		throw InvalidSpeedException("Invalid speed: '" + std::to_string(speed) + "' for gear: '" + std::to_string(m_gear) + "'");
	}
}

