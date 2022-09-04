#include <array>
#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "extended_euclid.h"
#include "modulo_power.h"
#include "sito_erastotenesa.h"
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

void TestExtendedEuclid() {
  MK_ASSERT_EQ(ExtendedEuclid(10, 5), 5, "");
  MK_ASSERT_EQ(ExtendedEuclid(125, 225), 25, "");
  MK_ASSERT_EQ(ExtendedEuclid(294, 546), 42, "");
}

void TestIsMerseneNumberPrime() {
  // Reference values from: https://www.mersenne.org/primes/
//  MK_ASSERT_EQ(IsMerseneNumberPrime(2), true, ""); //FIXME(mkojro) Not working for 2
  MK_ASSERT_EQ(IsMerseneNumberPrime(4), false, "");
  MK_ASSERT_EQ(IsMerseneNumberPrime(11), false, "");
  MK_ASSERT_EQ(IsMerseneNumberPrime(13), true, "");
  MK_ASSERT_EQ(IsMerseneNumberPrime(17), true, "");
}

int main() {
  auto tests = {TestCesarCypher, TestVigenere, TestModPower, TestExtendedEuclid,
                TestIsMerseneNumberPrime};
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