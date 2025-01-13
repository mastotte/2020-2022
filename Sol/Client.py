import random
import Game
import Scoreboard
import tkinter as tk
from enum import Enum
root = tk.Tk()
canvas1 = tk.Canvas(root, width = 1000, height = 1000)
canvas1.pack()
SEED = 2022
TEST = False
players = 0
ppg = 0                 
rounds = 0
saveslot = 0
rounds_played = 0
name_sample = ['AA','AB','AC','AD','AE','AF','AG','AH','AI','AJ','AK','AL']

names = name_sample
mode_options = ["Double", "Triple", "Quadruple", "Pentuple", "Hextuple", "Septuple"]
player_names_var = [tk.StringVar() for _ in range(100)]
player_names = ["" for _ in range(100)] 
players_var = tk.StringVar()
rounds_var = tk.StringVar()
game_mode_var = tk.StringVar()

class Mode(Enum):
    Double = 2
    Triple = 3
    Quadruple = 4
    Pentuple = 5
    Hextuple = 6
    Septuple = 7

# NOTES
#
# ALL terminal inputs will have to be replaced with GUI inputs
# LoadGame is in the process of being changed
# For future: save and display full names, not just initials


# PLAYER NAME INPUT screen still needs to be called after submit button is pushed,
# and it needs its own submit button to move on to the game. The submit button doesn't have
# to do anything, it just needs to move on to the next screen
# 




def scores_input(players, round, names):
    global TEST
    in_choice = 0
    if not TEST and round > 1:
        print("\n1: Exit\n2: Continue\n")
        in_choice = int(input())
        print("\n")

    random.seed(SEED)
    
    if round % 2 == 1:
        f = open("GameFiles/scoreboard2", "r")
        f2 = open("GameFiles/scoreboard", "w")
    else:
        f = open("GameFiles/scoreboard", "r")
        f2 = open("GameFiles/scoreboard2", "w")

    if in_choice != 1:
        for i in range(1, players + 1):
            buf = f.readline().strip()
            if not TEST:
                print("\n")
                print(f"{names[i - 1][0]}{names[i - 1][1]}'s score: ", end="")
                y = int(input())
            else:
                y = random.randint(1,52)
                print("RANDOM SCORE: ",y)
            f2.write(f"{buf}\t{y}\n")

        if not TEST:
            print("\n0: Yes\n1: No\nFinalize Scores?")
            x = int(input())
            print("\n\n\n\n")
        else:
            x = 0

        if x == 1:
            scores_input(players, round, names)

    f.close()
    f2.close()
    return in_choice == 1

def print_scores():
    f = open("GameFiles/best", "r")
    f2 = open("GameFiles/scOut", "r")
    buf = ""
    temp = ""
    buf2 = ""
    buf_end = False

    for _ in range(10):
        print("\n\n\n\n")

    while True:
        buf2 = f2.readline()
        if not buf2:
            break
        buf2 = buf2.strip()
        if not buf_end:
            buf2 = buf2.strip()
        if buf2:
            print(buf2)
        buf = f.readline()
        if not buf_end:
            print(" " * (50 - len(buf2)), end="")
        if temp != buf:
            print(buf, end="")
            temp = buf
        elif not buf_end:
            print("\n")
            buf_end = True

    while True:
        buf = f.readline()
        if not buf:
            break
        print(" " * 50, end="")
        print(buf, end="")
    
    print("\n")
    f.close()
    f2.close()

def makeTemplate(players):
    f = open("GameFiles/scoreboardTemplate", "w")
    for i in range(1, players + 1):
        f.write(f"{i}:\n")
    f.close()

def reset():
    f = open("GameFiles/scoreboardTemplate", "r")
    f2 = open("GameFiles/scoreboard2", "w")
    f3 = open("GameFiles/scoreboard", "w")
    f4 = open("GameFiles/scOut", "w")
    
    while True:
        buf = f.readline()
        if not buf:
            break
        f2.write(buf)

    f.close()
    f2.close()
    f3.close()
    f4.close()

def resetSaves():
    f = open("GameFiles/saveList", "w")
    f.write("1: ______________________________\n2: ______________________________\n3: ______________________________\n")
    f.write("4: ______________________________\n5: ______________________________\n")
    f.close()

def getInput():
    global players
    global rounds
    global ppg
    out = None
    print("\n-- Main Menu --")
    print("0: New Game\n1: Load Saved Game\n2: Testing Mode")
    out = int(input())

    if out == 1: 
        return out
    
    if out == 2: # ADDED OPTION 2 FOR TESTING
        global TEST
        players = 5
        rounds = 8
        ppg = 3
        TEST = True
        print("TEST: ",TEST)
        return  out # ppg, players, rounds

    print("How many players?")
    players = int(input())

    print("How many rounds?")
    rounds = int(input())

    ppg = 0
    while ppg not in range(2, 8):
        print("\n-- Game Selection --")
        print("2: Double\n3: Triple\n4: Quadruple\n5: Pentuple\n6: Hextuple\n7: Septuple\n0: Exit")
        ppg = int(input())

    return 0


def displaySaveList():
    with open("GameFiles/saveList", "r") as save_list:
        for line in save_list:
            if line[3] != '_':
                line = line.replace('_', ' ')
            print(line, end='')

def loadGame():
    global players
    global rounds
    global ppg
    global names
    global saveslot
    global rounds_played
    save = None
    f2 = open("GameFiles/f2", "w")
    s1 = open("GameFiles/scoreboard", "w")
    s2 = open("GameFiles/scoreboard2", "w")
    
    #displaySaveList()
    display_saves_window()      # this calls select_save_slot() which sets saveslot
    #print("\nEnter a save slot: ")
    #saveslot = int(input())

    save_file_map = {
        1: "GameFiles/save1",
        2: "GameFiles/save2",
        3: "GameFiles/save3",
        4: "GameFiles/save4",
    }
    save = open(save_file_map.get(saveslot, "GameFiles/save5"), "r")

    #----------------------------
    """i = 0
    while(i < 100):
        line = save.readline().strip()
        i += 1
        print(line)


    """
    #----------------------------
    line = save.readline().strip()  # first line
    print(line)
    buf_small = save.readline().strip()  # players 
    print(buf_small)
    players = int(buf_small[0])
    f2.write(f"{players}\n")
    #print(f"{players} Players buf:({buf_small})")

    buf_small = save.readline().strip()  # rounds
    print(buf_small)
    rounds = int(buf_small[0])
    f2.write(f"{rounds}\n")
    #print(f"{rounds} rounds buf:({buf_small})")

    buf_small = save.readline().strip()  # ppg
    print(buf_small)
    ppg = int(buf_small[0])
    f2.write(f"{ppg}\n")
    #print(f"{ppg} ppg buf:({buf_small})")

    buf_small = save.readline().strip()  # rounds played
    print(buf_small)
    rounds_played = int(buf_small[0])
    #print(f"{rounds_played} rounds played buf:({buf_small})")

    BUFSIZE = (10 * rounds) + 3
    BUF2 = (35 * players)
    if BUF2 > BUFSIZE:
        BUFSIZE = BUF2
    buf = [''] * BUFSIZE

    print("------------SCHEDULE----------")
    for i in range(rounds):
        buf[i] = save.readline()
        f2.write(buf[i])
        print(buf[i], end='')

    print("\n------------SCOREBOARD----------")
    for i in range(players):
        buf[i] = save.readline()
        s1.write(buf[i])
        s2.write(buf[i])
        print(buf[i], end='')

    print("\n------------PLAYERS------------")
    buf = save.readline()
    for i in range(players,2):
        names[i] = buf[i:i+1]
    print(buf)
    print("Names3: ",names)

    save.close()
    f2.close()
    s1.close()
    s2.close()

def createGame():
    global saveslot
    first_input = True
    BUFSIZE = 20
    buf = ""
    
    #displaySaveList()  
    display_saves_window()
    #saveslot = int(input("Enter a save slot: "))     
    
    with open("GameFiles/saveList", "r+") as saveList:
        saveList.seek(3 + (35 * (saveslot-1)))
        saveList.write("_" * 30) # write over any previous save
        print(saveList.tell())
        saveList.seek(saveList.tell() - 30)  # go back to start of line
        
        while first_input or len(buf) < 1 or len(buf) > 30:
            first_input = False
            print("\n(No spaces)\nName of save: ")
            buf = input()
            if len(buf) > 30:
                print("\nError: Save name too long. Must be under 30 characters.")
            else:
                print(f"Length: {len(buf)}   ")
                saveList.write(buf)
    


def saveGame(players, rounds, ppg, rounds_played, names):
    global saveslot
    BUFSIZE = (10 * rounds) + 5
    
    save_filename = f"GameFiles/save{saveslot}"
    with open(save_filename, "w") as f:
        f2_filename = "GameFiles/f2"
        f3_filename = "GameFiles/scoreboard" if rounds_played % 2 == 1 else "GameFiles/scoreboard2"
        
        with open(f2_filename, "r") as f2, open(f3_filename, "r") as f3:
            f.write(f"----- Save Slot {saveslot} -----\n")
            f.write(f"{players} Players\n{rounds} Rounds\n{ppg} Players Per Game\n{rounds_played} Rounds Played\n")
            
            # printing schedule
            # ignore first 3 lines of "f2"
            for _ in range(3):
                f2.readline()
            
            for line in f2:
                f.write(line)
            
            # printing scoreboard
            for i in range(players):
                print(f"Saved player {i+1}")
                line = f3.readline()
                f.write(line)
            
            # printing names
            for i in range(players):
                for j in range(2):
                    f.write(names[i][j])

def do_nothing():
    pass

def newgame_button():
    new_game_input_screen()
    print("\nEnter Each Player's First and Last Initials")
    for i in range(players):
        print(f"\nPlayer {i+1}: ")
        name = input()
        names[i] = name

    Game.game(players, rounds, 2000, ppg, names)  
    createGame()
    makeTemplate(players)  
    reset() 
    

def clear_frame():
    for widget in root.winfo_children():
        if widget != canvas1:
            widget.destroy()

def loadgame_button():
    clear_frame()
    loadGame()  
    Scoreboard.scoreBoard(rounds_played, players, ppg, names)  
    #print_scores(10*players, 8*rounds)
    print_scores() 
    pass

def select_save_slot(selection):
    global saveslot
    saveslot = selection
    clear_frame()

def display_saves_window():
    button1 = tk.Button(text='Save 1', command=lambda: select_save_slot(1), bg='brown',fg='white')
    button2 = tk.Button(text='Save 2', command=lambda: select_save_slot(2), bg='brown',fg='white')
    button3 = tk.Button(text='Save 3', command=lambda: select_save_slot(3), bg='brown',fg='white')
    button4 = tk.Button(text='Save 4', command=lambda: select_save_slot(4), bg='brown',fg='white')
    button5 = tk.Button(text='Save 5', command=lambda: select_save_slot(5), bg='brown',fg='white')

    canvas1.create_window(150, 150, window=button1)
    canvas1.create_window(150, 200, window=button2)
    canvas1.create_window(150, 250, window=button3)
    canvas1.create_window(150, 300, window=button4)
    canvas1.create_window(150, 350, window=button5)

def submit_button():
    global players
    global rounds
    global ppg
    players = int(players_var.get())
    rounds = int(rounds_var.get())
    mode = game_mode_var.get()
    ppg = Mode[mode].value

    print("submit button called\n")
    print(f"players: {players}, rounds: {rounds}, ppg: {ppg}\n")
    player_name_input_screen()
    pass

def new_game_input_screen():
    print("new game input screen called\n")
    clear_frame()
    global players_var
    global game_mode_var
    # if this doesn't work try including mode options as global variable
    players_label = tk.Label(root, text='Enter number of players:', fg='blue', font=('helvetica', 12, 'bold'))
    players_entry = tk.Entry(root, textvariable= players_var, font=('helvetica', 12, 'bold'))
    rounds_label = tk.Label(root, text='Enter number of rounds:', fg='blue', font=('helvetica', 12, 'bold'))
    rounds_entry = tk.Entry(root, textvariable= rounds_var, font=('helvetica', 12, 'bold'))

    game_mode_var.set("Double")
    dropdown = tk.OptionMenu(root, game_mode_var, *mode_options)
    

    # creating submit button
    sub_btn = tk.Button(root, text='Submit', command=submit_button, bg='brown', fg='white')
    canvas1.create_window(150, 150, window=players_label)
    canvas1.create_window(150, 200, window=players_entry)
    canvas1.create_window(150, 250, window=rounds_label)
    canvas1.create_window(150, 300, window=rounds_entry)
    canvas1.create_window(150, 350, window=dropdown)
    canvas1.create_window(150, 400, window=sub_btn)
    root.mainloop()

def submit_player_names():
    global player_names
    print("submit player names called\n")
    for i in range(players):
        player_names[i] = player_names_var[i].get()
    print(player_names)
    pass

def player_name_input_screen():
    global player_names
    print("player name input screen called\n")
    clear_frame()

    player_name_label = tk.Label(root, text='Enter player names:', fg='blue', font=('helvetica', 12, 'bold'))
    canvas1.create_window(150, 150, window=player_name_label)
    # pe stands for player entry
    for i in range(players):
        pe = tk.Entry(root, textvariable= player_names_var[i], font=('helvetica', 12, 'bold'))
        canvas1.create_window(150, 200 + (50 * i), window=pe)

    sub_btn = tk.Button(root, text='Submit', command=submit_player_names, bg='brown', fg='white')
    canvas1.create_window(150, 200 + (50 * players), window=sub_btn)



    
def main():
    #label1 = tk.Label(root, text= '', fg='blue', font=('helvetica', 12, 'bold'))
    #canvas1.create_window(150, 200, window=label1)
    button1 = tk.Button(text='New Game', command=newgame_button, bg='brown',fg='white')
    canvas1.create_window(150, 150, window=button1)

    button2 = tk.Button(text='Load Game', command=loadgame_button, bg='blue', fg='white')
    canvas1.create_window(150, 200, window=button2)

    button3 = tk.Button(text='Testing Mode', command=do_nothing, bg='green', fg='white')
    canvas1.create_window(150, 250, window=button3)


    exit = 0
    
    menu_select = getInput()  
    #menu_select = 0
    global TEST
    global names
    global rounds_played
    print(players, " players\n")
    
    if menu_select == 0:
        print("\nEnter Each Player's First and Last Initials")
        for i in range(players):
            print(f"\nPlayer {i+1}: ")
            name = input()
            names[i] = name

        Game.game(players, rounds, 2000, ppg, names)  
        createGame()
        makeTemplate(players)  
        reset()  
    elif menu_select == 1:
        loadGame()  
        Scoreboard.scoreBoard(rounds_played, players, ppg, names)  
        #print_scores(10*players, 8*rounds)
        print_scores()  
    elif menu_select == 2:
        print("MENU WORKING")
        names = name_sample[:players]
        Game.game(players, rounds, 2000, ppg, names)  
        createGame()
        makeTemplate(players)  
        reset() 

    
    for i in range(rounds_played + 1, rounds + 1):
        #print_scores(10*players, 8*rounds)
        print_scores() 
        exit = scores_input(players, i, names)  
        if exit == 0 or i == 1:
            Scoreboard.scoreBoard(i, players, ppg, names)
            #print_scores(10*players, 8*rounds)
            print_scores() 
        else:
            break
    
        saveGame(players, rounds, ppg, i-1, names)
        print("Game Saved.")
        
if __name__ == "__main__":
    main()
