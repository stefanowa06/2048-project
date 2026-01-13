/**
*
* Solution to course project # 8
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Teodora Stefanova
* @idnumber 7MI0600669
* @compiler VC
*
* <2048 Game - Comprehensive implementation with custom PRNG and no global variables>
*
*/

#include <iostream>
#include <fstream>

// --- CONSTANTS ---
const int MAX_BOARD_SIZE = 10;
const int T_2 = 2;
const int T_4 = 4;
const int LEADERBOARD_LIMIT = 5;
const int MAX_NAME_LEN = 100;
const int MIN_BOARD_SIZE = 4;
const int CLEAR_SCREEN_LINES = 40;
const int MAX_PATH_LEN = 64;

const unsigned int RAND_MULTIPLIER = 1103515245;
const unsigned int RAND_INCREMENT = 12345;
const unsigned int RAND_MODULUS = 2147483647;

// --- HELPERS ---

int myStrLen(const char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void myStrCpy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}
char digitToChar(int digit) {
    return digit + '0';
}

int getDigitsCount(int num) {
    if (num == 0) return 1;
    int count = 0;
    while (num > 0) {
        count++;
        num /= 10;
    }
    return count;
}

void reverseString(char* str, int len) {
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void toString(int num, char* str) {
    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    int len = getDigitsCount(num);
    for (int i = 0; i < len; i++) {
        str[i] = digitToChar(num % 10);
        num /= 10;
    }
    str[len] = '\0';
    reverseString(str, len);
}
void makePath(char* buf, int s) {
    char p1[] = "leaderboard_";
    char p2[] = ".txt";
    char sizeStr[5];
    toString(s, sizeStr);

    int k = 0;
    for (int i = 0; p1[i] != '\0'; i++)
        buf[k++] = p1[i];
    for (int i = 0; sizeStr[i] != '\0'; i++)
        buf[k++] = sizeStr[i];
    buf[k++] = 'x';
    for (int i = 0; sizeStr[i] != '\0'; i++)
        buf[k++] = sizeStr[i];
    for (int i = 0; p2[i] != '\0'; i++)
        buf[k++] = p2[i];
    buf[k] = '\0';
}

int getNextRand(int& seed) {
    seed = (seed * RAND_MULTIPLIER + RAND_INCREMENT) & RAND_MODULUS;
    return seed;
}
int main() {
    while (true) {
        std::cout << "1. Start Game" << std::endl;
        std::cout << "2. Leaderboard" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Choice: ";
        int ch;
        std::cin >> ch;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }
       
    }
    return 0;
}