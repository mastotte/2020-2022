import random
import Game
import Scoreboard
SEED = 2022

def scores_input(players, round, isTest, names):
    in_choice = 0
    if not isTest and round > 1:
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
        BUFSIZE = (10 * round) + 5
        for i in range(1, players + 1):
            buf = f.readline().strip()
            if not isTest:
                print("\n")
                print(f"{names[i - 1][0]}{names[i - 1][1]}'s score: ", end="")
                y = int(input())
            else:
                y = 5
            f2.write(f"{buf}\t{y}\n")

        if not isTest:
            print("\n0: Yes\n1: No\nFinalize Scores?")
            x = int(input())
            print("\n\n\n\n")
        else:
            x = 0

        if x == 1:
            scores_input(players, round, isTest, p, names)

    f.close()
    f2.close()
    return in_choice == 1

def print_scores(BUFSIZE, BUF2SIZE):
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
    players = 0
    rounds = 0
    out = None
    print("\n-- Main Menu --")
    print("0: New Game\n1: Load Saved Game")
    out = int(input())

    if out == 1:
        return out

    print("How many players?")
    players = int(input())

    print("How many rounds?")
    rounds = int(input())

    while out not in range(2, 8):
        print("\n-- Game Selection --")
        print("2: Double\n3: Triple\n4: Quadruple\n5: Pentuple\n6: Hextuple\n7: Septuple\n0: Exit")
        out = int(input())
        if out == 0:
            break

    return (out, players, rounds)

def displaySaveList():
    with open("GameFiles/saveList", "r") as save_list:
        for line in save_list:
            if line[3] != '_':
                line = line.replace('_', ' ')
            print(line, end='')

def loadGame(players, rounds, ppg, rounds_played, names):
    saveslot = 0
    save = None
    f2 = open("GameFiles/f2", "w")
    s1 = open("GameFiles/scoreboard", "w")
    s2 = open("GameFiles/scoreboard2", "w")
    
    displaySaveList()
    print("\nEnter a save slot: ")
    saveslot = int(input())

    save_file_map = {
        1: "GameFiles/save1",
        2: "GameFiles/save2",
        3: "GameFiles/save3",
        4: "GameFiles/save4",
    }
    save = open(save_file_map.get(saveslot, "GameFiles/save5"), "r")

    line = save.readline()  # first line
    buf_small = save.readline().strip()  # players
    players[0] = int(buf_small)
    f2.write(f"{players[0]}\n")
    print(f"{players[0]} Players buf:({buf_small})")

    line = save.readline()  # next line
    buf_small = save.readline().strip()  # rounds
    rounds[0] = int(buf_small)
    f2.write(f"{rounds[0]}\n")
    print(f"{rounds[0]} rounds buf:({buf_small})")

    line = save.readline()  # next line
    buf_small = save.readline().strip()  # ppg
    ppg[0] = int(buf_small)
    f2.write(f"{ppg[0]}\n")
    print(f"{ppg[0]} ppg buf:({buf_small})")

    line = save.readline()  # next line
    buf_small = save.readline().strip()  # rounds played
    rounds_played[0] = int(buf_small)
    print(f"{rounds_played[0]} rounds played buf:({buf_small})")
    line = save.readline()

    BUFSIZE = (10 * rounds[0]) + 3
    BUF2 = (35 * players[0])
    if BUF2 > BUFSIZE:
        BUFSIZE = BUF2
    buf = [''] * BUFSIZE

    print("------------SCHEDULE----------")
    for i in range(rounds[0]):
        buf[i] = save.readline()
        f2.write(buf[i])
        print(buf[i], end='')

    print("\n------------SCOREBOARD----------")
    for i in range(players[0]):
        buf[i] = save.readline()
        s1.write(buf[i])
        s2.write(buf[i])
        print(buf[i], end='')

    print("\n------------PLAYERS------------")
    buf = save.readline()
    for i in range(players[0]):
        for j in range(2):
            names[i][j] = buf[j + (i * 2)]
            print(buf[j + (i * 2)], end='')
        print()

    save.close()
    f2.close()
    s1.close()
    s2.close()
    return saveslot

def createGame():
    saveslot = 0
    first_input = True
    BUFSIZE = 20
    buf = ""
    
    displaySaveList()  # Assuming this function exists
    saveslot = int(input("Enter a save slot: "))
    
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
    
    return saveslot

def saveGame(players, rounds, ppg, rounds_played, names, saveslot):
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

def main():
    players = rounds = ppg = rounds_played = saveslot = exit = 0
    ppg = rounds_played = 0
    
    ppg, players, rounds = getInput()  # Assuming this function exists
    print(players, " players\n")
    names = [['' for _ in range(2)] for _ in range(players)]
    
    if ppg > 1:
        print("\nEnter Each Player's First and Last Initials")
        for i in range(players):
            print(f"\nPlayer {i+1}: ")
            name = input()
            for j in range(len(name)):
                names[i][j] = name[j]
        
        Game.game(players, rounds, 2000, ppg, names)  # Assuming this function exists
        saveslot = createGame()
        makeTemplate(players)  # Assuming this function exists
        reset()  # Assuming this function exists
    else:
        saveslot = loadGame(players, rounds, ppg, rounds_played, names)  # Assuming this function exists
        Scoreboard.scoreBoard(rounds_played, players, ppg, names)  # Assuming this function exists
        print_scores(10*players, 8*rounds)  # Assuming this function exists
    
    for i in range(rounds_played + 1, rounds + 1):
        print_scores(10*players, 8*rounds)
        exit = scores_input(players, i, False, names)  # Assuming this function exists
        if exit == 0 or i == 1:
            Scoreboard.scoreBoard(i, players, ppg, names)
            print_scores(10*players, 8*rounds)
        else:
            break
    
        saveGame(players, rounds, ppg, i-1, names, saveslot)
        print("Game Saved.")

if __name__ == "__main__":
    main()
