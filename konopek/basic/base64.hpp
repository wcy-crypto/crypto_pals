#ifndef CRYPTO_PALS_BASIC_BASE64_HPP
#define CRYPTO_PALS_BASIC_BASE64_HPP


#include <string>

namespace base64 {

    const static unsigned char ASCII_NUMBER = '0';
    const static unsigned char ASCII_LETTER = 'a';
    const static unsigned char BASE64TABLE[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
                                                'O', 'P',
                                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
                                                'e', 'f',
                                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                                                'u', 'v',
                                                'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                                                '+', '/'};

    std::string hexToBase64(std::string const &buffer) {
        std::string result{};

        for (auto i = buffer.cbegin(); i != buffer.cend(); ++i) {
            char bits6;
            char tmp2 = ((*(i + 1) & 12) >> 2);
            bits6 = (*i << 2) + tmp2;
            result += BASE64TABLE[bits6];
            ++i;
            bits6 = ((*i & 3) << 4) + *(i + 1);
            result += BASE64TABLE[bits6];
            ++i;
        }
        return result;
    }

    std::string stringToHex(std::string const &string) {
        std::string buffer{};
        for (auto i : string) {
            char bits4;
            if (i <= ASCII_LETTER) {
                bits4 = i - ASCII_NUMBER;
                buffer += bits4;
            } else {
                bits4 = i - ASCII_LETTER + 10;
                buffer += bits4;
            }
        }
        return buffer;
    }
}

#endif //CRYPTO_PALS_BASIC_BASE64_HPP
