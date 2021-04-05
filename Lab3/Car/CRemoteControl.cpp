#include "CRemoteControl.h"
#include "CCar.h"
#include "Exceptions.h"
#include <string>
#include <iostream>
#include <sstream>


using namespace std;
using namespace std::placeholders;

CRemoteControl::CRemoteControl(CCar& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "EngineOn", [this](istream& strm) {
			   return EngineOn(strm);
		   } },
		  { "EngineOff", bind(&CRemoteControl::EngineOff, this, std::placeholders::_1) },
		  { "Info", bind(&CRemoteControl::Info, this, _1) },
		  { "SetSpeed", bind(&CRemoteControl::SetSpeed, this, _1) },
		  { "SetGear", bind(&CRemoteControl::SetGear, this, _1) },
		})
{
}

		   bool CRemoteControl::HandleCommand()
		   {
			   string commandLine;
			   getline(m_input, commandLine);
			   istringstream strm(commandLine);

			   string action;
			   strm >> action;

			   auto it = m_actionMap.find(action);
			   if (it != m_actionMap.end())
			   {
				   return it->second(strm);
			   }

			   return false;
		   }

		   bool CRemoteControl::EngineOn(std::istream&)
		   {
			   m_car.TurnOnEngine();
			   m_output << "Car's engine is turned on" << endl;
			   return true;
		   }

		   bool CRemoteControl::EngineOff(std::istream&)
		   {
			   try
			   {
				   m_car.TurnOffEngine();
				   m_output << "Car's engine is turned off" << endl;
			   }
			   catch (const InvalidEngineOffStateException& e)
			   {
				   m_output << e.GetMessage() << endl;
			   }
			   return true;
		   }

		   bool CRemoteControl::Info(std::istream&)
		   {
			   int gear = m_car.GetGear();
			   int speed = m_car.GetSpeed();
			   bool isTurnedOn = m_car.IsTurnedOn();
			   std::string direction = m_car.GetDirection();
			   
			   string info = (isTurnedOn)
				   ? ("Car's engine is turned on\nGear is: " + to_string(gear) + "\nSpeed is: " + to_string(speed) + "\nDirection is: " + direction + "\n" )
				   : "Car's engine is turned off\n";
			   m_output << info;
			   
			   return true;
		   }

		   bool CRemoteControl::SetSpeed(std::istream& args)
		   {
			   int speed;
			   args >> speed;
			   try
			   {
				   m_car.SetSpeed(speed);
				   m_output << "Speed set to " + to_string(speed) << endl;
			   }
			   catch (const InvalidSpeedException& e)
			   {
				   cout << e.GetMessage() << endl;
			   }
			   return true;
		   }

		   bool CRemoteControl::SetGear(std::istream& args)
		   {
			   int gear;
			   args >> gear;
			   try
			   {
				   m_car.SetGear(gear);
				   m_output << "Gear set to " + to_string(gear) << endl;
			   }
			   catch (const InvalidGearException& e)
			   {
				   cout << e.GetMessage() << endl;
			   }
			   return true;
		   }
