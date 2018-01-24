
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
using namespace std;
struct nodes{
    int number;
    nodes* next;
};
struct myarr
{
    int y;
    nodes* root;
};

ifstream files1 , files2, files3;
char* infile1;
char* infile2;
char* infile3;
void confirm(nodes* t);
myarr *Array;
int Arrsize, edge;
int deg, edgearr[1000];
void endgraph(nodes* t);

void print(){
}
void close(int a){
    if( a == 1 ){
        files1.close();
    }
    if( a == 2 ){
        files2.close();
    }
    if( a == 3 ){
        files3.close();
    }
}
void open(int a,int b){
    if( a == 1 ){
        if (b == 1){
            files1.open(infile1);
        }
        if(b == 2){
            files1.open(infile2);
        }
        if(b == 3){
            files1.open(infile3);
        }
    }
    if( a == 2){
        if (b == 1){
            files2.open(infile1);
        }
        if(b == 2){
            files2.open(infile2);
        }
        if(b == 3){
            files2.open(infile3);
        }
    }
    if( a == 3){
        if (b == 1){
            files3.open(infile2);
        }
        if(b == 2){
            files3.open(infile2);
        }
        if(b == 3){
            files3.open(infile3);
        }
    }
}

void addin(int case1, int case2) {
	int stop = false , node1, node2 ,pos = 0;
	open(1,2);
	while (true){
		files1 >> node1, files1 >> node2;
		if (files1.good() != true) {
			break;
		}
		if (node2 <= case2){
            if(node2 >= case1){
            Array[pos].root = 0;
            Array[pos].y = node1;
			pos = pos + 1;
            }
		}
	}
	close(1);
	open(2,1);
	while (true){
    stop = false;
		files2 >> node1 , files2 >> node2;
		if (files2.good() != true) {
			close(2);
			return;
		}
		int scale = 0;
		  while(scale < Arrsize && stop == false) {
			if (Array[scale].y == node1) {
                int itarrayt = 0; // hahah get it iterate... itarrayt.... haha
				while(itarrayt < Arrsize && stop == false) {
					if (Array[itarrayt].y == node2) {
						edge++;
						nodes * t = new nodes();
						t->number = node2;
						t->next = Array[scale].root;
						Array[scale].root = t;
						stop = true;
					}
                    itarrayt++;
				}
			}
			scale++;
		}
	}
}
void getrange(int input2, int input3) {
	int node1, node2;
	Arrsize = 0;
	open(1,2);
	while(true){
		files1 >> node1;
		files1 >> node2;
		if (files1.good() != true) {
			break;
		}
		if (node2 >= input2 && node2 <= input3) {
			Arrsize++;
		}
	}
	close(1);
	Array = new myarr[Arrsize];
	close(1);
	addin(input2, input3);
	return;
}

void outdeg(){

}

void shortestpath(){
// int in1, in2;
// in1 = atoi(comarray[i][1].c_str()); // turn the string to number
// in2 = atoi(comarray[i][2].c_str()); // #2

}
void confirm(nodes* t){
    if (t->next != 0){
        deg = deg + 1;
        confirm(t->next);
    }
    else{
        return;
    }
}
void endgraph(nodes* t){
    if (t->next != 0){
        endgraph(t->next);
    }
    delete t;
    return;
}
void Init_single_source(int V, int s){

}
void shortest_path(int s, int t){
int arr[100], arrb[100];


}
int main(int argc, char* argv[]){
    cout<<"[----------start---------]"<<endl;
    infile1 = argv[1],infile2 = argv[2], infile3 = argv[3];
    open(3,3);
    int num_com;
    string myArray[100];
    ifstream file(infile3);//change to "commands.txt" for test
    //open file and seperate lines
    if(file.is_open())
    {
       int x = 0;
       while(file.good())
        {
            getline(file,myArray[x]);
            num_com = x;
            x++;
        }
    }
    string comarray[50][6];         // 2d array of [line] & [words]
    for(int i = 0; i<= num_com; i++)
    {
        string line = myArray[i]; // line to seperate the string into an array.
        stringstream ssin(line);
        for(int c = 0; ssin.good() && c < 6; c++){
            ssin >> comarray[i][c];// store the commands in an array
        }
    }
    string command = comarray[0][0];
    for (int i = 0; i <= num_com; i++){
        command = comarray[i][0];
        if (files3.good() != true){
            break;
        }
        if (command == "graph"){
            int input2 = atoi(comarray[i][1].c_str());
            int input3 = atoi(comarray[i][2].c_str());
            edge = 0;
            getrange(input2, input3);
            cout << "The # of vertices: " << Arrsize << endl;
            cout << "The # of edges: " << edge << endl;
        }
        if (command == "out-degree"){
            int x = 0;
            while( x < Arrsize){
                if (Array[x].root != 0)
                {
                    deg = 1;
                    nodes *t = Array[x].root;
                    confirm(t);
                    int one = 1;
                    edgearr[deg]= edgearr[deg] + one;
                }
                else{
                    deg = 0;
                    edgearr[deg]++;
                }
                x++;
            }
            double edges = (double)edge;
            double asize = (double)Arrsize;
            double average = edges/asize;
            cout << "out-degree average = " << average << endl;
            cout << "-------------------------"<<endl;
            int z = 0;
            while(z < 1000){
                if (edgearr[z] != 0){
                    cout << "Out-Degree ~ "<< z <<" " <<"#vert: " << edgearr[z] <<endl;
                }
                z++;
            }
            cout<<endl;
        }
        if (command == "end-graph"){
            for (int x = 0; x < Arrsize; x++){
                if (Array[x].root != 0){
                    endgraph(Array[x].root);
                }
            }
            delete Array;
            Arrsize = 0, edge = 0, deg = 0;
        }
        if (command == "shortest-path"){
            cout<<"shortest path is: "<<endl;
        }
        if (command == "diameter"){
            cout<<"The diameter of G is: "<<endl;
        }
        if (command == "scc"){
            cout<<"The number of SCC is: "<<endl;
        }
        if(command == ""){
            i--;
            continue;
        }
    }
    return 0;
}


