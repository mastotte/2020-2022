#Bag Tags
import tkinter as tk
root = tk.Tk()
canvas1 = tk.Canvas(root, width = 300, height = 300)
canvas1.pack()
#----------Helper Functions----------
def sortScores(val):
    v = val.split(",")
    return int(v[2])
def main():
    label1 = tk.Label(root, text= '', fg='blue', font=('helvetica', 12, 'bold'))
    canvas1.create_window(150, 200, window=label1)
    #----------Importing Data----------
    members = []
    players = []
    tags = []
    f = open("members.txt","r")
    members = f.readlines()
    f.close()

    f = open("players.txt","r")
    players = f.readlines()
    f.close()
    #----------Identifying Tags in Play----------
    for p in players:
        ply = p.split(",")
        for m in members:
            mem = m.split(",")
            if ply[0] == mem[0]:
                tags.append(int(mem[1]))
    #----------Sorting Scores and Assigning Tags----------
    players.sort(key=sortScores)
    tags.sort()
    print("TAG NUMBERS\n")
    for (p,t) in zip(players,tags):
        count = 0
        for m in members:
            ply = p.split(",")
            mem = m.split(",")
            #print(p)
            #print(m)
            if ply[0] == mem[0]:
                #mem[1] = t

                members[count] = mem[0]+","+str(t)+"\n"
                break
            count+=1
        print(t,end="")
        print(": ",end="")
        print(p,end="")
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
    for p in players:
        ply = p.split(",")
        if ply[1] not in divisions:
            divisions.append(ply[1])
            standings.append([])
    # fill standings
    for p in players:
        ply = p.split(",")
        for i in range(0, len(divisions)):
            if ply[1] == divisions[i]:
                standings[i].append(p)
    # sort standings
    for i in range(0, len(standings)):
        standings[i].sort(key=sortScores)
    # output scores by division
    for i in range(0, len(divisions)):
        print("\n"+divisions[i])
        for j in range(0,len(standings[i])):
            print(standings[i][j],end = "")
    

    


            




button1 = tk.Button(text='Click Me', command=main, bg='brown',fg='white')
canvas1.create_window(150, 150, window=button1)

root.mainloop()
