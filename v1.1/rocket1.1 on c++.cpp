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
    int type; // 1 정수, 2 실수, 3 문자열
    string data;
};

string filetext;
char text[MAX_CODE_LEN];
stack<struct stkdata> stk[11];
stack<size_t> callstk;
size_t returnPoint[3] = { 0,0,0 };

void runRocket(size_t start, size_t end) {
    string code = filetext.substr(start, end - start);
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
                    if (callstk.empty()) {
                        return;
                    }
                    else {
                        x = callstk.top();
                        callstk.pop();
                    }
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
                    if (callstk.empty()) {
                        return;
                    }
                    else {
                        x = callstk.top();
                        callstk.pop();
                    }
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
                    if (callstk.empty()) {
                        return;
                    }
                    else {
                        x = callstk.top();
                        callstk.pop();
                    }
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
            if (callstk.empty()) {
                return;
            }
            else {
                x = callstk.top();
                callstk.pop();
            }
        }
        else if (code.at(x) == '?') {
            x += 1;
            int tmp = 0;
            while (1) {
                if (code.at(x) == '?') {
                    if (tmp == 0) tmp = 1;
                    else break;
                }
                x++;
            }
        }
        else if (code.at(x) == '\"') {
            string tmp = "";
            x++;
            while (code.at(x) != '\"') {
                tmp += code.at(x);
                x++;
            }
            size_t backlive = x;
            size_t stfunc = code.find("?" + tmp + "?");
            int tmp2 = 0;
            int tmp3 = x;
            x = stfunc + 1;
            while (1) {
                if (code[x] == '?') {
                    if (tmp2 == 0) {
                        tmp2 = 1;
                        stfunc = x;
                    }
                    else {
                        break;
                    }
                }
                x++;
            }
            callstk.push(tmp3);
            x = stfunc;
        }
        x++;
    }

}

int main(int argc, char** argv) {
    if (argv[1] != nullptr) {
        fstream file(argv[1]);
        string buff;
        while (getline(file, buff)) {
            filetext += (buff + '\n');
        }
        runRocket(0, filetext.length());
        cout << "\n프로그램이 종료되었습니다...";
        char g = getch();
    }
    else {
        while (1) {
            cout << "> ";
            cin.getline(text, MAX_CODE_LEN);
            string str(text);
            filetext = str;
            runRocket(0, filetext.length());
            cout << "\n";
        }
    }
}