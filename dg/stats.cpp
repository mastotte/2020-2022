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
    }else if(text == "Jim Palmeri's AFDO"){
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
int player_index(string Players[10000], string name){
    for(int i = 0; i < 10000; i++){
        if(Players[i].length() == 0){
            return i;
        }
        
        if(Players[i] == name){
            return i;
        }
    }
    return -1;
}
// Outputs the 20 best Overperformers at given event
void print_event_best(string Players[10000], int Stats[10000]){
    int names[20] = {0};
    for(int x = 0; x < 20; x++){
        names[x] = -1;
    }
    int scores[20] = {-999};
    int min_index = -1;
    int min = -999;
    int i = 0;
    while(Players[i] != ""){
        if(Stats[i] > min){
            // find lowest
            min = 999;
            for(int j = 0; j < 20; j++){
                if(min > scores[j]){
                    min = scores[j];
                    min_index = j;
                }
            }
            scores[min_index] = Stats[i];
            names[min_index] = i;
        }
        i++;
    }
    // bubble sort on list
    int swaps = 1;
    while(swaps != 0){
        swaps = 0;
        for(int k = 0; k < 20-1; k++){
            if(scores[k]<scores[k+1]){
                swap(scores[k],scores[k+1]);
                swap(names[k],names[k+1]);
                swaps++;
            }
        }
    } 
    if(scores[0] == 0 || scores[0] == -999){
        cout<<"Event Not Played"<<endl;
    }else{
        for(int n = 0; n < 20; n++){
            if(names[n]!=-1)
                cout<<Players[names[n]]<<": "<<scores[n]<<endl;
        }
    }
    cout<<endl;
}
//
void print_event_worst(string Players[10000], int Stats[10000]){
    int names[20] = {0};
    for(int x = 0; x < 20; x++){
        names[x] = -1;
    }
    int scores[20] = {999};
    int max_index = -1;
    int max = 999;
    int i = 0;
    while(Players[i] != ""){
        if(Stats[i] < max){
            // find lowest
            max = -999;
            for(int j = 0; j < 20; j++){
                if(max < scores[j]){
                    max = scores[j];
                    max_index = j;
                }
            }
            scores[max_index] = Stats[i];
            names[max_index] = i;
        }
        i++;
    }
    // bubble sort on list
    int swaps = 1;
    while(swaps != 0){
        swaps = 0;
        for(int k = 0; k < 20-1; k++){
            if(scores[k]<scores[k+1]){
                swap(scores[k],scores[k+1]);
                swap(names[k],names[k+1]);
                swaps++;
            }
        }
    } 
    if(scores[0] == 0 || scores[0] == -999){
        cout<<"Event Not Played"<<endl;
    }else{
        for(int n = 0; n < 20; n++){
            if(names[n]!=-1)
                cout<<Players[names[n]]<<": "<<scores[n]<<endl;
        }
    }
    cout<<endl;
}
// calculates the hottest and coldest players of the last 3 events
void calc_temp(string Players[10000],int Stats[26][10000], int event_count){
    int Heat[10000] = {0};
    int j = 0;
    int i = 0;
    int played = 0;
    int avg = 0;
    int sum = 0;
    while(Players[i] != ""){
        j = 0;
        sum = 0;
        played = 0;
        while(event_count - j > 0 && j < 4){
            if(Stats[event_count-j][i] != -999){
                sum += (Stats[event_count-j][i]);
                played++;
            }
            j++;
        }
        
        if(played < 2){ // not big enough sample size
            Heat[i] = 0;
        }else{
            avg = sum / played;
            Heat[i] = avg;
        }
        i++;
    }
    cout<<"Hottest:"<<endl;
    print_event_best(Players, Heat);
    cout<<"Coldest:"<<endl;
    print_event_worst(Players,Heat);
}
// calculates the best players at every event in the last 2 years
void event_best(string Players[10000],int Stats2021[26][10000],int Stats2022[26][10000],int Stats2023[26][10000], string events[26]){
    int event = 1;
    for(int k = 0; k < 26; k++){
        if(events[k] == "") break;
        int EventScore[10000] = {0};
        int i = 0;
        int played = 0;
        int avg = 0;
        int sum = 0;
        while(Players[i] != ""){
            sum = 0;
            played = 0;
            
            if(Stats2021[event][i] != -999){
                sum += (Stats2021[event][i]);
                played++;
            }
            if(Stats2022[event][i] != -999){
                sum += (Stats2022[event][i]);
                played++;
            }
            
            if(played < 2){ // must have played event both years
                EventScore[i] = 0;
            }else{
                avg = sum / played;
                EventScore[i] = avg;
            }
            i++;
        }
        cout<<"Best of '"<<events[event]<<"'"<<endl;
        print_event_best(Players, EventScore);
        event++;

    }
}

int compile_year(string Players[10000], int Stats[26][10000], string filename){
    smatch matches;
    regex DNF("DNF");
    /*regex pattern_1round$(R"((\d+)\t([\d.]+)\t([^\t]+)\t(\d+)\t(\d+)\t([+-]?[\d.E]+)\t(\d+)\t(\d+)\t(\d+)\t(\$[\d,]+))");
    regex pattern_2round$(R"((\d+)\t([\d.]+)\t([^\t]+)\t(\d+)\t(\d+)\t([+-]?[\d.E]+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\$[\d,]+))");
    regex pattern_3round$(R"((\d+)\t([\d.]+)\t([^\t]+)\t(\d+)\t(\d+)\t([+-]?[\d.E]+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\$[\d,]+))");
    regex pattern_4round$(R"((\d+)\t([\d.]+)\t([^\t]+)\t(\d+)\t(\d+)\t([+-]?[\d.E]+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\$[\d,]+))");
    regex pattern_5round$(R"((\d+)\t([\d.]+)\t([^\t]+)\t(\d+)\t(\d+)\t([+-]?[\d.E]+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\$[\d,]+))");
    regex pattern_6round$(R"((\d+)\t([\d.]+)\t([^\t]+)\t(\d+)\t(\d+)\t([+-]?[\d.E]+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\$[\d,]+))");*/
    regex pattern_1round(R"(^(\d+)\t([\d\.]*)\t([^\t]+)\t(\d*)\t(\d*)\t([+-]?[\d.E]+)\t(\d+)\t(\d+))");
    regex pattern_2round(R"(^(\d+)\t([\d\.]*)\t([^\t]+)\t(\d*)\t(\d*)\t([+-]?[\d.E]+)\t(\d+)\t(\d+)\t(\d+)\t(\d+))");
    regex pattern_3round(R"(^(\d+)\t([\d\.]*)\t([^\t]+)\t(\d*)\t(\d*)\t([+-]?[\d.E]+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+))");
    regex pattern_4round(R"(^(\d+)\t([\d\.]*)\t([^\t]+)\t(\d*)\t(\d*)\t([+-]?[\d.E]+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+))");
    regex pattern_5round(R"(^(\d+)\t([\d\.]*)\t([^\t]+)\t(\d*)\t(\d*)\t([+-]?[\d.E]+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+))");
    regex pattern_6round(R"(^(\d+)\t([\d\.]*)\t([^\t]+)\t(\d*)\t(\d*)\t([+-]?[\d.E]+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+)\t(\d+))");
    // Import Data
    ifstream in (filename);
    int event = 1;
    int rounds = 0;
    int event_count = 0;
    while(!in.eof()){
        string text;
        getline(in,text);
        //cout<<"Text: "<<text<<endl;
        if(text.length() == 0){ // blank newline?
            
            // it's a new event
            getline(in,text);
            event = determine_event(text);
            //cout<<"Event: "<<text<<endl;
            event_count++;
        }
        else if(text.length() == 1){
            rounds = stoi(text);
            if(rounds == 9){ // event not played yet
                event_count--;
                
            } 
            if(rounds == 8){ // event didn't exist in this year
                event_count--;
            }
            //cout<<"Rounds: "<<rounds<<endl;
        }
        else if(regex_search(text, DNF)){ 
            // getting rid of DNF finishes
            // -ignore
            //cout<<"DNF REACHED"<<endl;
        }else{
            bool x = false;
            if(rounds == 6){
                x = regex_search(text, matches, pattern_6round);
                if(x == false){
                    rounds = 5;
                    x =regex_search(text, matches, pattern_5round);
                }
            }else if(rounds == 5){
                x =regex_search(text, matches, pattern_5round);
                if(x == false){
                    rounds = 4;
                    x =regex_search(text, matches, pattern_4round);
                }
            }else if(rounds == 4){
                x =regex_search(text, matches, pattern_4round);
                if(x == false){
                    rounds = 3;
                    x =regex_search(text, matches, pattern_3round);
                }
            }else if(rounds == 3){
                x =regex_search(text, matches, pattern_3round);
                if(x == false){
                    rounds = 2;
                    x =regex_search(text, matches, pattern_2round);
                }
            }else if(rounds == 2){
                x =regex_search(text, matches, pattern_2round);
                if(x == false){
                    rounds = 1;
                    x =regex_search(text, matches, pattern_1round);
                }
            }else if(rounds == 1){
                x =regex_search(text, matches, pattern_1round);
            }else{
                
                //cout<<"NO REGEX FOUND"<<endl;
            }
            if(x == false){
                //cout<<"x is false"<<endl;
            }
            int index = player_index(Players, matches[3]);
            Players[index] = matches[3]; // write name to index, even if it already exists
            int avg = calc_average(matches, rounds);
            if(matches[5] != ""){
                Stats[event][index] =  avg - stoi(matches[5]);
            } 
        }
    }
    return event_count;
}
int main() {
    string Players[10000] = {""};
    string Players_FPO[10000] = {""};
    string events[26] = {"-","Las Vegas Challenge","WACO","The Open at Austin","Texas State Disc Golf Championships","Music City Open","Blue Ridge Championship","Champions Cup","Jonesboro Open","OTB Open","Beaver State Fling","Cascade Challenge","Zoo Town Open","Dynamic Discs Open","Des Moines Challenge","Kansas City Wide Open","PCS Open","European Open","Mid America Open","Ledgestone Open","Idlewild","Great Lakes Open","Jim Palmeri's AFDO","PDGA Worlds","MVP Open"};
    int Stats2023[26][10000] = {0};
    int Stats2022[26][10000] = {0};
    int Stats2021[26][10000] = {0};
    int Stats2023_FPO[26][10000] = {0};
    int Stats2022_FPO[26][10000] = {0};
    int Stats2021_FPO[26][10000] = {0};
    for(int i = 0; i < 26; i++){
        for(int j = 0; j < 10000; j++){
            Stats2023[i][j] = -999;
            Stats2022[i][j] = -999;
            Stats2021[i][j] = -999;
            Stats2023_FPO[i][j] = -999;
            Stats2022_FPO[i][j] = -999;
            Stats2021_FPO[i][j] = -999;
        }
    }
    int event_count = compile_year(Players, Stats2023,"2023.txt");
    compile_year(Players, Stats2022,"2022.txt");
    compile_year(Players, Stats2021,"2021.txt");
    compile_year(Players_FPO, Stats2023_FPO, "2023_FPO.txt");
    compile_year(Players_FPO, Stats2022_FPO, "2022_FPO.txt");
    compile_year(Players_FPO, Stats2021_FPO, "2021_FPO.txt");
    for(int i = 1; i <= event_count; i++){
        cout<<events[i]<<endl;
        print_event_best(Players, Stats2023[i]);
        print_event_best(Players_FPO,Stats2023_FPO[i]);
        cout<<endl<<endl;
    }
    cout<<"----------TEMP MPO----------"<<endl;
    calc_temp(Players,Stats2023,event_count);
    cout<<"----------TEMP FPO----------"<<endl;
    calc_temp(Players_FPO,Stats2023_FPO,event_count);
    cout<<endl<<endl<<"----------Event History MPO----------"<<endl;
    event_best(Players,Stats2021,Stats2022,Stats2023,events);
    cout<<endl<<endl<<"----------Event History FPO----------"<<endl;
    event_best(Players_FPO,Stats2021_FPO,Stats2022_FPO,Stats2023_FPO,events);
}
