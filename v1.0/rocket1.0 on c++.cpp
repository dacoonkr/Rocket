#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <stdlib.h>
#include <conio.h>
#define MAX_CODE_LEN 10000
using namespace std;

struct stkdata {
    int type; // 1 ����, 2 �Ǽ�, 3 ���ڿ�
    string data;
};

char text[MAX_CODE_LEN];
stack<struct stkdata> stk[11];
size_t returnPoint[3] = { 0,0,0 };

void runRocket(string code) {
    int len = code.length();
    size_t x = 0;
    while (x < len) {
        if (code.at(x) == '$') {
            cin.getline(text, MAX_CODE_LEN);
            stk[1].push({ code.at(x + 1) - '0', text });
            x++;
        }
        else if (code.at(x) == '%') {
            cout << stk[1].top().data;
        }
        else if (code.at(x) == '^') {
            stk[1].pop();
        }
        else if (code.at(x) == '#') {
            stk[code.at(x + 2) - '0'].push(stk[code.at(x + 1) - '0'].top());
        }
        else if (code.at(x) == '@') {
            stk[code.at(x + 2) - '0'].push(stk[code.at(x + 1) - '0'].top());
            stk[code.at(x + 1) - '0'].pop();
            x += 2;
        }
        else if (code.at(x) == '!') {
            struct stkdata tmp = { code.at(x + 1) - '0',"" };
            x += 3;
            while (code.at(x) != ')') {
                tmp.data += code.at(x);
                x++;
            }
            stk[1].push(tmp);
        }
        else if (code.at(x) == '+') {
            struct stkdata second = stk[1].top();
            stk[1].pop();
            struct stkdata first = stk[1].top();
            stk[1].pop();
            if (first.type == 1 && second.type == 1) {
                stk[1].push({ 1, to_string(stoi(first.data) + stoi(second.data)) });
            }
            if (first.type == 1 && second.type == 2) {
                stk[1].push({ 2, to_string(stoi(first.data) + stod(second.data)) });
            }
            if (first.type == 2 && second.type == 1) {
                stk[1].push({ 2, to_string(stod(first.data) + stoi(second.data)) });
            }
            if (first.type == 2 && second.type == 2) {
                stk[1].push({ 2, to_string(stod(first.data) + stod(second.data)) });
            }
            if (first.type == 3 && second.type == 3) {
                first.data.append(second.data);
                stk[1].push({ 3, first.data });
            }
        }
        else if (code.at(x) == '-') {
            struct stkdata second = stk[1].top();
            stk[1].pop();
            struct stkdata first = stk[1].top();
            stk[1].pop();
            if (first.type == 1 && second.type == 1) {
                stk[1].push({ 1, to_string(stoi(first.data) - stoi(second.data)) });
            }
            if (first.type == 1 && second.type == 2) {
                stk[1].push({ 2, to_string(stoi(first.data) - stod(second.data)) });
            }
            if (first.type == 2 && second.type == 1) {
                stk[1].push({ 2, to_string(stod(first.data) - stoi(second.data)) });
            }
            if (first.type == 2 && second.type == 2) {
                stk[1].push({ 2, to_string(stod(first.data) - stod(second.data)) });
            }
        }
        else if (code.at(x) == '*') {
            struct stkdata second = stk[1].top();
            stk[1].pop();
            struct stkdata first = stk[1].top();
            stk[1].pop();
            if (first.type == 1 && second.type == 1) {
                stk[1].push({ 1, to_string(stoi(first.data) * stoi(second.data)) });
            }
            if (first.type == 1 && second.type == 2) {
                stk[1].push({ 2, to_string(stoi(first.data) * stod(second.data)) });
            }
            if (first.type == 2 && second.type == 1) {
                stk[1].push({ 2, to_string(stod(first.data) * stoi(second.data)) });
            }
            if (first.type == 2 && second.type == 2) {
                stk[1].push({ 2, to_string(stod(first.data) * stod(second.data)) });
            }
        }
        else if (code.at(x) == '/') {
            struct stkdata second = stk[1].top();
            stk[1].pop();
            struct stkdata first = stk[1].top();
            stk[1].pop();
            if (first.type == 1 && second.type == 1) {
                stk[1].push({ 1, to_string(stoi(first.data) / stoi(second.data)) });
            }
            if (first.type == 1 && second.type == 2) {
                stk[1].push({ 2, to_string(stoi(first.data) / stod(second.data)) });
            }
            if (first.type == 2 && second.type == 1) {
                stk[1].push({ 2, to_string(stod(first.data) / stoi(second.data)) });
            }
            if (first.type == 2 && second.type == 2) {
                stk[1].push({ 2, to_string(stod(first.data) / stod(second.data)) });
            }
        }
        else if (code.at(x) == ':') {
            struct stkdata second = stk[1].top();
            stk[1].pop();
            struct stkdata first = stk[1].top();
            stk[1].pop();
            stk[1].push({ 1, to_string(stoi(first.data) % stoi(second.data)) });
        }
        else if (code.at(x) == '&') {
            string tmp = "";
            x += 1;
            while (code.at(x) != '&') {
                tmp += code.at(x);
                x++;
            }
            x = (size_t)stoi(tmp) - 2;
        }
        else if (code.at(x) == '~' && code.at(x + 1) == '=') {
            stkdata second = stk[1].top();
            stk[1].pop();
            stkdata first = stk[1].top();
            stk[1].push(second);
            string tmp = "";
            x += 2;
            while (code.at(x) != '*') {
                tmp += code.at(x);
                x++;
            }
            if (first.data.compare(second.data) == 0) {
                if (tmp[0] == ']') {
                    x = code.find('[') - 1;
                }
                else if (tmp[0] == '}') {
                    x = code.find('{') - 1;
                }
                else if (tmp[0] == '>') {
                    x = code.find('<') - 1;
                }
                else if (tmp[0] == ';') {
                    return;
                }
                else {
                    x = (size_t)stoi(tmp) - 2;
                }
            }
        }
        else if (code.at(x) == '~' && code.at(x + 1) == '1') {
            stkdata second = stk[1].top();
            stk[1].pop();
            stkdata first = stk[1].top();
            stk[1].push(second);
            string tmp = "";
            x += 2;
            while (code.at(x) != '*') {
                tmp += code.at(x);
                x++;
            }
            if (stoi(first.data) > stoi(second.data)) {
                if (tmp[0] == ']') {
                    x = code.find('[') - 1;
                }
                else if (tmp[0] == '}') {
                    x = code.find('{') - 1;
                }
                else if (tmp[0] == '>') {
                    x = code.find('<') - 1;
                }
                else if (tmp[0] == ';') {
                    return;
                }
                else {
                    x = (size_t)stoi(tmp) - 2;
                }
            }
        }
        else if (code.at(x) == '~' && code.at(x + 1) == '2') {
            stkdata second = stk[1].top();
            stk[1].pop();
            stkdata first = stk[1].top();
            stk[1].push(second);
            string tmp = "";
            x += 2;
            while (code.at(x) != '*') {
                tmp += code.at(x);
                x++;
            }
            if (stoi(first.data) < stoi(second.data)) {
                if (tmp[0] == ']') {
                    x = code.find('[') - 1;
                }
                else if (tmp[0] == '}') {
                    x = code.find('{') - 1;
                }
                else if (tmp[0] == '>') {
                    x = code.find('<') - 1;
                }
                else if (tmp[0] == ';') {
                    return;
                }
                else {
                    x = (size_t)stoi(tmp) - 2;
                }
            }
        }
        else if (code.at(x) == ']') {
            x = code.find('[') - 1;
        }
        else if (code.at(x) == '}') {
            x = code.find('{') - 1;
        }
        else if (code.at(x) == '>') {
            x = code.find('<') - 1;
        }
        else if (code.at(x) == ';') {
            return;
        }
        x++;
    }
}

int main(int argc, char** argv) {
    string filetext;
    if (argv[1] != nullptr) {
        fstream file(argv[1]);
        string buff;
        while (getline(file, buff)) {
            filetext += (buff + '\n');
        }
        runRocket(filetext);
        cout << "\n���α׷��� ����Ǿ����ϴ�...";
        char g = getch();
    }
    else {
        while (1) {
            cout << "> ";
            cin.getline(text, MAX_CODE_LEN);
            string str(text);
            filetext = str;
            runRocket(filetext);
            cout << "\n";
        }
    }
}