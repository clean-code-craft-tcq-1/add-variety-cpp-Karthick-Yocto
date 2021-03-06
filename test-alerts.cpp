#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits - Test for Low Breach") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
}

TEST_CASE("infers the breach according to limits - Test for High Breach") {
	REQUIRE(inferBreach(32, 20, 30) == TOO_HIGH);
}

TEST_CASE("infers the breach according to limits - Test for No Breach") {
	REQUIRE(inferBreach(25, 20, 30) == NORMAL);
}

TEST_CASE("classifies the temperature breach for passive cooling- Test for Low Breach") {
	REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -1.0) == TOO_LOW);
}

TEST_CASE("classifies the temperature breach - Test for High Breach") {
	REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 36) == TOO_HIGH);
}

TEST_CASE("classifies the temperature breach for high active cooling - Test for Low Breach") {
	REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -1.0) == TOO_LOW);
}

TEST_CASE("classifies the temperature breach for high active cooling - Test for High Breach") {
	REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50) == TOO_HIGH);
}

TEST_CASE("classifies the temperature breach for med active cooling - Test for Low Breach") {
	REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -1.0) == TOO_LOW);
}

TEST_CASE("classifies the temperature breach for med active cooling - Test for High Breach") {
	REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 50) == TOO_HIGH);
}

TEST_CASE("check and alert via email - Test for Alert") {
	Messager* emailmsgobj = new EmailMessager;
	BatteryCharacter newbattery = { PASSIVE_COOLING , "Exide"};
	checkAndAlert( emailmsgobj , newbattery , 55) ;
}

TEST_CASE("check and alert via email - Test for No alert") {
	Messager* emailmsgobj = new EmailMessager;
	BatteryCharacter newbattery = { HI_ACTIVE_COOLING , "Amara Raja" };
	checkAndAlert(emailmsgobj, newbattery, 30);
}

TEST_CASE("check and alert via controller - Test for alert") {
	Messager* controllermsgobj = new ControllerMessager;
	BatteryCharacter newbattery = { MED_ACTIVE_COOLING , "Duracell" };
	checkAndAlert(controllermsgobj, newbattery, 50);
}
