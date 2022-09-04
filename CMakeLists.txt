project(OchronaDanych)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cc algorytm_krasickiego.h indeks_koincydencji.h sito_erastotenesa.h utils.h szyfr_vigenere.h szyfr_cezara.h modulo_power.h diffie_hellman_key_exchange.h checksums.h rainbow_tables.h extended_euclid.h)