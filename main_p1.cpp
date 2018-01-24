#define NO_TEAMS 32 // Number of NFL teams
#define TEAM_NAME_LEN 25 // Maximum team name string length
#define TOP_LEN 6 // Maximum time of possession string length
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <iomanip>
//

const int MAX_TOKENS_PER_LINE = 20;
const int CMDS = 9;
using namespace std;
int yearstart, yearend, y;// number of years
int provyear, year, printorder, thestat;
string thename;
string fourth[10];
string sixth;
string seventh;
string eighth;
string order;
string comarray[7];
string cominput;
    string name;           // stores name of person
    string command;       // define a string to hold the user command
    string com;
    stringstream ss(command);
int sel;
int prange1, prange2;
string tsarr[20]; // checks user input for a stat
int order1[6*NO_TEAMS];
int orderyear[6*NO_TEAMS];

int printcheck;

///////////////////////////////ARRAYS TO HOLD STATS 2 BE SORTED
string tempst[NO_TEAMS*6];
int tempi[NO_TEAMS*6];
float tempf[NO_TEAMS*6];
///////////////////////////////////////////////////////////////
struct team_stats
{
    char team_name[ TEAM_NAME_LEN ]; // Name of NFL team
    int games; // Number of games played in the season
    float pts_per_game; // Points per game
    int total_points; // Total points
    int scrimmage_plays; // Scrimmage plays
    float yds_per_game; // Yards per game
    float yds_per_play; // Yards per play
    float first_per_game; // First downs per game
    int third_md; // Third down conversions
    int third_att; // Third down attempts
    int third_pct; // Third down percentage
    int fourth_md; // Fourth down conversions
    int fourth_att; // Fourth down attempts
    int fourth_pct; // Fourth down percentage
    int penalties; // Number of penalties
    int pen_yds; // Penalty yards
    char top_per_game[ TOP_LEN ]; // Time of possession per game
    int fum; // Number of fumbles
    int lost; // Fumbles lost
    int to; // Turnover ratio
};

struct annual_stats{
    int year;
    struct team_stats teams[NO_TEAMS];
};

//
ifstream infile;
//

void printi(){
    for (int w = 0; w <= NO_TEAMS-1; w++){
        cout<<tempi[w]<<endl;

    }

}
void rprinti(int interval){
    for (int w = 0; w <= 31*interval ; w++){
        cout<<tempi[w]<<endl;
    }
}

void printid(){
    for (int w = NO_TEAMS-1; w >= 0; w--){
        cout<<tempi[w]<<endl;
    }
}
void printfl(){
    for (int w = 0; w < NO_TEAMS; w++){
        cout<< tempf[w] <<endl;
    }
}
void printfld(){
    for (int w = NO_TEAMS-1; w >  0; w--){
        cout<< tempf[w] <<endl;
    }
}
void printst(){
    for (int w = 0; w < NO_TEAMS; w++){
        cout<<tempst[w]<<endl;
    }
}
void printsd(){
    for (int w = NO_TEAMS-1; w >  0; w--){
        cout<<tempst[w]<<endl;
    }
}

////////////////bfind//////////////

void bfind(int year, int stat, int sel){
    cout<<"--------------bfind--------------"<<endl;
    int n = NO_TEAMS;
    int x=0;
    int d;
    int temp;
    int temporder;
    float ftemp;
    string temps;
    int r = stat;
    if(r== 1||r ==3 ||r== 4 || r== 8 || r==9
            ||r==10 ||r== 11||r==12||r == 13||r == 14
            ||r==15 ||r== 17||r==18||r==19){
        printcheck=0;
        while (x < n){
            for (x = 0 ; x < ( n - 1 ); x++){
                for (d = 0 ; d < n - x - 1; d++){
                    if (tempi[d] > tempi[d+1])
                    {
                        temporder = order1[d];
                        order1[d]   = order1[d+1];
                        order1[d+1] = temporder;

                        temp = tempi[d];
                        tempi[d]   = tempi[d+1];
                        tempi[d+1] = temp;
                    }
                }
            }
            x++;
        }

    }
    //float
    if(r == 2 || r == 5 || r == 6 || r == 7)
    {
        printcheck=1;
        while (x < n)  ////same loop different data type
        {
            for (x = 0 ; x < ( n - 1 ); x++){
                for (d = 0 ; d < n - x - 1; d++){
                    if (tempf[d] > tempf[d+1]){
                        ftemp = tempf[d];
                        tempf[d]   = tempf[d+1];
                        tempf[d+1] = ftemp;
                    }
                }
            }
            x++;
        }

    }
    comarray[0]="";
    comarray[1]="";
    comarray[2]="";
    comarray[3]="";
    r = 0;
} // END BFIND ////////
///////////////////////

////////////////////////
////bsort////////
//////////////////////

void bsort(int year, int stat, int sel)
{
    int c=0;
    int r = stat;
    string temps;
    if(year<0 && year > 5)
    {
    }
    else
    {
        cout<<"------------------bsort----------------"<<endl;
        int n = NO_TEAMS;
        int p=0;
        int d;
        int temp;
        int temporder;
        float ftemp;
// the different temps are for the different data types.
// the first if statements are to check which is which.
        if(r== 1||r ==3|| r== 4 ||r== 8 || r==9 ||
           r==10||r== 11||r==12||r == 13|| r==14|| r== 15||
           r==17||r==18||r==19){
            printcheck =0;
            while (p < n){
                for (p = 0 ; p < ( n - 1 ); p++){
                    for (d = 0 ; d < n - p - 1; d++){
                        if (tempi[d] > tempi[d+1])    {
                            temp = tempi[d];
                            tempi[d]   = tempi[d+1];
                            tempi[d+1] = temp;
                        temporder = order1[d];
                        order1[d]   = order1[d+1];
                        order1[d+1] = temporder;
                        }
                    }
                }
                p++;
            }

        }
        //float
        if(r == 2||r == 5||r ==6||r==7){
            printcheck = 1;
            p=0;n=NO_TEAMS;
            while (p < n){
                for (p = 0 ; p < ( n - 1 ); p++){
                    for (d = 0 ; d < n - p - 1; d++){
                        if (tempf[d] > tempf[d+1]){
                            ftemp = tempf[d];
                            tempf[d]   = tempf[d+1];
                            tempf[d+1] = ftemp;
                        temporder = order1[d];
                        order1[d]   = order1[d+1];
                        order1[d+1] = temporder;
                        }
                    }
                }
                p++;
            }
            if (printorder == 0){
                printfl();
                }
        }
        //string
        if(r == 0||r == 16){
            printcheck =2;
            while (c < n)   //string data type
            {
                for (c = 0 ; c < ( n - 1 ); c++){
                    for (d = 0 ; d < n - c - 1; d++){
                        if (tempst[d] > tempst[d+1]){
                            temps = tempst[d];
                            tempst[d]   = tempst[d+1];
                            tempst[d+1] = temps;
                        temporder = order1[d];
                        order1[d]   = order1[d+1];
                        order1[d+1] = temporder;
                        }
                    }
                }
                c++;
            }
            if (printorder == 0)
            {
                printst();
            }
            if (printorder == 1)
            {
                printsd();
            }
        }
    }

    comarray[0]="";
    comarray[1]="";
    comarray[2]="";
    comarray[3]="";
    r=0;
} // end bsort////
//////////////////


void qsort(int tempi[], int start, int fin)
{
  int st = start, f = fin, temp;
  int x = 0;
  x=start;
  int y;
  int temporder;
  y = fin;
  int half = tempi[(y + x)*(1)/2];
//swapping//
////////////
if (st<=f){
  while (st <= f){
    for (st;tempi[st] < half;st++){st=st;}
    for(f;tempi[f] > half;f--){
        f;
    }
        if (st <= f){
        temp = tempi[st],
        tempi[st] = tempi[f],
        tempi[f] = temp;
    temporder = order1[st];
    order1[st]= order1[f];
    order1[f] = temporder;
              st++;
              f--;
    }
 }
}
//start over
if (start < f){
    qsort(tempi, start, f);
}
if (st < fin){
    qsort(tempi, st, fin);
}
}//end qsort

void qprint(int tempi[], int start, int fin){

}

// qsort range/////
//////////////////
void qsort_range(int tempi[], int start, int fin){
int st = start, f = fin, temp;
int x = 0;
  x=start;
  int y;
  int temporder;
  y = fin;
  int half = tempi[(y + x)*(1)/2];
//swapping//
////////////
if (st<=f){
  while (st <= f){
    for (st;tempi[st] < half;st++){}
    for(f;tempi[f] > half;f--){}
        if (st <= f){
        temp = tempi[st],
        tempi[st] = tempi[f],
        tempi[f] = temp;
temporder = order1[st];
order1[st]   = order1[f];
order1[f] = temporder;
              st++;
              f--;
    }
 }
}

//start over
if (start < f){
    qsort_range(tempi, start, f);
}
if (st < fin){
    qsort_range(tempi, st, fin);
 }
}//end qrange


void bsort_range(int yearstart,int yearend, int stat, int sel)
{
    int r1 = yearstart;
    int r2 = yearend;
    int interval =r2-r1;
    int n = 32+32*interval;
    int c=0;
    int temp;
    float ftemp;
    int d;
    int tempr[NO_TEAMS*6];
    float ftempr[NO_TEAMS*6];
    int r = stat;
    int temporder;

    string temps;
    if(comarray[1]=="range")
    {
        if(r== 1||r ==3|| r== 4 || r== 8 || r==9 ||
           r==10||r== 11||r==12||r == 13|| r== 15||
           r==17||r==18||r==19){
            printcheck =0;

            while (c < n){
                for (c = 0 ; c < ( n - 1 ); c++){
                    for (d = 0 ; d < n - c - 1; d++){
                        if (tempi[d] > tempi[d+1])  // can change
                        {
                            temp = tempi[d];
                            tempi[d]   = tempi[d+1];
                            tempi[d+1] = temp;
                        temporder = order1[d];
                        order1[d]   = order1[d+1];
                        order1[d+1] = temporder;
                        }
                    }
                }
                c++;
            }

        }//if r
         if(r == 2||r == 5||r ==6||r==7){
            printcheck =1;
            while (c < n){
                for (c = 0 ; c < ( n - 1 ); c++){
                    for (d = 0 ; d < n - c - 1; d++){
                        if (tempi[d] > tempi[d+1])  // can change
                        {
                            ftemp = tempf[d];
                            tempf[d]   = tempf[d+1];
                            tempf[d+1] = ftemp;
                        temporder = order1[d];
                        order1[d]   = order1[d+1];
                        order1[d+1] = temporder;
                        }
                    }
                }
                c++;
            }
           }


    }//if range
}//end Brange


int main()
{
/////////
    int rangestart;
    int rangeend;
    int noOfYears;
    //infile.open("2010-2015-game-stats.txt");

   // % a.out <2010-2015-game-stats.txt>

    cin >> noOfYears;
   // cout<<noOfYears<<endl;
   // cin >> noOfYears;
    annual_stats* stats = new annual_stats[noOfYears]; // new
    team_stats* teams = new team_stats[NO_TEAMS];
    //checking still

    for (int s = 0; s < noOfYears; s++){
       cin >> stats[s].year;
        for (int j = 0; j < NO_TEAMS; j++){
            cin.getline(stats[s].teams[j].team_name,TEAM_NAME_LEN,'\t');
            cin >> stats[s].teams[j].games;
            cin >> stats[s].teams[j].pts_per_game;
            cin >> stats[s].teams[j].total_points;
            cin >> stats[s].teams[j].scrimmage_plays;
            cin >> stats[s].teams[j].yds_per_game;
            cin >> stats[s].teams[j].yds_per_play;
            cin >> stats[s].teams[j].first_per_game;
            cin >> stats[s].teams[j].third_md;
            cin >> stats[s].teams[j].third_att;
            cin >> stats[s].teams[j].third_pct;
            cin >> stats[s].teams[j].fourth_md;
            cin >> stats[s].teams[j].fourth_att;
            cin >> stats[s].teams[j].fourth_pct;
            cin >> stats[s].teams[j].penalties;
            cin >> stats[s].teams[j].pen_yds;
            cin >> stats[s].teams[j].top_per_game;
            cin >> stats[s].teams[j].fum;
            cin >> stats[s].teams[j].lost;
            cin >> stats[s].teams[j].to;
            //cout<<stats[s].teams[j].to<<endl;
/*
                infile.getline(stats[s].teams[j].team_name, TEAM_NAME_LEN, '\t');
        //*/
        }
    }

    for (int o =0;o<NO_TEAMS*6;o++){
        order1[o]= o;
    }

int numberofcom = 0;
cin>>numberofcom;
cout<<"number of com: "<<numberofcom<<endl;

/////////
    cout<< "-------------start-----------"<< endl;
    //globals
    string name;           // stores name of person
    string command;       // define a string to hold the user command
    string com;
    stringstream ss(command);
    ss >> command >> name;
    char commands[CMDS][MAX_TOKENS_PER_LINE] = {"pmin", "bfind", "bsort", "qsort", "qfind", "brange", "qrange", "pmax", "Exit"};

    int year1;
    int k = 0;
    int r = 0;

    fourth[0]="incr";
    fourth[1]="decr";
    fourth[2]="max";
    fourth[3]="min";
    fourth[4]="average";
    fourth[5]="median";
    //
    tsarr[0]="team_name";
    tsarr[1]="games";
    tsarr[2]="pts_per_game";
    tsarr[3]="total_points";
    tsarr[4]="scrimmage_plays";
    tsarr[5]="yds_per_game";
    tsarr[6]="yds_per_play";
    tsarr[7]="first_per_game";
    tsarr[8]="third_md";
    tsarr[9]="third_att";
    tsarr[10]="third_pct";
    tsarr[11]="fourth_md";
    tsarr[12]="fourth_att";
    tsarr[13]="fourth_pct";
    tsarr[14]="penalties";
    tsarr[15]="pen_yds";
    tsarr[16]="top_per_game";
    tsarr[17]="fum";
    tsarr[18]="lost";
    tsarr[19]="to";


    //while loop checks if command is not EXIT
    comarray[0]="";
    comarray[1]="";
    comarray[2]="";
    comarray[3]="";
    comarray[4]="";
    comarray[5]="";
    comarray[6]="";
/////commands loop start
    //getline(std::cin, cominput);

    string line = cominput; // line to seperate the string into an array.
    int i = 0;
    stringstream ssin(line);
    cin.ignore();
    cin.ignore();

for (int loopnum = 0; loopnum<numberofcom; loopnum++)
    {
//////
        comarray[0]="";
        comarray[1]="";
        comarray[2]="";
        comarray[3]="";
        comarray[4]="";
        comarray[5]="";
        comarray[6]="";

        getline(cin, cominput); // Take in and reset the commands each time one is completed
        string line = cominput; // line to seperate the string into an array.
        int i = 0;
        stringstream ssin(line);
        while (ssin.good() && i < 6)     // splitting the string
        {
            ssin >> comarray[i];    // storing it in an array
            ++i;
        }
        com = comarray[0];
//////////////////////////////////////////////////////


/////set up to take in commands and input, and convert them for use on functions.

        // first string is the command

        //add RANGE CHECK HERE
        //

        if (comarray[1]!= "range")
        {
            if (comarray[1] == "2010")
            {
                int year1=2010;
                year = 0;
            }
            else if (comarray[1] == "2011")
            {
                int  year1=2011;
                year = 1;
            }
            else if (comarray[1] == "2012")
            {
                int  year1=2012;
                year = 2;
            }
            else if (comarray[1] == "2013")
            {
                int  year1=2013;
                year = 3;
            }
            else if (comarray[1] == "2014")
            {
                int  year1=2014;
                year = 4;
            }
            else if (comarray[1] == "2015")
            {
                int  year1 =2015;
                year = 5;
            }
            else
            {
                cout<<"Error:no such year. "<<endl;
                break;
            }//end year part
        }//end range part

        /*
            std::istringstream sy(comarray[1]);
                sy >> year1;            // making the year into an int
                if (year1 < 2010|| year1>2015){cout<<"Error: no such year. "<<endl;
                command = "nothing";
                }
                else{ year = year1 - 2010;
                com = comarray[0];
                command = com;} // giving the correct year by the count of years.
        */

        /*
          if (comarray[1] == "range"){//check range first
                    rangestart = 0;
                    rangeend = 0;
                    k = 0;
                    r = 0;
                    while(tsarr[k]!= comarray[4]){
                            if (tsarr[k]==comarray[4]){
                                thestat == r;}
                    else{
                        k++;
                        r++;
                    }
                }
            }
            */
        if (comarray[1] != "range") //check range first
        {
            rangestart = 0;
            rangeend = 0;
            k = 0;
            r = 0;
            while(tsarr[k]!= comarray[2])
            {
                if (tsarr[k]==comarray[2])
                {
                    thestat == r;
                }
                else
                {
                    k++;
                    r++;
                }
            }
        }
        else
        {
            while(tsarr[k]!= comarray[4])
            {
                if (tsarr[k]==comarray[4])
                {
                    thestat == r;
                }
                else
                {
                    k++;
                    r++;
                }
            }

        }

        if (comarray[1]== "range"){
            if (comarray[0] == "bsort"){
                com = "brange";
            }
            if (comarray[0] == "qsort"){
                com = "qrange";
            }
        }

        if (comarray[1]!= "range"){
            if (comarray[3] == "decr"){printorder = 1; }
            else if (comarray[3] == "incr"){printorder = 0; }
            else if (comarray[3] == "max"){printorder = 2;}
            else if (comarray[3] == "min"){printorder = 3;}
            else if (comarray[3] == "average"){printorder = 4;}
            else if (comarray[3] == "median"){printorder = 5;}
        }//end non-range print selector
        else
        {
            if (comarray[5] == "decr"){
                printorder = 1;
            }
            if (comarray[5] == "incr"){
                printorder = 0;
            }
            if (comarray[5] == "max"){
                printorder = 2;
            }
            if (comarray[5] == "min"){
                printorder = 3;
            }
            if (comarray[5] == "average"){
                printorder = 4;
            }
            if (comarray[5] == "median"){
                printorder = 5;
            }
        }// end range print selector
        int rsave;
        if(comarray[1]=="range"){
                rsave = 2;
        }
        else{
}
        if (comarray[2] == "2010"){ rangestart=0;}
        else if (comarray[2] == "2011"){rangestart=1;}
        else if (comarray[2] == "2012"){rangestart=2;}
        else if (comarray[2] == "2013"){rangestart=3;}
        else if (comarray[2] == "2014"){rangestart=4;}
        else if (comarray[2] == "2015"){rangestart=5;}
        if (comarray[3] == "2010"){rangeend=0;}
        else if (comarray[3] == "2011"){rangeend=1;}
        else if (comarray[3] == "2012"){rangeend=2;}
        else if (comarray[3] == "2013"){rangeend=3;}
        else if (comarray[3] == "2014"){rangeend=4;}
        else if (comarray[3] == "2015"){rangeend=5;}
        if (comarray[1] == "2010"){ rangestart=0;}
        else if (comarray[1] == "2011"){rangestart=1;}
        else if (comarray[1] == "2012"){rangestart=2;}
        else if (comarray[1] == "2013"){rangestart=3;}
        else if (comarray[1] == "2014"){rangestart=4;}
        else if (comarray[1] == "2015"){rangestart=5;}

       //// to help print range
        prange1 = rangestart;
        prange2 = rangeend;
        ////////////
        sixth = comarray[5];
        seventh= comarray[6];
        eighth = comarray[7];
        int statwanted=0;

        if (comarray[1]!="range")
        {
            while(tsarr[k]!=comarray[2])
            {
                statwanted++;
                cout<<"ran";
            }
        }
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//////////////FIlling array for sorting/////////////////
        int rtemp = rangestart;

        if (comarray[1]== "range" )
        {
            year = rangestart;
        }
        else{rangeend=rangestart;
        }
        cout<<endl;
        cout<<"year: "<< year<<"  ";
        cout<<comarray[0]<<"  ";
        cout<<comarray[1]<<"  ";
        cout<<comarray[2]<<"  ";
        cout<<comarray[3]<<"  ";
        cout<<comarray[4]<<"  ";
        cout<<comarray[5]<<endl;
        int e = 0;
        int year2 = 0;
        year2;

        while(rtemp <= rangeend)
        {
            if(year2 < 6 && year2 >= 0)
            {
                if(r==0){
                    for (int w = 0; w <= NO_TEAMS; w++){
                        tempst[e]= stats[rtemp].teams[w].team_name;
                        e++;
                    }
                }
                if(r==1){
                    for (int w = 0; w <= NO_TEAMS; w++){
                        tempi[e]= stats[rtemp].teams[w].games;
                        e++;
                    }
                }
                if(r==2){
                    for (int w = 0; w <= NO_TEAMS; w++){
                        tempf[e]= stats[rtemp].teams[w].pts_per_game;
                        e++;
                    }
                }
                if(r==3){
                    for (int w = 0; w <= NO_TEAMS; w++){
                        tempi[e]= stats[rtemp].teams[w].total_points;
                        e++;
                    }
                }
                if(r==4){
                    for (int w = 0; w <= NO_TEAMS; w++){
                        tempi[e]= stats[rtemp].teams[w].scrimmage_plays;
                        e++;
                    }
                }
                if(r==5){
                    for (int w = 0; w <= NO_TEAMS; w++){
                        tempf[e]= stats[rtemp].teams[w].yds_per_game;
                        e++;
                    }
                }
                if(r==6){
                    for (int w = 0; w <= NO_TEAMS; w++){
                        tempf[e]= stats[rtemp].teams[w].yds_per_play;
                        e++;
                    }
                }
                if(r==7){
                    for (int w = 0; w <= NO_TEAMS; w++){
                        tempf[e]= stats[rtemp].teams[w].first_per_game;
                        e++;
                    }
                }
                if(r==8){
                    for (int w = 0; w <= NO_TEAMS; w++){
                        tempi[e]= stats[rtemp].teams[w].third_md;
                        e++;
                    }
                }
                if(r==9){
                    for (int w = 0; w <= NO_TEAMS; w++){
                        tempi[e]= stats[rtemp].teams[w].third_att;
                        e++;
                    }
                }
                if(r==10){
                    for (int w = 0; w <= NO_TEAMS; w++){
                        tempi[e]= stats[rtemp].teams[w].third_pct;
                        e++;
                    }
                }
                if(r==11){
                    for (int w = 0; w <= NO_TEAMS; w++){
                        tempi[e]= stats[rtemp].teams[w].fourth_md;
                        e++;
                    }
                }
                if(r==12){
                    for (int w = 0; w <= NO_TEAMS; w++)
                    {
                        tempi[e]= stats[rtemp].teams[w].fourth_att;
                        e++;
                    }
                }
                if(r==13)
                {
                    for (int w = 0; w <= NO_TEAMS-1; w++)
                    {
                        tempi[e]= stats[rtemp].teams[w].fourth_pct;
                        e++;
                    }
                }
                if(r==14)
                {
                    for (int w = 0; w <= NO_TEAMS; w++)
                    {
                        tempi[e]= stats[rtemp].teams[w].penalties;
                        e++;
                    }
                }
                if(r==15)
                {
                    for (int w = 0; w <= NO_TEAMS; w++)
                    {
                        tempi[e]= stats[rtemp].teams[w].pen_yds;
                        e++;
                    }
                }
                if(r==16)
                {
                    for (int w = 0; w <= NO_TEAMS; w++)
                    {
                        tempst[e]= stats[rtemp].teams[w].top_per_game;
                        e++;
                    }
                }
                if(r==17)
                {
                    for (int w = 0; w <= NO_TEAMS; w++)
                    {
                        tempi[e]= stats[rtemp].teams[w].fum;
                        e++;
                    }
                }
                if(r==18)
                {
                    for (int w = 0; w <= NO_TEAMS; w++)
                    {
                        tempi[e]= stats[rtemp].teams[w].lost;
                        e++;
                    }
                }
                if(r==19)
                {
                    for (int w = 0; w <= NO_TEAMS ; w++)
                    {
                        tempi[e]= stats[rtemp].teams[w].to;
                        e++;
                    }
                }
                year2++;
            }//end year check
            rtemp++;
        }// end rangecheck
        command = com;
/////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
        //getline(std::cin, command);     //takes user input and stores in command


//command startings//
/////////////////////
        if (command.compare(commands[0]) == 0)
        {
            cout<<"------------pmin-------------"<<endl;
cout << setw(30) << left << "TEAM" << setw(10) << left << "YEAR" << setw(4) << "STAT" << endl;


          /*  for (int x = 0; x < noOfYears; x++)
            {
                for (int y = 0; y < NO_TEAMS; y++)
                {
                    printf("%s\n",stats[x].teams[y].team_name);

                }
            }*/
            comarray[0]="";
            comarray[1]="";
            comarray[2]="";
            comarray[3]="";
        }
///////////////////////////bfind///////////////////////////
        if (command.compare(commands[1]) == 0)
        {
            bfind(year,r,printorder);


cout << setw(30) << left << "TEAM" << setw(10) << left << "YEAR" << setw(4) << "STAT" << endl;

            int average=0;
            float averagef=0;
            if(printcheck == 0){
                if (printorder == 2) {//max

                //    cout<<tempi[NO_TEAMS - 1]<<endl;
cout << setw(30) << left << "TEAM" << setw(10) << left << (2010+year) << setw(4) << tempi[NO_TEAMS - 1] << endl;

                                }

                if (printorder == 3) {//min
                        cout<< tempi[0]<<endl;
cout << setw(30) << left << "TEAM" << setw(10) << left << (2010+year) << setw(4) << tempi[0] << endl;

                            }

                if (printorder == 4) {//average
                    for(int q = 0; q < NO_TEAMS - 1; q++ ){
                        average += tempi[q];
                                }
                        average =average/32;
               // cout<<average<<endl;

cout << setw(30) << left << "TEAM" << setw(10) << left << (2010+year) << setw(4) << average << endl;

                                }

                if (printorder == 5) //median
                            {
                   // cout<<tempi[16]<<endl;
cout << setw(30) << left << "TEAM" << setw(10) << left
<< (2010+year) << setw(4) << tempi[16] << endl;

                        }
        }//endprintcheck 0
        if(printcheck==1){
        if (printorder == 2){ //max
cout << setw(30) << left << "team name" << setw(10)
<< left << (2010+year) << setw(4) << tempf[NO_TEAMS-1] << endl;
          //  cout<<tempf[NO_TEAMS-1]<<endl;
        }
        if (printorder == 3) //min
        {
cout << setw(30) << left << "team name" << setw(10)
<< left << (2010+year) << setw(4) << tempf[0] << endl;
           // cout<<tempf[0]<<endl;
        }
        if (printorder == 4) //average
        {

            averagef = 0;
            for(int q = 0; q < NO_TEAMS-1; q++ )
            {

                averagef = averagef + tempf[q];
            }
            averagef = (averagef/NO_TEAMS);
cout << setw(30) << left << "team name" << setw(10)
<< left << (2010+year) << setw(4) << averagef << endl;
            //cout<<averagef<<endl;
        }

        if (printorder == 5) //median
        {
cout << setw(30) << left << "team name" << setw(10)
<< left << "year" << setw(4) << tempf[16] << endl;
            //cout<<tempf[NO_TEAMS/2]<<endl;
                }
            }

        }//endbfind

//////////////BSORT///////////////////////////

        if (command.compare(commands[2]) == 0){
        bsort(year, r, printorder);
        if (printorder == 0 && printcheck == 0){
    for (int a = 0; a <= NO_TEAMS-1; a++){
cout << setw(30) << left << stats[year].teams[order1[a]].team_name << setw(10) << left << (year+2010) << setw(4) << tempi[a] << endl;

                }
            }
        if (printorder == 1 && printcheck == 0){
               for (int a = NO_TEAMS; a >= 0; a--){
cout << setw(30) << left << stats[year].teams[order1[a]].team_name << setw(10) << left << (year+2010) << setw(4) << tempi[a] << endl;
                    }
            }
    if (printorder == 1){
        for (int a = NO_TEAMS-1; a >  0; a--){
cout << setw(30) << left << stats[year].teams[order1[a]].team_name << setw(10) << left << (year+2010) << setw(4) << tempf[a] << endl;
    }
            }
        }///end bsort
//////////

        if (command.compare(commands[3]) == 0){
            cout<<"---------qsort------------"<<endl;
            qsort(tempi,0,32);
            if(printorder ==0){

             for (int a = 0; a < NO_TEAMS; a++)
                    {
cout << setw(30) << left << stats[year].teams[order1[a]].team_name << setw(10) << left << (year+2010) << setw(4) << tempi[a] << endl;
             //   cout<<tempi[a]<<endl;
                    }
                }
                if(printorder ==1){
                for (int a = NO_TEAMS; a> 0; a--){
cout << setw(30) << left << stats[year].teams[order1[a]].team_name << setw(10) << left << (year+2010) << setw(4) << tempi[a] << endl;
                }
            }
        }
///////////////////////
        if (command.compare(commands[4]) == 0){
            cout<<"---------------qfind-------------"<<endl;

cout << setw(30) << left << "TEAM" << setw(10) << left << "YEAR" << setw(4) << "STAT" << endl;
            int average = 0;
            qsort(tempi,0,32);
            if (printorder == 2) {//max
cout << setw(30) << left << "team name" << setw(10)
<< left << 2010+year << setw(4) << tempi[NO_TEAMS - 1] << endl;
            cout<<tempi[NO_TEAMS - 1]<<endl;
            }
            if (printorder == 3) { //min
cout << setw(30) << left << "team name" << setw(10)
<< left << 2010+year << setw(4) << tempi[0] << endl;

           // cout<< tempi[0]<<endl;
            }
            float averagef=0;
            if (printorder == 4) //average
            {
            for(int q = 0; q < NO_TEAMS - 1; q++ ){
                 average += tempi[q];
            }
            average =average/NO_TEAMS;

cout << setw(30) << left << "team name" << setw(10)
<< left << 2010+year << setw(4) << average << endl;
            //cout<<average<<endl;

            }
            if (printorder == 5){//median
cout << setw(30) << left << "team name" << setw(10)
<< left << 2010+year << setw(4) << tempi[16] << endl;
            //cout<<tempi[16]<<endl;
            }
        }
/////////////////////
        if (command.compare(commands[5]) == 0){
            cout<<"------------Brange---------------"<<endl;
            cout << setw(30) << left << "TEAM" << setw(10) << left << "YEAR" << setw(4) << "STAT" << endl;

              int newyear;
              newyear=0;
              int r1 = rangestart;
              int yearcount = rangestart;
              int r2 = rangeend;
              int interval =r2-r1;
              int n = 32+32*interval;

              int saveyear[32+32*interval];
            for (int q=0; q<=32+32*interval-1;q++){
                 //   cout<<"order: "<<order1[q]<<endl;
                    saveyear[q]=(order1[q]/32);
                    }
              for (int q=0; q <= 32+32*interval;q++){
                    order1[q]=(order1[q]%32);
              }


            bsort_range(rangestart,rangeend,r,printorder);
            if(printcheck ==0){
             if (printorder == 1){
                int u = 0;
                for (int j = NO_TEAMS+32*interval - 1; j >= 0; j--){
                if (j % 32 == 0){  newyear=0;  }

                    u++;
cout << setw(30) << left << "team name" << setw(10) << left << "year" << setw(4) << tempi[j] << endl;
                        newyear++;
                }
                r1++;
            }
            if (printorder == 0){ //incr
                for (int j = 0; j < NO_TEAMS+32*interval; j++){
                if (j % 32 == 0){  newyear =0; yearcount++;}
cout << setw(30) << left << "team name" << setw(10) << left << "year" << setw(4) << tempi[j] << endl;
                    newyear++;
                }
                r1++;
                }
            }//endpcheck
        if(printcheck ==1){
             if (printorder == 1){
                int u = 0;
                for (int j = NO_TEAMS+32*interval - 1; j >= 0; j--){
                    if(u % 32 == 0 || u ==0){
                        if(comarray[1]=="range"){
                            cout<<"201"<<prange1<<endl;
                            prange1++;
                            }
                        }
                    u++;
        cout << setw(30) << left << "team name" << setw(10) << left << "year" << setw(4) << tempi[j] << endl;


                    //cout<<tempf[j]<<endl;
                }
                r1++;
            }
            if (printorder == 0){
                for (int j = 0; j < NO_TEAMS+32*interval; j++){
                 //////print year
                  if(j % 32 == 0 || j==0){
                        if(comarray[1]=="range"){
                            cout<<"201"<<prange1<<endl;
                            prange1++;
                            }
                        }
cout << setw(30) << left << "team name" << setw(10) << left << "year" << setw(4) << tempi[j] << endl;

                    //cout<<tempi[j]<<endl;
                }
                r1++;
            }
            }//end printcheck 1




        }


        if (command.compare(commands[6]) == 0){
            cout<<"----------------Qrange----------------"<<endl;
cout << setw(30) << left << "TEAM" << setw(10) << left << "YEAR" << setw(4) << "STAT" << endl;

            int rang = rangeend-rangestart;
            int u = 0;
            qsort_range(tempi,0,32+32*rang);
            if (printorder == 1){

                for (int j = NO_TEAMS+32*rang -1; j >= 0; j--){
                     if(u % 32 == 0 || u ==0){
                                    if(comarray[1]=="range"){
                                   // cout<<"201"<<prange1<<endl;
                                    prange1++;
                                            }
                                        }
                    u++;
cout << setw(30) << left << "team name" << setw(10) << left << "year" << setw(4) << tempi[j] << endl;
                    //cout<<tempi[j]<<endl;
                }
            }
            if (printorder == 0){
                for (int j = 0; j < NO_TEAMS+32*rang; j++){

                        if(j % 32 == 0 || j==0){
                            if(comarray[1]=="range"){
                             //   cout<<"201"<<prange1<<endl;
                                prange1++;
                            }
                        }

        cout << setw(30) << left << "team name" << setw(10) << left << "year" << setw(4) << tempi[j] << endl;
                    //cout<<tempi[j]<<endl;
                }
            }

        }
        if (command.compare(commands[7]) == 0){
            cout<<"---------------pmax------------"<<endl;
            cout << setw(30) << left << "TEAM" << setw(10) << left << "YEAR" << setw(4) << "STAT" << endl;

            cout<<stats[0].teams[0].games;
        }
        if (command.compare(commands[8]) == 0){
            cout<<"END"<<endl;
        }
    }//end of while


}//end of main
