static const int TOO_LONG_STRING = 200;

#include "catch.hpp"

#include <iostream>
#include <string>
#include "log.h"
#include "../NK_C_API.h"

int login;

TEST_CASE("C API connect", "[BASIC]") {
  login = NK_login_auto();
  REQUIRE(login != 0);
  NK_logout();
  login = NK_login_auto();
  REQUIRE(login != 0);
  NK_logout();
  login = NK_login_auto();
  REQUIRE(login != 0);
}

TEST_CASE("Check retry count", "[BASIC]") {
  REQUIRE(login != 0);
  REQUIRE(NK_get_admin_retry_count() == 3);
  REQUIRE(NK_get_user_retry_count() == 3);
}

TEST_CASE("Check long strings", "[STANDARD]") {
  REQUIRE(login != 0);
  const char* longPin = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  const char* pin = "123123123";
  auto result = NK_change_user_PIN(longPin, pin);
  REQUIRE(result == TOO_LONG_STRING);
  result = NK_change_user_PIN(pin, longPin);
  REQUIRE(result == TOO_LONG_STRING);
  CAPTURE(result);
}