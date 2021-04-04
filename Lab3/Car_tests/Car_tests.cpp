#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include "../Car/CCar.h"

SCENARIO("Test car creation")
{
	CCar car;
	int gear = car.GetGear();
	int speed = car.GetSpeed();
	bool isEngineTurnedOn = car.IsTurnedOn();
	REQUIRE(!isEngineTurnedOn);
	REQUIRE(gear == 0);
	REQUIRE(speed == 0);
}

SCENARIO("Test turn on engine after car creation")
{
	CCar car;
	car.TurnOnEngine();
	int gear = car.GetGear();
	int speed = car.GetSpeed();
	bool isEngineTurnedOn = car.IsTurnedOn();
	REQUIRE(isEngineTurnedOn);
	REQUIRE(gear == 0);
	REQUIRE(speed == 0);
}

SCENARIO("Test turn off engine with 0 speed")
{
	CCar car;
	car.TurnOnEngine();
	REQUIRE_NOTHROW(car.TurnOffEngine());
	int gear = car.GetGear();
	int speed = car.GetSpeed();
	bool isEngineTurnedOn = car.IsTurnedOn();
	REQUIRE(!isEngineTurnedOn);
	REQUIRE(gear == 0);
	REQUIRE(speed == 0);
}

SCENARIO("Test turn on first with 0 speed and 0 gear")
{
	CCar car;
	car.TurnOnEngine();
	REQUIRE_NOTHROW(car.SetGear(1));
	int gear = car.GetGear();
	int speed = car.GetSpeed();
	bool isEngineTurnedOn = car.IsTurnedOn();
	REQUIRE(isEngineTurnedOn);
	REQUIRE(gear == 1);
	REQUIRE(speed == 0);
}

SCENARIO("Test turn on -1 gear with 0 speed and 0 gear")
{
	CCar car;
	car.TurnOnEngine();
	REQUIRE_NOTHROW(car.SetGear(-1));
	int gear = car.GetGear();
	int speed = car.GetSpeed();
	bool isEngineTurnedOn = car.IsTurnedOn();
	REQUIRE(isEngineTurnedOn);
	REQUIRE(gear == -1);
	REQUIRE(speed == 0);
}

SCENARIO("Test turn on 1 gear with 0 speed and -1 gear")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);
	std::string message;
	REQUIRE_NOTHROW(car.SetGear(-1));
	int gear = car.GetGear();
	int speed = car.GetSpeed();
	bool isEngineTurnedOn = car.IsTurnedOn();
	REQUIRE(isEngineTurnedOn);
	REQUIRE(gear == -1);
	REQUIRE(speed == 0);
}

SCENARIO("Test turn on 1 gear with 10 speed and -1 gear")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);
	std::string message;
	car.SetSpeed(10);
	REQUIRE_THROWS(car.SetGear(-1));
	int gear = car.GetGear();
	int speed = car.GetSpeed();
	bool isEngineTurnedOn = car.IsTurnedOn();
	REQUIRE(isEngineTurnedOn);
	REQUIRE(gear == 1);
	REQUIRE(speed == 10);
}

SCENARIO("Test turn on -1 gear with -10 speed and 0 gear")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(-1);
	std::string message;
	car.SetSpeed(-10);
	car.SetGear(0);
	REQUIRE_THROWS(car.SetGear(-1));
	int gear = car.GetGear();
	int speed = car.GetSpeed();
	bool isEngineTurnedOn = car.IsTurnedOn();
	REQUIRE(isEngineTurnedOn);
	REQUIRE(gear == 0);
	REQUIRE(speed == 10);
}

SCENARIO("Test turn on 2 gear with 20 speed and 1 gear")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);
	std::string message;
	car.SetSpeed(20);
	REQUIRE_NOTHROW(car.SetGear(2));
	int gear = car.GetGear();
	int speed = car.GetSpeed();
	bool isEngineTurnedOn = car.IsTurnedOn();
	REQUIRE(isEngineTurnedOn);
	REQUIRE(gear == 2);
	REQUIRE(speed == 20);
}

SCENARIO("Test turn on 3 gear with 30 speed and 1 gear")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);
	std::string message;
	car.SetSpeed(30);
	REQUIRE_NOTHROW(car.SetGear(3));
	int gear = car.GetGear();
	int speed = car.GetSpeed();
	bool isEngineTurnedOn = car.IsTurnedOn();
	REQUIRE(isEngineTurnedOn);
	REQUIRE(gear == 3);
	REQUIRE(speed == 30);
}

SCENARIO("Test turn on 3 gear with 20 speed and 1 gear")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);
	std::string message;
	car.SetSpeed(20);
	REQUIRE_THROWS(car.SetGear(3));
	int gear = car.GetGear();
	int speed = car.GetSpeed();
	bool isEngineTurnedOn = car.IsTurnedOn();
	REQUIRE(isEngineTurnedOn);
	REQUIRE(gear == 1);
	REQUIRE(speed == 20);
}

SCENARIO("Test turn on 4 gear with 40 speed and 2 gear")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);
	std::string message;
	car.SetSpeed(30);
	car.SetGear(2);
	car.SetSpeed(40);
	REQUIRE_NOTHROW(car.SetGear(4));
	int gear = car.GetGear();
	int speed = car.GetSpeed();
	bool isEngineTurnedOn = car.IsTurnedOn();
	REQUIRE(isEngineTurnedOn);
	REQUIRE(gear == 4);
	REQUIRE(speed == 40);
}

SCENARIO("Test turn on 5 gear with 90 speed and 4 gear")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);
	std::string message;
	car.SetSpeed(30);
	car.SetGear(2);
	car.SetSpeed(40);
	car.SetGear(4);
	car.SetSpeed(90);
	REQUIRE_NOTHROW(car.SetGear(5));
	int gear = car.GetGear();
	int speed = car.GetSpeed();
	bool isEngineTurnedOn = car.IsTurnedOn();
	REQUIRE(isEngineTurnedOn);
	REQUIRE(gear == 5);
	REQUIRE(speed == 90);
}

SCENARIO("Test turn engine off on gear 5 with speed 90")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);
	std::string message;
	car.SetSpeed(30);
	car.SetGear(2);
	car.SetSpeed(40);
	car.SetGear(4);
	car.SetSpeed(90);
	car.SetGear(5);
	REQUIRE_THROWS(car.TurnOffEngine());
	int gear = car.GetGear();
	int speed = car.GetSpeed();
	bool isEngineTurnedOn = car.IsTurnedOn();
	REQUIRE(isEngineTurnedOn);
	REQUIRE(gear == 5);
	REQUIRE(speed == 90);
}

SCENARIO("Test turn engine off on gear 0 with speed 90")
{
	CCar car;
	car.TurnOnEngine();
	car.SetGear(1);
	std::string message;
	car.SetSpeed(30);
	car.SetGear(2);
	car.SetSpeed(40);
	car.SetGear(4);
	car.SetSpeed(90);
	car.SetGear(0);
	REQUIRE_THROWS(car.TurnOffEngine());
	int gear = car.GetGear();
	int speed = car.GetSpeed();
	bool isEngineTurnedOn = car.IsTurnedOn();
	REQUIRE(isEngineTurnedOn);
	REQUIRE(gear == 0);
	REQUIRE(speed == 90);
}



