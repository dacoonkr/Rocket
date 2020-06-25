#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#define MAX_CODE_LEN 10000
using namespace std;

struct stkdata {
    int type; // 1 정수, 2 실수, 3 문자열
    string data;
};

bool debug_mode = false;
bool step_mode = false;
bool gotomode = false;

string filetext;
string pubcode = "";
char text[MAX_CODE_LEN];
stack<struct stkdata> stk[11];
stack<size_t> callstk;
size_t returnPoint[3] = { 0, 0, 0 };

int maxV(int a, int b) {
    if (a < b) return b;
    else return a;
}

void printNow(int st, int en) {
    string code = filetext + pubcode;
    if (st == -1) {
        for (int i = 1; i <= 10; i++) {
            if (!stk[i].empty()) {
                cout << "Stack " << i << " : ";
                stack<stkdata> tmp;
                while (!stk[i].empty()) {
                    tmp.push(stk[i].top());
                    stk[i].pop();
                }
                while (!tmp.empty()) {
                    if (tmp.top().type == 1) {
                        cout << "{" << "int, " << tmp.top().data << "}";
                    }
                    if (tmp.top().type == 2) {
                        cout << "{" << "float, " << tmp.top().data << "}";
                    }
                    if (tmp.top().type == 3) {
                        cout << "{" << "string, \"" << tmp.top().data << "\"}";
                    }
                    stk[i].push(tmp.top());
                    tmp.pop();
                    if (!tmp.empty()) cout << ", ";
                }
                cout << "\n";
            }
        }
        return;
    }
    if (debug_mode == true) {
        cout << "\n===========================\n";
        if (gotomode == false) {
            if (st == en) {
                cout << st + 1 << "번째 글자 실행 중\n";
            }
            else {
                cout << st + 1 << "번째 글자부터 " << en + 1 << "번째 글자 실행 중\n";
            }
        }
        else {
            cout << st + 1 << "번째 글자에서 " << en + 1 << "번째 글자로 이동 중\n";
            if (st > en) swap(st, en);
            gotomode = false;
        }
        for (int i = 0; i < 10; i++) {
            cout << " ";
        }
        cout << "v";
        if (st != en) {
            for (int i = 0; i < en - st - 1; i++) {
                cout << " ";
            }
            cout << "v";
        }
        cout << "\n";
        int space = maxV(0, 10 - st);
        if (space == 10 - st) {
            for (int i = 0; i < space; i++) {
                cout << " ";
            }
            cout << code;
        }
        else {
            cout << code.substr((size_t)st - 10, code.length());
        }
        cout << "\n";
        for (int i = 1; i <= 10; i++) {
            if (!stk[i].empty()) {
                cout << "Stack " << i << " : ";
                stack<stkdata> tmp;
                while (!stk[i].empty()) {
                    tmp.push(stk[i].top());
                    stk[i].pop();
                }
                while (!tmp.empty()) {
                    if (tmp.top().type == 1) {
                        cout << "{" << "int, " << tmp.top().data << "}";
                    }
                    if (tmp.top().type == 2) {
                        cout << "{" << "float, " << tmp.top().data << "}";
                    }
                    if (tmp.top().type == 3) {
                        cout << "{" << "string, \"" << tmp.top().data << "\"}";
                    }
                    stk[i].push(tmp.top());
                    tmp.pop();
                    if (!tmp.empty()) cout << ", ";
                }
                cout << "\n";
            }
        }
        if (step_mode == false) {
            cout << "===========================\n";
        }
        else {
            cout << "===========================";
            if (callstk.size() < 2) {
                getch();
            }
            cout << "\n";
        }
    }
}

void runRocket(size_t start, size_t end) {
    string code = filetext.substr(start, end - start);
    code = code + pubcode;
    size_t x = 0;
    int len = code.length();
    while (x < len) {
        if (code.at(x) == '$') {
            printNow(x, x + 1);
            cin.getline(text, MAX_CODE_LEN);
            stk[1].push({ code.at(x + 1) - '0', text });
            x++;
        }
        else if (code.at(x) == '%') {
            printNow(x, x);
            cout << stk[1].top().data;
        }
        else if (code.at(x) == '^') {
            printNow(x, x);
            stk[1].pop();
        }
        else if (code.at(x) == '#') {
            printNow(x, x + 2);
            stk[code.at(x + 2) - '0'].push(stk[code.at(x + 1) - '0'].top());
            x += 2;
        }
        else if (code.at(x) == '@') {
            printNow(x, x + 2);
            stk[code.at(x + 2) - '0'].push(stk[code.at(x + 1) - '0'].top());
            stk[code.at(x + 1) - '0'].pop();
            x += 2;
        }
        else if (code.at(x) == '!') {
            size_t tmp2 = x;
            while (code.at(x) != ')') {
                x++;
            }
            printNow(tmp2, x);
            x = tmp2;
            struct stkdata tmp = { code.at(x + 1) - '0',"" };
            x += 3;
            while (code.at(x) != ')') {
                tmp.data += code.at(x);
                x++;
            }
            stk[1].push(tmp);
        }
        else if (code.at(x) == '+') {
            printNow(x, x);
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
            if (first.type == 3 && second.type == 1) {
                char t = (char)(stoi(second.data));
                string tmp = "0";
                tmp[0] = t;
                first.data.append(tmp);
                stk[1].push({ 3, first.data });
            }
        }
        else if (code.at(x) == '-') {
            printNow(x, x);
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
            if (first.type == 3 && second.type == 1) {
                int a = stoi(second.data);
                stk[1].push({ 3, first.data.substr(0, first.data.length() - a) });
            }
        }
        else if (code.at(x) == '*') {
            printNow(x, x);
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
            if (first.type == 3 && second.type == 1) {
                int a = stoi(second.data);
                string tmp = "";
                for (int i = 0; i < a; i++) {
                    tmp += first.data;
                }
                stk[1].push({ 3, tmp });
            }
        }
        else if (code.at(x) == '/') {
            printNow(x, x);
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
            printNow(x, x);
            struct stkdata second = stk[1].top();
            stk[1].pop();
            struct stkdata first = stk[1].top();
            stk[1].pop();
            stk[1].push({ 1, to_string(stoi(first.data) % stoi(second.data)) });
        }
        else if (code.at(x) == '&') {
            size_t tmp2 = x;
            x++;
            while (code.at(x) != '&') {
                x++;
            }
            printNow(tmp2, x);
            x = tmp2;
            string tmp = "";
            x += 1;
            while (code.at(x) != '&') {
                tmp += code.at(x);
                x++;
            }
            x = (size_t)stoi(tmp) - 2;
        }
        else if (code.at(x) == '`') {
            if (code.at(x + 1) == '/') {
                size_t tmp2 = x;
                x += 2;
                while (code.at(x) != '`') {
                    x++;
                }
                printNow(tmp2, x);
                x = tmp2;
                string tmp = "";
                x += 2;
                while (code.at(x) != '`') {
                    tmp += code.at(x);
                    x++;
                }
                tmp = '`' + tmp + '`';
                x = code.find(tmp) - 1;
            }
            else {
                x += 1;
                while (code.at(x) != '`') {
                    x++;
                }
            }
        }
        else if (code.at(x) == '\'') {
            size_t tmp2 = x;
            x++;
            while (code.at(x) != '\'') {
                x++;
            }
            printNow(tmp2, x);
            x = tmp2;
            string tmp = "";
            x += 1;
            while (code.at(x) != '\'') {
                tmp += code.at(x);
                x++;
            }
            string pkname = "library//";
            pkname += tmp;
            fstream pkfile(pkname);
            string pkcode;
            string buff;
            while (getline(pkfile, buff)) {
                if (buff[0] != '#') {
                    pkcode += buff;
                }
            }
            pubcode += pkcode;
            cout << "라이브러리 " << tmp << "가 로드되었습니다.";
        }
        else if (code.at(x) == '~' && code.at(x + 1) == '-') {
            size_t tmp2 = x;
            x += 2;
            while (code.at(x) != '*') {
                x++;
            }
            printNow(tmp2, x);
            x = tmp2;
            string tmp = "";
            x += 2;
            while (code.at(x) != '*') {
                tmp += code.at(x);
                x++;
            }
            if (tmp == "_") {
                stk[1].push({ 1, to_string(stk[1].top().data.length()) });
            }
            else if (tmp == "$") {
                stkdata tmp2 = stk[1].top();
                stk[1].pop();
                string tmp3 = stk[1].top().data;
                stk[1].push(tmp2);
                int a = tmp3[(size_t)stoi(tmp2.data)];
                stk[1].push({ 1, to_string(a) });
            }
            else {
                int a = stk[1].top().data[(size_t)stoi(tmp)];
                stk[1].push({ 1, to_string(a) });
            }
        }
        else if (code.at(x) == '~' && code.at(x + 1) == '+') {
            size_t tmp2 = x;
            x += 2;
            while (code.at(x) != '*') {
                x++;
            }
            printNow(tmp2, x);
            x = tmp2;
            string tmp = "";
            x += 2;
            while (code.at(x) != '*') {
                tmp += code.at(x);
                x++;
            }
            if (tmp == "_") {
                stk[1].push({ 1, to_string(stk[1].size()) });
            }
        }
        else if (code.at(x) == '~' && code.at(x + 1) == '=') {
            size_t tmp2 = x;
            x += 2;
            while (code.at(x) != '*') {
                x++;
            }
            printNow(tmp2, x);
            x = tmp2;
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
                else if (tmp[0] == '/') {
                    tmp = tmp.substr(1, tmp.length());
                    tmp = '`' + tmp + '`';
                    x = code.find(tmp) - 1;
                }
                else {
                    x = (size_t)stoi(tmp) - 2;
                }
            }
        }
        else if (code.at(x) == '~' && code.at(x + 1) == '1') {
            size_t tmp2 = x;
            x += 2;
            while (code.at(x) != '*') {
                x++;
            }
            printNow(tmp2, x);
            x = tmp2;
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
                else if (tmp[0] == '/') {
                    tmp = tmp.substr(1, tmp.length());
                    tmp = '`' + tmp + '`';
                    x = code.find(tmp) - 1;
                }
                else {
                    x = (size_t)stoi(tmp) - 2;
                }
            }
        }
        else if (code.at(x) == '~' && code.at(x + 1) == '2') {
            size_t tmp2 = x;
            x += 2;
            while (code.at(x) != '*') {
                x++;
            }
            printNow(tmp2, x);
            x = tmp2;
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
                else if (tmp[0] == '/') {
                    tmp = tmp.substr(1, tmp.length());
                    tmp = '`' + tmp + '`';
                    x = code.find(tmp) - 1;
                }
                else {
                    x = (size_t)stoi(tmp) - 2;
                }
            }
        }
        else if (code.at(x) == ']') {
            gotomode = true;
            printNow(x, code.find('['));
            x = code.find('[') - 1;
        }
        else if (code.at(x) == '}') {
            gotomode = true;
            printNow(x, code.find('{'));
            x = code.find('{') - 1;
        }
        else if (code.at(x) == '>') {
            gotomode = true;
            printNow(x, code.find('<'));
            x = code.find('<') - 1;
        }
        else if (code.at(x) == ';') {
            printNow(x, x);
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
            size_t tmp4 = x;
            x += 1;
            while (code.at(x) != '\"') {
                x++;
            }
            printNow(tmp4, x);
            x = tmp4;
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
    cin.sync_with_stdio(1);
    cin.tie(0);
    if (argv[1] != nullptr) {
        fstream file(argv[1]);
        string buff;
        while (getline(file, buff)) {
            filetext += (buff + '\n');
        }
        debug_mode = false;
        runRocket(0, filetext.length());
        cout << "\n프로그램이 종료되었습니다...";
        char g = getch();
    }
    else {
        while (1) {
            cout << ">> ";
            cin.getline(text, MAX_CODE_LEN);
            string str(text);
            filetext = str;
            debug_mode = false;
            step_mode = false;
            if (filetext.rfind("debug ", 0) == 0) {
                debug_mode = true;
                filetext = filetext.substr(6, filetext.length());
            }
            if (filetext.rfind("step ", 0) == 0) {
                debug_mode = true;
                step_mode = true;
                filetext = filetext.substr(5, filetext.length());
            }
            if (filetext == "stack") {
                printNow(-1, -1);
            }
            else {
                runRocket(0, filetext.length());
            }
            cout << "\n";
        }
    }
}