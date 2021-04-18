#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include "../Bodies/CBody.h"
#include "../Bodies/CCompound.h"
#include "../Bodies/CCone.h"
#include "../Bodies/CSphere.h"
#include "../Bodies/CCylinder.h"
#include "../Bodies/CParallelepiped.h"
#include "../Bodies/Exception.h"

#include <string>
#include <sstream>

SCENARIO("Test sphere creation")
{
	CSphere sphere();
}