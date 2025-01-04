import math


# NOTES:
#
#   Need to print schedule to f2
#
#
#
#
def scoreBoard(rounds, players, ppg, names):
    # Open appropriate score file based on round number
    if rounds % 2 == 1:
        SCORES = open("GameFiles/scoreboard", "r")
    else:
        SCORES = open("GameFiles/scoreboard2", "r")
    
    infile = open("GameFiles/f2", "r")
    
    # Read initial parameters
    p = infile.readline()
    r = infile.readline()
    ppG = infile.readline()
    
    BUFSIZE = 35 * players
    BUFSCORES = (10 * rounds) + 5
    
    # Initialize scores and pars arrays
    pars = [[0.0] * (rounds + 1) for _ in range(players + 1)]
    scores = [[0] * (rounds + 1) for _ in range(players + 1)]
    
    # Read scores
    for i in range(1, players + 1):
        buf_scores = SCORES.readline()
        score_values = buf_scores.split()
        print("Score Values: ",score_values)
        for j in range(1, rounds + 1):
            scores[i][j] = int(score_values[j])

    # Process matches
    for j in range(1, rounds + 1):
        buf = infile.readline().strip()
        print("BUF: ",buf)
        matches = buf.split('-')
        
        for i in range(players // ppg):
            # Initialize player scores
            p1 = p2 = p3 = p4 = p5 = p6 = p7 = 0
            s1 = s2 = s3 = s4 = s5 = s6 = s7 = 0.0
            
            # Parse player numbers
            print("Matches: ",matches)
            players_in_match = matches[i].split(' vs ')        # USED TO BE '{tab}vs{tab}', changed to '{space}vs{space}'
            p1 = int(players_in_match[0])
            p2 = int(players_in_match[1])
            if ppg > 2 and len(players_in_match) > 2:
                p3 = int(players_in_match[2])
            if ppg > 3 and len(players_in_match) > 3:
                p4 = int(players_in_match[3])
            if ppg > 4 and len(players_in_match) > 4:
                p5 = int(players_in_match[4])
            if ppg > 5 and len(players_in_match) > 5:
                p6 = int(players_in_match[5])
            if ppg > 6 and len(players_in_match) > 6:
                p7 = int(players_in_match[6])
            
            # Get scores
            s1 = scores[p1][j]
            s2 = scores[p2][j]
            if ppg > 2: s3 = scores[p3][j]
            if ppg > 3: s4 = scores[p4][j]
            if ppg > 4: s5 = scores[p5][j]
            if ppg > 5: s6 = scores[p6][j]
            if ppg > 6: s7 = scores[p7][j]
            
            # Calculate average
            sum_scores = s1 + s2
            if ppg > 2: sum_scores += s3
            if ppg > 3: sum_scores += s4
            if ppg > 4: sum_scores += s5
            if ppg > 5: sum_scores += s6
            if ppg > 6: sum_scores += s7
            
            avg = sum_scores / ppg
            
            # Calculate pars
            pars[p1][j] = s1 - avg
            pars[p2][j] = s2 - avg
            if ppg > 2: pars[p3][j] = s3 - avg
            if ppg > 3: pars[p4][j] = s4 - avg
            if ppg > 4: pars[p5][j] = s5 - avg
            if ppg > 5: pars[p6][j] = s6 - avg
            if ppg > 6: pars[p7][j] = s7 - avg
    
    # Output results
    with open("GameFiles/scOut", "w") as sc_out:
        # Write scores
        sc_out.write("Scores")
        for i in range(1, players + 1):
            sc_out.write("\n")
            sc_out.write(f"{names[i-1][0]}{names[i-1][1]}:")
            for j in range(1, rounds + 1):
                score = scores[i][j]
                sc_out.write(f" {score:2d}")
        
        # Write pars
        sc_out.write("\n      \nPars")
        standings = [[0, 0, 0] for _ in range(players + 1)]
        for i in range(1, players + 1):
            sum_pars = 0.0
            sc_out.write("\n")
            sc_out.write(f"{names[i-1][0]}{names[i-1][1]}:")
            for j in range(1, rounds + 1):
                par = pars[i][j]
                sum_pars += par
                sc_out.write(f" {int(par):3d}")
            standings[i][1] = i
            standings[i][2] = sum_pars
        
        # Sort standings
        for i in range(1, players):
            for j in range(1, players - i + 1):
                if standings[j][2] > standings[j+1][2]:
                    standings[j], standings[j+1] = standings[j+1], standings[j]
        
        # Write standings
        sc_out.write("\n      \nStandings:")
        for i in range(1, players + 1):
            player_idx = int(standings[i][1]) - 1
            sc_out.write(f"\n{names[player_idx][0]}{names[player_idx][1]}: {standings[i][2]:.1f}")

