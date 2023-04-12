#include <iostream>
#include <regex>
#include <string>
#include <bits/stdc++.h>
using namespace std;
// Create array of names, read from 'scores.txt'
// Players[0] = Player Name
// Stats[0][0] = 0th Player Rating 
/*

1\t1190.00\tCalvin Heimburg\t45971\t1041\t-31\t57\t1029\t51\t1063\t50\t1062\t53\t1047\t211\t$7,500
1. Place
2. Tour Points
3. Player Name
4. PDGA#
5. PDGA Rating
6. Total Score
7. R1 Score
8. R1 Rating
9. R2 Score
10. R2 Rating
11. R3 Score
12. R3 Rating
13. R4 Score
14. R4 Rating
15. Total Score
16. Winnings

1. Las Vegas Challenge
2. WACO
3. The Open at Austin
4. Texas State Disc Golf Championships
5. Music City Open
6. Blue Ridge Championship
7. Champions Cup
8. Jonesboro Open
9. OTB Open
10. Beaver State Fling
11. Cascade Challenge
12. Zoo Town Open
13. Dynamic Discs Open
14. Des Moines Challenge
15. Kansas City Wide Open
16. PCS Open
17. European Open
18. Mid America Open
19. Ledgestone Open
20. Idlewild
21. Great Lakes Open
22. Jim Palmeri's AFDO 
23. PDGA Worlds
24. MVP Open

*/
// returns player's index, or next open index if reached end
int determine_event(string text){
    if(text == "Las Vegas Challenge"){
        return 1;
    }else if(text == "WACO"){
        return 2;
    }else if(text == "The Open at Austin"){
        return 3;
    }else if(text == "Texas State Disc Golf Championships"){
        return 4;
    }else if(text == "Music City Open"){
        return 5;
    }else if(text == "Blue Ridge Championship"){
        return 6;
    }else if(text == "Champions Cup"){
        return 7;
    }else if(text == "Jonesboro Open"){
        return 8;
    }else if(text == "OTB Open"){
        return 9;
    }else if(text == "Beaver State Fling"){
        return 10;
    }else if(text == "Cascade Challenge"){
        return 11;
    }else if(text == "Zoo Town Open"){
        return 12;
    }else if(text == "Dynamic Discs Open"){
        return 13;
    }else if(text == "Des Moines Challenge"){
        return 14;
    }else if(text == "Kansas City Wide Open"){
        return 15;
    }else if(text == "PCS Open"){
        return 16;
    }else if(text == "European Open"){
        return 17;
    }else if(text == "Mid America Open"){
        return 18;
    }else if(text == "Ledgestone Open"){
        return 19;
    }else if(text == "Idlewild"){
        return 20;
    }else if(text == "Great Lakes Open"){
        return 21;
    }else if(text == "Jim Palmeri's AFDO "){
        return 22;
    }else if(text == "PDGA Worlds"){
        return 23;
    }else if(text == "MVP Open"){
        return 24;
    }else{
        return 24;
    }
}
int calc_average(smatch matches, int rounds){
    int avg = 0;
    switch(rounds){
        case 1:
        avg = stoi(matches[8]);
        avg = avg/1;
        break;
        case 2:
        avg = stoi(matches[8]) + stoi(matches[10]);
        avg = avg/2;
        break;
        case 3:
        avg = stoi(matches[8]) + stoi(matches[10]) + stoi(matches[12]);
        avg = avg/3;
        break;
        case 4:
        avg = stoi(matches[8]) + stoi(matches[10]) + stoi(matches[12]) + stoi(matches[14]);
        avg = avg/4;
        break;
        case 5:
        avg = stoi(matches[8]) + stoi(matches[10]) + stoi(matches[12]) + stoi(matches[14]) + stoi(matches[16]);
        avg = avg/5;
        break;
        case 6:
        avg = stoi(matches[8]) + stoi(matches[10]) + stoi(matches[12]) + stoi(matches[14]) + stoi(matches[16]) + stoi(matches[18]);
        avg = avg/6;
        break;
    }
    return avg;
}
int player_index(string Players[100], string name){
    for(int i = 0; i < 1000; i++){
        if(Players[i].length() == 0){
            return i;
        }
        
        if(Players[i] == name){
            return i;
        }
    }
    return -1;
}
// Outputs the 5 best Overperformers at given event
void print_event_best(string Players[100], int Stats[100][26], int event){
    int names[5] = {0};
    int scores[5] = {0};
    int max_index = -1;
    int max = 0;
    for(int i = 0; i < 1000; i++){
        if(Stats[i][event] < max){
            // find highest
            max = -999;
            for(int j = 0; j < 5; j++){
                if(max < scores[j]){
                    max = scores[j];
                    max_index = j;
                }
            }
            scores[max_index] = Stats[i][event];
            names[max_index] = i;
        }
    }
    for(int i = 0; i < 5; i++){
        cout<<Players[names[i]]<<": "<<scores[i]<<endl;
    }
}
// 

int main() {
    string Players[100] = {""};
    int Stats2023[100][26] = {0};
    //int Stats2022[1000][26] = {0};
    smatch matches;
    regex DNF(R"((\d+)\t0.00\t([^\t]+))");
    /*regex pattern_1round$(R"((\d+)\t([\d.]+)\t([^\t]+)\t(\d+)\t(\d+)\t(-?\d+)\t(\d+)\t(\d+)\t(\d+)\t(\$[\d,]+))");
    regex pattern_2round$(R"((\d+)\t([\d.]+)\t([^\t]+)\t(\d+)\t(\d+)\t(-?\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\$[\d,]+))");
    regex pattern_3round$(R"((\d+)\t([\d.]+)\t([^\t]+)\t(\d+)\t(\d+)\t(-?\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\$[\d,]+))");
    regex pattern_4round$(R"((\d+)\t([\d.]+)\t([^\t]+)\t(\d+)\t(\d+)\t(-?\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\$[\d,]+))");
    regex pattern_5round$(R"((\d+)\t([\d.]+)\t([^\t]+)\t(\d+)\t(\d+)\t(-?\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\$[\d,]+))");
    regex pattern_6round$(R"((\d+)\t([\d.]+)\t([^\t]+)\t(\d+)\t(\d+)\t(-?\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\$[\d,]+))");*/
    regex pattern_1round(R"(^(\d+)\t([\d\.]+)\t([^\t]+)\t(\d+)\t(\d+)\t(-?\d+)\t(\d+)\t(\d+)\t(\d+))");
    regex pattern_2round(R"(^(\d+)\t([\d\.]+)\t([^\t]+)\t(\d+)\t(\d+)\t(-?\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+))");
    regex pattern_3round(R"(^(\d+)\t([\d\.]+)\t([^\t]+)\t(\d+)\t(\d+)\t(-?\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+))");
    regex pattern_4round(R"(^(\d+)\t([\d\.]+)\t([^\t]+)\t(\d+)\t(\d+)\t(-?\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+))");
    regex pattern_5round(R"(^(\d+)\t([\d\.]+)\t([^\t]+)\t(\d+)\t(\d+)\t(-?\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+))");
    regex pattern_6round(R"(^(\d+)\t([\d\.]+)\t([^\t]+)\t(\d+)\t(\d+)\t(-?\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+))");
    // Import Data
    ifstream in ("2023.txt");
    cout<<"check 2"<<endl;
    int event = 1;
    int rounds = 0;
    while(!in.eof()){
        string text;
        getline(in,text);
        cout<<"Text 1: "<<text<<endl;
        if(text.length() == 0){ // blank newline?
            // it's a new event
            getline(in,text);
            event = determine_event(text);
            cout<<"Event: "<<text<<endl;
        }
        else if(text.length() == 1){
            rounds = stoi(text);
            cout<<"Rounds: "<<rounds<<endl;
        }
        else if(regex_match(text, matches, DNF)){ 
            // getting rid of DNF finishes
            // -ignore
        }else{
            bool x = false;
            cout<<"Text 2: "<<text<<endl;
            if(rounds == 6){
                x = regex_search(text, matches, pattern_6round);
                if(!x){
                    rounds = 5;
                    x =regex_search(text, matches, pattern_5round);
                }
                cout<<"6 round called"<<endl;
            }else if(rounds == 5){
                x =regex_search(text, matches, pattern_5round);
                if(!x){
                    rounds = 4;
                    x =regex_search(text, matches, pattern_4round);
                }
                cout<<"5 round called"<<endl;
            }else if(rounds == 4){
                x =regex_search(text, matches, pattern_4round);
                if(!x){
                    rounds = 3;
                    x =regex_search(text, matches, pattern_3round);
                }
                cout<<"4 round called"<<endl;
            }else if(rounds == 3){
                x =regex_search(text, matches, pattern_3round);
                if(!x){
                    rounds = 2;
                    x =regex_search(text, matches, pattern_2round);
                }
                cout<<"3 round called"<<endl;
            }else if(rounds == 2){
                x =regex_search(text, matches, pattern_2round);
                if(!x){
                    rounds = 1;
                    x =regex_search(text, matches, pattern_1round);
                }
                cout<<"2 round called"<<endl;
            }else if(rounds == 1){
                x =regex_search(text, matches, pattern_1round);
                cout<<"1 round called"<<endl;
            }else{
                
                cout<<"NO REGEX FOUND"<<endl;
            }
            if(x == true){
                cout<<"x is true"<<endl;
            }else{
                cout<<"x is false"<<endl;
            }
            int index = player_index(Players, matches[3]);
            Players[index] = matches[3]; // write name to index, even if it already exists
            cout<<"check 2"<<endl;
            int avg = calc_average(matches, rounds);
            cout<<"check 3"<<endl;
            Stats2023[index][event] = stoi(matches[5]) - avg;
            cout<<matches[3]<<" "<<avg<<endl;
        }
    }
    cout<<Stats2023[0][0];
    return 0;
}
