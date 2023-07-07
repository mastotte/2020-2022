Table of Contents

SCHOOLWORK:

1 and 101(pt2) -
My work from CSE101 

12-
My work from CSE12 (Computer Systems/Assembly Language)

13-
My work from CSE13s (Computer Systems and C Programming)

PERSONAL PROJECTS:

Quordle- A twist to the NYT's "Wordle", "Quordle" makes the user solve four words 
at once. With feedback of guess results from the user, this program will produce the
best guesses to solve the Quordle.

Sol- Sol is a game-scoring interface for one of my
favorite games, Multitaire. The game involves multiple players, each with their own decks, playing solitaire with a communal foundations. A player's score is represented
by (player's cards remaining) - (average cards remaining of all players in game). I call this 
adjusted player score their "Par" score.

Program Features:
-Computer generated round schedule for up to 100 players, with games of 2-7 players. In cases
of remainders, e.g. 3 players with 2 per game, each player will sit out as close to an even amount of times as possible.
-Scoreboard interface with standings, pars, un-adjusted scores, and round schedule
-5 save files
-User friendly input prompts

dg: A program I made for my interest in fantasy disc golf, which is the same thing as a fantasy football week-to-week auction league. Participants have a total of 6000 points to spend on 4 men and 2 women. Players are assigned a $ value in fantasy football auction leagues. In disc golf, they cost what their PDGA (Professional Disc Golf Association) rating is. I use regular expressions to parse tournament data to find 2 things: players who have played well recently, and players who have played well at each specific event in the past. If a player has excelled at the upcoming event in the past, and they have been playing well recently, then they are a good pick. 

Interpreting the data in out.txt:

[Player Name]:  [Points above Rating]
James Beckner: 39
This means that at this event, James Beckner played an average of 39 points above his rating. (good)
A negative number means they played below their rating. (bad)


SECTIONS:

1.) Tournament Data from this current year

Generally, each tournament will look like this:
<blank line>
[Tournament Name]
[Men's Player Name]:  [Points above Rating]
[Men's Player Name]:  [Points above Rating]
[Men's Player Name]:  [Points above Rating]
...
<blank line>
[Women's Player Name]:  [Points above Rating]
[Women's Player Name]:  [Points above Rating]
[Women's Player Name]:  [Points above Rating]

2.) TEMP MPO (men) and TEMP FPO (women) 
"Hottest" and "Coldest" are referring to how well a player is playing recently. Hot = good, Cold = bad

3.) Event History MPO
Men's Tournament data from 2021 and 2022.

4.) Event History FPO
Women's Tournament data from 2021 and 2022.

BagTags: Weekly bag tag calculations for the Oak Grove Disc Golf Club. Tag numbers are automatically updated in database, and the need for the physical tag is removed. This is helpful because players lose or forget their bag tags very frequently. Also, calculating tag results usually takes up to 30 minutes after the event is finished, and now it can be done instantly.




