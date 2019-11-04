#include <iostream>
#include <cassert>
#include <vector>
#include <fstream>
#include <array>
#include "simpleXor.hpp"
#include "base64.hpp"

void tests(void);

int main() {

    tests();
    return 0;
}


void tests(void) {
    printf("Tests start:\n");
    printf("test 1: \n \n");
    std::string hexData{"49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"};
    std::string result1 = base64::hexToBase64(base64::stringToHex(hexData));
    assert(result1 == "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t");
    //drugie jest zawarte w w kazdym zadaniu w sumie
    printf("test 3: \n \n");
    simpleXor::rawBytes e = simpleXor::stringToRawBytes("1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736");
    simpleXor::decrypt(e);
    printf("\ntest 4: \n\n ");
    simpleXor::decryptFile("messages.txt");
    //klucz to 'X' wiadomosc to Cooking MC's like a pound of bacon
    printf("test 5: \n \n");
    simpleXor::rawBytes multiXorResult = simpleXor::xorHexEncdoingWithRawAscii(std::string{"Burning 'em, if you ain't quick and nimble I go crazy when I hear a cymbal"},std::array<char,3>{'I','C','E'});
    for(auto i : multiXorResult) {
        printf("%0x",i);
    }
    //klucz to 53 decimal a wiadomosc: Now that the party is jumping // tu jest jakis bug z alokacja pamieci
}
