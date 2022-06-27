//
//
//	Game.h
//

// Runs simulation to create schedules, outputs to "out"
void game(int players, int rounds, int TESTSIZE, bool isTest, FILE* p, int ppg);

// Calculates Standard Deviation, used to determine most balanced schedule.
float calculateSD(float data[], float p, int matches_call);

// Outputs the most balanced schedule to "best" and other information to "f2" for 
// Scoreboard.c to use.
void output(int best_round, int n, int rounds, FILE* p, int ppg);
