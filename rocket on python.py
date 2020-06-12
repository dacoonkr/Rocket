def runRocket(code):
    stack = [ [],[],[],[],[],[],[],[],[],[],[] ]
    x = 0
    while x < len(code):
        if code[x] == ";":
            return
        if code[x] == "$":
            if code[x + 1] == "1":
                stack[1].append(int(input()))
            if code[x + 1] == "2":
                stack[1].append(float(input()))
            if code[x + 1] == "3":
                stack[1].append(str(input()))
            x += 1
        if code[x] == "%":
            print(stack[1][len(stack[1]) - 1], end = "")
        if code[x] == "^":
            del stack[1][len(stack[1]) - 1]
        if code[x] == "@":
            first = int(code[x + 1])
            second = int(code[x + 2])
            value = stack[first][len(stack[first]) - 1]
            del stack[first][len(stack[first]) - 1]
            stack[second].append(value)
            x += 2
        if code[x] == "#":
            first = int(code[x + 1])
            second = int(code[x + 2])
            value = stack[first][len(stack[first]) - 1]
            stack[second].append(value)
            x += 2
        if code[x] == "+":
            second = stack[1][len(stack[1]) - 1]
            del stack[1][len(stack[1]) - 1]
            first = stack[1][len(stack[1]) - 1]
            del stack[1][len(stack[1]) - 1]
            stack[1].append(first + second)
        if code[x] == "-":
            second = stack[1][len(stack[1]) - 1]
            del stack[1][len(stack[1]) - 1]
            first = stack[1][len(stack[1]) - 1]
            del stack[1][len(stack[1]) - 1]
            stack[1].append(first - second)
        if code[x] == "*":
            second = stack[1][len(stack[1]) - 1]
            del stack[1][len(stack[1]) - 1]
            first = stack[1][len(stack[1]) - 1]
            del stack[1][len(stack[1]) - 1]
            stack[1].append(first * second)
        if code[x] == "/":
            second = stack[1][len(stack[1]) - 1]
            del stack[1][len(stack[1]) - 1]
            first = stack[1][len(stack[1]) - 1]
            del stack[1][len(stack[1]) - 1]
            stack[1].append(first / second)
        if code[x] == ":":
            second = stack[1][len(stack[1]) - 1]
            del stack[1][len(stack[1]) - 1]
            first = stack[1][len(stack[1]) - 1]
            del stack[1][len(stack[1]) - 1]
            stack[1].append(first % second)
        if code[x] == "&":
            merge = ""
            while True:
                x += 1
                if code[x] == '&':
                    x = int(merge) - 2
                    break
                merge += code[x]
        if code[x] == "!":
            if code[x + 1] == "1":
                merge = ""
                x += 2
                while True:
                    x += 1
                    if code[x] == ')':
                        stack[1].append(int(merge))
                        break
                    merge += code[x]
            if code[x + 1] == "2":
                merge = ""
                x += 2
                while True:
                    x += 1
                    if code[x] == ')':
                        stack[1].append(float(merge))
                        break
                    merge += code[x]
            if code[x + 1] == "3":
                merge = ""
                x += 2
                while True:
                    x += 1
                    if code[x] == ')':
                        stack[1].append(str(merge))
                        break
                    merge += code[x]
        if code[x] == "~":
            if code[x + 1] == "=":
                x += 1
                first = stack[1][len(stack[1]) - 1]
                second = stack[1][len(stack[1]) - 2]
                if first == second:
                    merge = ""
                    while True:
                        x += 1
                        if code[x] == '*':
                            if merge == "]":
                                x = code.find("[")
                            elif merge == ">":
                                x = code.find("<")
                            elif merge == "}":
                                x = code.find("{")
                            elif merge == ";":
                                return
                            else:
                                x = int(merge) - 2
                            break
                        merge += code[x]
                else:
                    while True:
                        x += 1
                        if code[x] == '*':
                            break

            elif code[x + 1] == "1":
                x += 1
                first = stack[1][len(stack[1]) - 1]
                second = stack[1][len(stack[1]) - 2]
                if first < second:
                    merge = ""
                    while True:
                        x += 1
                        if code[x] == '*':
                            if merge == "]":
                                x = code.find("[")
                            elif merge == ">":
                                x = code.find("<")
                            elif merge == "}":
                                x = code.find("{")
                            elif merge == ";":
                                return
                            else:
                                x = int(merge) - 2
                            break
                        merge += code[x]
                else:
                    while True:
                        x += 1
                        if code[x] == '*':
                            break

            elif code[x + 1] == "2":
                x += 1
                first = stack[1][len(stack[1]) - 1]
                second = stack[1][len(stack[1]) - 2]
                if first > second:
                    merge = ""
                    while True:
                        x += 1
                        if code[x] == '*':
                            if merge == "]":
                                x = code.find("[")
                            elif merge == ">":
                                x = code.find("<")
                            elif merge == "}":
                                x = code.find("{")
                            elif merge == ";":
                                return
                            else:
                                x = int(merge) - 2
                            break
                        merge += code[x]
                else:
                    while True:
                        x += 1
                        if code[x] == '*':
                            break


        if code[x] == "]":
            x = code.find("[")
        if code[x] == ">":
            x = code.find("<")
        if code[x] == "}":
            x = code.find("{")
        x += 1

if __name__ == "__main__":
    runRocket("!3(Hello, World!)%")