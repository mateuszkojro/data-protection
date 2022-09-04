#include <array>
#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "modulo_power.h"
#include "szyfr_cezara.h"
#include "szyfr_vigenere.h"
#include "utils.h"

void TestCesarCypher() {
  std::string messgae = "helloworld";
  int key = 12;

  std::string encrypted = CesarsCypher(messgae, key);
  MK_ASSERT_EQ(
      messgae, DecipherCesarsCypher(encrypted, key),
      "Cesar's cypher: Encrypted and decrypted messages should be the same");
}

void TestVigenere() {
  std::string messgae = "helloworld";
  std::string key = "abc";

  std::string encrypted = VigenereCypher(messgae, key);
  MK_ASSERT_EQ(
      messgae, DecipherVigenereCypher(encrypted, key),
      "Vigenere cypher encrypted and decrypted message should be the same");
}

void TestModPower() {
  int a = 5, b = 6, c = 10;
  MK_ASSERT_EQ(ModPower(a, b, c), Pow(a, b) % c,
               "a^b % c should be equal optimised modulo power");
}

int main() {
  auto tests = {TestCesarCypher, TestVigenere, TestModPower};
  int tests_failed = 0;
  for (auto test : tests) {
    try {
      test();
    } catch (std::exception& exception) {
      std::cout << "Test failed: " << exception.what() << std::endl;
      tests_failed++;
    }
  }

  if (tests_failed == 0) {
    std::cout << "OK: All tests passed!" << std::endl;
    return 0;
  } else {
    std::cout << "FAIL: Tests failed: " << tests_failed << std::endl;
    return 1;
  }
}