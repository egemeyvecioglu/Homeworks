number = input()
index = number.find("?")

if(number[5] == "X"):
    digit5 = 10
else:
    if(number[5]!="?"):
        digit5 = int(number[5])

if(index == 0 or index == 1 or index == 2 or index == 3) :
    
    if(index == 0):
        a = (digit5 - 3 * int(number[1]) - 5 * int(number[2]) - 7 * int(number[3])) % 2
        n = ( digit5 - 3 * int(number[1]) - 5 * int(number[2]) - 7 * int(number[3])  + a * 11 ) / 2 % 11
        print(str(int(n))+number[1:])
    elif(index == 1):
        b = (digit5 - 2 * int(number[0]) - 5 * int(number[2]) - 7 * int(number[3]))  % 3
        n = (digit5 - 2 * int(number[0]) - 5 * int(number[2]) - 7 * int(number[3])  + 11 * b) / 3 % 11
        print(number[0:1] + str(int(n)) + number[2:])
    elif(index == 2):
        c = (digit5 - 2 * int(number[0]) - 3 * int(number[1]) - 7 * int(number[3])) % 5
        n = ( digit5 - 2 * int(number[0]) - 3 * int(number[1]) - 7 * int(number[3]) - c * 11) / 5 % 11
        print(number[0:2] + str(int(n)) + number[3:])
    elif(index == 3):
        d = (digit5- 2 * int(number[0]) - 3 * int(number[1]) - 5 * int(number[2])) % (-4)
        n = (digit5 - 2 * int(number[0]) - 3 * int(number[1]) - 5 * int(number[2]) + d * 11)  / (-4) % 11
        print(number[0:3] + str(int(n)) + number[4:])

elif(index == 5):
    n = (2 * int(number[0]) + 3 * int(number[1]) + 5 * int(number[2]) + 7 * int(number[3])) % 11
    if(n==10):
        n = "X"
        print(number[0:5] + n)
    else:
        print(number[0:5] + str(int(n)))    
    
else:
    checkdigit = (2 * int(number[0]) + 3 * int(number[1]) + 5 * int(number[2]) + 7 * int(number[3])) % 11

    if((digit5) == checkdigit):
        print("VALID")
    else:
        print("INVALID")
