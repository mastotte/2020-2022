#Bag Tags
#import os
import tkinter as tk
root = tk.Tk()
canvas1 = tk.Canvas(root, width = 300, height = 300)
canvas1.pack()

#print(os.getcwd())
#python -m PyInstaller bagtags.py
#----------Helper Functions----------
def sortScores(val):
    #v = val.split(",")
    return int(val[3])

def formatName(s):
    s = s.replace("\""," ")
    s = s.strip()
    return s

def formatInput(players):
    i = 0
    for p in players:
        ply = p.split(",")
        ply[2] = formatName(ply[2])
        if(ply[1] == "DNF"):
            ply[3] = 999
        if(ply[1] == "DUP"):
            del players[i]
        else:
            players[i] = ply[:4]
        i+=1

def listSearch(list,val,key):
    for item in list:
        mem = item.split(",")
        #print("Item[key]:"+mem[key])
        #print("Val:"+val)
        if(mem[key]==val):
            return mem
        
    return -1 

def removeFPO(players):
    
    dels = 1
    while dels != 0:
        dels = 0
        i = 0
        for p in players:
            if p[0][0] == "F":
                dels+=1
                del players[i]
            i+=1


def main():
    label1 = tk.Label(root, text= '', fg='blue', font=('helvetica', 12, 'bold'))
    canvas1.create_window(150, 200, window=label1)
    #----------Importing Data----------
    members = []
    players = []
    tags = []
    f = open("members.txt","r",encoding = "utf-8")
    members = f.readlines()
    #print(members)
    f.close()

    f = open("players.txt","r",encoding = "utf-8")
    players = f.readlines()
    
    FPO_players = []
    FPO_tags = []
    
    del players[0]

    formatInput(players)
    all_players = players.copy()
    f.close()
    #----------Identifying Tags in Play----------
    i = 0
    ret = False
    for p in players:
        found = False
        for m in members:
            mem = m.split(",")
            if p[2] == mem[0]:
                if p[0][0] == "F":
                    FPO_players.append(p)
                    FPO_tags.append(int(mem[1]))
                    #del players[i]
                else:
                    tags.append(int(mem[1]))
                found = True
        if(found == False):
            print(p[2]+" was not found in members.txt. Check for typos.")
            ret = True
        i+=1
    if(ret == True):
        return
    removeFPO(players)   
    #----------Sorting Scores and Assigning Tags----------
    players.sort(key=sortScores)
    FPO_players.sort(key=sortScores)
    # sorting tied players (tiebreakers)
    swaps = 1
    while(swaps != 0):
        swaps = 0
        for i in range(1,len(players)):
            if(players[i][3] == players[i-1][3]):
                m1 = listSearch(members,players[i-1][2],0)
                m2 = listSearch(members,players[i][2],0)
                if(m1[1] > m2[1]):
                    players[i],players[i-1] = players[i-1],players[i]
                    swaps += 1
    # Now for FPO
    swaps = 1
    while(swaps != 0):
        swaps = 0
        for i in range(1,len(FPO_players)):
            if(FPO_players[i][3] == FPO_players[i-1][3]):
                m1 = listSearch(members,FPO_players[i-1][2],0)
                m2 = listSearch(members,FPO_players[i][2],0)
                if(m1[1] > m2[1]):
                    FPO_players[i],FPO_players[i-1] = FPO_players[i-1],FPO_players[i]
                    swaps += 1
    tags.sort()
    FPO_tags.sort()
    #print(tags)
    #print(players)
    
    print("MPO TAGS\n")
    
    for (p,t) in zip(players,tags):
        count = 0
        #print("Searching: "+p[2])
        for m in members:
            #ply = p.split(",")
            mem = m.split(",")
            #print(p)
            #print(m)
            if p[2] == mem[0]:
                #mem[1] = t
                members[count] = mem[0]+","+str(t)+"\n"
                #print("mem[count]="+members[count])
                break
            count+=1
        print(t,end="")
        print(": ",end="")
        print(p[2])

    # Now for FPO
    print("\nFPO TAGS\n")
    for (p,t) in zip(FPO_players,FPO_tags):
        count = 0
        #print("Searching: "+p[2])
        for m in members:
            #ply = p.split(",")
            mem = m.split(",")
            #print(p)
            #print(m)
            if p[2] == mem[0]:
                #mem[1] = t
                members[count] = mem[0]+","+str(t)+"\n"
                #print("mem[count]="+members[count])
                break
            count+=1
        print(t,end="")
        print(": ",end="")
        print(p[2])
    #----------Sorting Members List----------
    members.sort()
    f = open("members.txt","w")
    for m in members:
        f.write(m)
    f.close()
    #----------Making Divisions----------
    divisions = []
    standings = []
    i = 0
    print("\nDIVISION STANDINGS")
    for p in all_players:
        #ply = p.split(",")
        if p[0] not in divisions:
            divisions.append(p[0])
            standings.append([])
    # fill standings
    for p in all_players:
        #ply = p.split(",")
        for i in range(0, len(divisions)):
            if p[0] == divisions[i]:
                standings[i].append(p)
    # sort standings
    for i in range(0, len(standings)):
        standings[i].sort(key=sortScores)
    # output scores by division
    for i in range(0, len(divisions)):
        print("\n"+divisions[i])
        for j in range(0,len(standings[i])):
            #print(standings[i][j])
            print(standings[i][j][1],end = ". ")
            print(standings[i][j][2],end = ", ")
            print(standings[i][j][3])


button1 = tk.Button(text='Click Me', command=main, bg='brown',fg='white')
canvas1.create_window(150, 150, window=button1)

root.mainloop()
