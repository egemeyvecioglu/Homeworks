import the4

with open("cases.txt", 'r') as c:
    v = 0
    t = 0
    ll = c.readlines()
    Descriptions = []
    for l in ll:
        if l.startswith("["):
            Descriptions = eval(l.strip('\n'))
            continue
        t += 1
        l = l.strip('\n').split('|')
        result = the4.inheritance(Descriptions + [l[0]])
        result.sort(key=lambda x: x[0])
        expResult = eval(l[1])
        expResult.sort(key=lambda x: x[0])
        if len(result) == len(expResult):
            for r in zip(result,expResult):
                if abs(r[0][1] - r[1][1]) > 10**-8:
                    print(r)
                    break
            else:
                v += 1
        else:
            print("-"*50)
            print("Resulting Value \t" ,result)
            print("Expected Value","\t",expResult)
    print(f"All cases tested. \n{v}/{t} is correct")
