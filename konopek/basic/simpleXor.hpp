#ifndef CRYPTO_PALS_BASIC_SIMPLEXOR_HPP
#define CRYPTO_PALS_BASIC_SIMPLEXOR_HPP

#include <iostream>
#include <algorithm>

//lekcja nie uzywac charow tylko vektora usinged chara i zawsze wyrownywac to bajta

namespace simpleXor {
    const static unsigned char ASCII_NUMBER = '0';
    const static unsigned char ASCII_LETTER = 'a';
    const static unsigned char COMMON_LETTERS[] = {'e', 't', 'a', 'o', 'i', 'n'};
    typedef std::vector<unsigned char> rawBytes;

    struct seen {
        int times = 0;
        unsigned char item;
    };

    rawBytes xorHex(rawBytes const &message, rawBytes const &key) {
        rawBytes result;
        for (auto m = message.cbegin(), k = key.cbegin(); m != message.cend(); m++) {
            result.push_back(*m ^ *k);
            if ((k + 1) != key.cend()) k++;
        }
        return result;
    }

    rawBytes xorHexEncdoingWithRawAscii(std::string message, std::array<char,3> key ) {
        rawBytes result;
        auto k = key.cbegin();
        for (auto m = message.cbegin(); m != message.cend(); m++) {
            result.push_back(*m ^ *k);
            if ((k + 1) != key.cend()) {
                k++;
            } else {
                k = key.begin();
            }
        }
        return result;
    }

    bool seenCmp(seen x, seen y) {
        return (x.times > y.times);
    }

    void printRawByts(rawBytes const &message) {
        for (auto byte : message) {
            printf("%c", byte);
        }
        printf("\n");
    }

    rawBytes groupByMostKnown(rawBytes const &data) {
        std::vector<seen> items;
        for (auto i = data.cbegin(); i != data.cend(); i += 1) {
            seen result;
            result.item = *i;
            items.push_back(result);
        }
        for (auto i = items.begin(); i != items.end(); i++) {
            for (auto itemInsied : items) {
                if (i->item == itemInsied.item) {
                    i->times++;
                }
            }
        }
        std::sort(items.begin(), items.end(), seenCmp);
        rawBytes result;
        if(items.size() !=0){
            result.push_back(items.front().item);
        }
        for (auto item = items.begin(); item != items.end(); item++) {
            if (result.back() != item->item) {
                result.push_back(item->item);
            }
        }
        return result;
    }

    rawBytes generateTestKeys(rawBytes const &sortedMessage, int numberOfTests = 2) {
        rawBytes keys;
        if((sortedMessage.cend() - sortedMessage.cbegin()) < numberOfTests) numberOfTests = 0;
        for (auto letter : COMMON_LETTERS) {
            for (auto m = sortedMessage.begin(); m != (sortedMessage.begin() + numberOfTests ); m++) {
                keys.push_back(*m ^ letter);
            }
        }
        return keys;
    }

    std::vector<rawBytes> testKeys(rawBytes const &eMessage, rawBytes const &keys) {
        std::vector<rawBytes> result;
        for (auto key : keys) {
            bool isValid = true;
            rawBytes dMessage = xorHex(eMessage, std::vector<unsigned char>{key});
            for(auto letter : dMessage) {
                if(!isprint(letter) && letter != '\n') {
                    isValid = false;
                }
            }
            if(isValid) {
                printf("%c :", key);
                result.push_back(dMessage);
                printRawByts(dMessage);
            }
        }
        return result;
    }

    rawBytes stringToRawBytes(std::string const &string) {
        rawBytes buffer{};
        rawBytes result{};
        for (auto i : string) {
            char bits4;
            if (i < ASCII_LETTER) {
                bits4 = i - ASCII_NUMBER;
            } else {
                bits4 = i - ASCII_LETTER + 10;
            }
            buffer.push_back(bits4);
        }
        for (auto i = buffer.begin(); i != buffer.cend(); i += 1) {
            unsigned char b8;
            b8 = (*i << 4);
            if(i + 1 != buffer.cend()) {
                i++;
                b8 = b8 + *i;
            }
            result.push_back(b8);
        }
        return result;
    }

    void decrypt(rawBytes e) {
        rawBytes groupedChars = groupByMostKnown(e);
        rawBytes keys = generateTestKeys(groupedChars);
        std::vector<rawBytes> dMessages = testKeys(e, keys);
    }

    void decryptFile(std::string filename) {
        std::ifstream in(filename);
        if (!in) {
            printf("Cannot open the file.");
            return;
        }
        std::vector<simpleXor::rawBytes> inputs;
        while (in) {
            std::string line;
            std::getline(in, line);
            inputs.push_back(simpleXor::stringToRawBytes(line));
        }
        for (auto m : inputs) {
            simpleXor::decrypt(m);
        }
        in.close();
    }
}
#endif //CRYPTO_PALS_BASIC_SIMPLEXOR_HPP
