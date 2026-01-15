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
#include <cstdlib>   
#include <ctime>     
#include <iomanip>   

const int MAX_BOARD_SIZE = 10;
const int T_2 = 2;
const int T_4 = 4;
const int LEADERBOARD_LIMIT = 5;
const int MAX_NAME_LEN = 100;
const int MIN_BOARD_SIZE = 4;
const int CLEAR_SCREEN_LINES = 40;
const int MAX_PATH_LEN = 64;

int myStrLen(const char* str) 
{
    int len = 0;
    while (str[len] != '\0') 
    {
        len++;
    }
    return len;
}

void myStrCpy(char* dest, const char* src) 
{
    int i = 0;
    while (src[i] != '\0') 
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}
char digitToChar(int digit) 
{
    return digit + '0';
}

int getDigitsCount(int num) 
{
    if (num == 0) return 1;
    int count = 0;
    while (num > 0) 
    {
        count++;
        num /= 10;
    }
    return count;
}

void reverseString(char* str, int len) 
{
    for (int i = 0; i < len / 2; i++) 
    {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void toString(int num, char* str) 
{
    if (num == 0)
    {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    int len = getDigitsCount(num);
    for (int i = 0; i < len; i++) 
    {
        str[i] = digitToChar(num % 10);
        num /= 10;
    }
    str[len] = '\0';
    reverseString(str, len);
}
void clear() 
{
    for (int i = 0; i < 50; i++) 
    {
        std::cout << std::endl;
    }
}
void makePath(char* buf, int s) 
{
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

void spawn(int b[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n) 
{
    int emptyCells[MAX_BOARD_SIZE * MAX_BOARD_SIZE][2];
    int count = 0;
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            if (b[i][j] == 0)
            {
                emptyCells[count][0] = i;
                emptyCells[count][1] = j;
                count++;
            }
        }
    }

    if (count > 0) 
    {
        int idx = std::rand() % count;
        int r = emptyCells[idx][0];
        int c = emptyCells[idx][1];
        b[r][c] = (std::rand() % 10 == 0) ? T_4 : T_2;
    }
}

void shift(int* line, int n) 
{
    int temp[MAX_BOARD_SIZE] = { 0 };
    int p = 0;
    for (int i = 0; i < n; i++) 
    {
        if (line[i] != 0) temp[p++] = line[i];
    }
    for (int i = 0; i < p - 1; i++) 
    {
        if (temp[i] == temp[i + 1] && temp[i] != 0) 
        {
            temp[i] *= 2;
            temp[i + 1] = 0;
            i++;
        }
    }
    int f = 0;
    for (int i = 0; i < n; i++)
        line[i] = 0;
    for (int i = 0; i < p; i++)
    {
        if (temp[i] != 0) 
            line[f++] = temp[i];
    }
}

bool move(int b[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n, char d) 
{
    int old[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) old[i][j] = b[i][j];

    for (int i = 0; i < n; i++) 
    {
        int line[MAX_BOARD_SIZE] = { 0 };
        if (d == 'a' || d == 'd') 
        {
            for (int j = 0; j < n; j++)
                line[j] = (d == 'a') ? b[i][j] : b[i][n - 1 - j];
            shift(line, n);
            for (int j = 0; j < n; j++)
                if (d == 'a') b[i][j] = line[j];
                else b[i][n - 1 - j] = line[j];
        }
        else if (d == 'w' || d == 's') 
        {
            for (int j = 0; j < n; j++)
                line[j] = (d == 'w') ? b[j][i] : b[n - 1 - j][i];
            shift(line, n);
            for (int j = 0; j < n; j++)
                if (d == 'w') b[j][i] = line[j];
                else b[n - 1 - j][i] = line[j];
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (b[i][j] != old[i][j]) return true;
    return false;
}

bool canContinue(int b[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n) 
{
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            if (b[i][j] == 0) return true;
            if (j + 1 < n && b[i][j] == b[i][j + 1]) return true;
            if (i + 1 < n && b[i][j] == b[i + 1][j]) return true;
        }
    }
    return false;
}

void show(int b[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int n) 
{
    clear();
    int score = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) score += b[i][j];

    std::cout << "Current Score: " << score << std::endl << std::endl;
    for (int i = 0; i < n; i++) 
    {
        std::cout << "|";
        for (int j = 0; j < n; j++) 
        {
            if (b[i][j] == 0) std::cout << std::setw(6) << ".";
            else std::cout << std::setw(6) << b[i][j]; 
        std::cout << " |" << std::endl;
    }
}

void play() 
{
    std::srand(std::time(0)); 
    int b[MAX_BOARD_SIZE][MAX_BOARD_SIZE] = { 0 };
    char name[MAX_NAME_LEN + 1];
    int n;

    std::cout << "Enter Nickname: ";
    std::cin >> name;

    do 
    {
        std::cout << "Enter Size (4-10): ";
        std::cin >> n;
    } while (n < MIN_BOARD_SIZE || n > MAX_BOARD_SIZE);

    spawn(b, n);
    spawn(b, n);

    while (canContinue(b, n)) 
    {
        show(b, n);
        std::cout << "Move (w/a/s/d): ";
        char c;
        std::cin >> c;
        if (c >= 'A' && c <= 'Z') c += 32; 
        if (c == 'w' || c == 'a' || c == 's' || c == 'd') 
        {
            if (move(b, n, c)) 
            {
                spawn(b, n);
            }
        }
    }
    show(b, n);
    std::cout << "\nGAME OVER!" << std::endl;
}
int main() 
{
    while (true)
    {
        std::cout << "1. Start Game" << std::endl;
        std::cout << "2. Leaderboard" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Choice: ";
        int ch;
        std::cin >> ch;
        if (std::cin.fail()) 
        {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }
        if (ch == 1) play();
        else if (ch == 3) break;
    }
    return 0;
}