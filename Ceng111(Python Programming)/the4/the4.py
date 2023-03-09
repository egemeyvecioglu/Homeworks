def inheritance(Descriptions):
    lst=create_data(Descriptions)
    data =lst[0]
    person = lst[1][0]
    heritance =lst[1][1] 

    pgs = create_pgs(data,person)
    spouse = pgs[0]

    if pgs[1]:
        if spouse and data[spouse]["alive"] == True:
            data[spouse]["heritance"] += heritance/4
            heritance = heritance - data[spouse]["heritance"]
        for i in pgs[1]:
            data[i]["heritance"] += heritance / len(pgs[1]) 
            if data[i]["alive"]==False:
                share(data,i)

    elif pgs[2]:
        if spouse and data[spouse]["alive"] == True:
            data[spouse]["heritance"] += heritance/2
            heritance = heritance - data[spouse]["heritance"]
        for i in pgs[2]:
            data[i]["heritance"] += heritance / len(pgs[2]) 
            if data[i]["alive"]==False:
                share(data,i)
    elif pgs[3]:
        if spouse and data[spouse]["alive"] == True:
            data[spouse]["heritance"] += 3*heritance/4
            heritance = heritance - data[spouse]["heritance"]
        for i in pgs[3]:
            data[i]["heritance"] += heritance / len(pgs[3]) 
            if data[i]["alive"]==False:
                share(data,i)
    else:
        if spouse and data[spouse]["alive"] == True:
            data[spouse]["heritance"]= heritance
    data[person]["heritance"]= 0

    result=[]   

    for key in data:
        if data[key]["heritance"] > 0:
            result.append((key,data[key]["heritance"]))

    return result


def create_data(Descriptions):
    data=dict()
    for j in range(len(Descriptions)):
        lst = Descriptions[j].split()
        for i in range(1,len(lst)):
            if not(lst[i] in data):
                data[lst[i]] = create_person()
        
        if lst[0] == "MARRIED":
            data[lst[1]]["married"] = lst[2]
            data[lst[2]]["married"] = lst[1]

        elif lst[0] == "CHILD":
    
            for k in range(3,len(lst)):
                data[lst[1]]["children"].append(lst[k])
                data[lst[2]]["children"].append(lst[k])
                data[lst[k]]["parents"].append(lst[1])
                data[lst[k]]["parents"].append(lst[2])
        
        elif lst[0] == "DEPARTED":
            data[lst[1]]["alive"] = False

        elif lst[0] =="DECEASED":
            data[lst[1]]["alive"] = False
            data[lst[1]]["heritance"] = float(lst[2])
            person = lst[1]
            heritance = data[lst[1]]["heritance"]
            data.pop(lst[-1],None)
    return [data,[person,heritance]]

def create_pgs(data,person):
    spouse = data[person]["married"]
    pg_1=[]
    pg_2=[]
    pg_3=[]
    for i in data[person]["children"]:
        if(data[i]["alive"]==True or does_have_descendants(data,i)):
            pg_1.append(i)

    for j in data[person]["parents"]:        
        if(data[j]["alive"]==True or does_have_descendants(data,j)):
            pg_2.append(j)

        for k in data[j]["parents"]:
            if(data[k]["alive"]==True or does_have_descendants(data,k)):
                pg_3.append(k)
    
    return [spouse,pg_1,pg_2,pg_3]

def share(data,person):
    if not data[person]["children"]:
        return
    heritance = data[person]["heritance"]
    flag = False
    a=[]
    for children in  data[person]["children"]:
        if data[children]["alive"]==False and not (does_have_descendants(data,children)):
            a.append(children)        
    for i in a:
        data[person]["children"].remove(i)
    
    n=len( data[person]["children"])
    
    for children in  data[person]["children"]:
       
        data[children]["heritance"] += heritance/n
        
        if data[children]["alive"] == False :
            share(data,children)
        
        data[person]["heritance"] = 0
    

def create_person():
    my_dict={"alive":True,"married":[],"children":[],"parents":[],"heritance":0.}
    return my_dict

def does_have_descendants(data,person):
    if not data[person]["children"]:
        return False

    flag = False
    
    for children in data[person]["children"]:
        if data[children]["alive"] == True or does_have_descendants(data,children):
            flag=True
            break
    
    return flag

print(inheritance(
["MARRIED ahmet ayse",
"CHILD ayse ahmet ali",
"MARRIED ali fatma",
"CHILD fatma ali emrah",
"DEPARTED ali",
"DEPARTED fatma",
"DECEASED emrah 100"

]
))