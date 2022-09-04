#include <array>
#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "diffie_hellman_key_exchange.h"
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
  {
  int a = 2, b = 2, c = 3;
  MK_ASSERT_EQ(ModPower(a, b, c), Pow(a, b) % c,
               "a^b % c should be equal optimised modulo power");
  }
  {
    int a = 5, b = 13, c = 4;
    MK_ASSERT_EQ(ModPower(a, b, c), Pow(a, b) % c,
                 "a^b % c should be equal optimised modulo power");
  }
  {
    int a = 123, b = 3, c = 12;
    MK_ASSERT_EQ(ModPower(a, b, c), Pow(a, b) % c,
                 "a^b % c should be equal optimised modulo power");
  }
}

void TestExtendedEuclid() {
  MK_ASSERT_EQ(ExtendedEuclid(10, 5), 5, "");
  MK_ASSERT_EQ(ExtendedEuclid(125, 225), 25, "");
  MK_ASSERT_EQ(ExtendedEuclid(294, 546), 42, "");
}

void TestIsMerseneNumberPrime() {
  // Reference values from: https://www.mersenne.org/primes/
  // FIXME(mkojro) Not working for 2
  //  MK_ASSERT_EQ(IsMerseneNumberPrime(2), true, "");
  MK_ASSERT_EQ(IsMerseneNumberPrime(4), false, "");
  MK_ASSERT_EQ(IsMerseneNumberPrime(11), false, "");
  MK_ASSERT_EQ(IsMerseneNumberPrime(13), true, "");
  MK_ASSERT_EQ(IsMerseneNumberPrime(17), true, "");
}

void TestDiffieHellmanKeyExchange() {
  // Implementing key exchange from:
  // https://en.wikipedia.org/wiki/Diffie%E2%80%93Hellman_key_exchange#Cryptographic_explanation

  // 1. Alice and Bob publicly agree to use a modulus p = 23 and base g = 5
  // (which is a primitive root modulo 23).
  int p = 23;
  int g = 5;

  // 2. Alice chooses a secret integer a = 4, then sends Bob A = g^a mod p
  int a = 4;
  int public_message_to_bob = APowBModC(g, a, p);
  int A = public_message_to_bob;

  // 3. Bob chooses a secret integer b = 3, then sends Alice B = g^b mod p
  int b = 3;
  int public_message_to_alice = APowBModC(g, b, p);
  int B = public_message_to_alice;

  // 4. Alice computes s = B^a mod p
  int alice_secret = APowBModC(B, a, p);

  // 5. Bob computes s = A^b mod p
  int bob_secret = APowBModC(A, b, p);

  MK_ASSERT_EQ(alice_secret, bob_secret, "Alice and bob should share a common secret");
  MK_ASSERT_EQ(alice_secret, 18, "The secret in this example should be 18");
}

int main() {
  auto tests = {TestCesarCypher,
                TestVigenere,
                TestModPower,
                TestExtendedEuclid,
                TestIsMerseneNumberPrime,
                TestDiffieHellmanKeyExchange};
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
    return tests_failed;
  }
}