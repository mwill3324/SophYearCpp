
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <cmath>
#include <stdlib.h>

///////////////proj 2 stuff//////////
#define SYMBOL_LENGTH   20      // Maximum length of a variable name (identifier)
#define INT             0       // Integer type
#define CHAR            1       // Character string type
#define BST             2       // Binary search tree type
#define STRTERM        '\0'    // String termination character
/////////////////
using namespace std;

int numOfCom;
int n,inputsize,memSize,hashTsize, size;
char * t;
int offSet = 0;
void print( string var);
int bstsize;

struct heapEntry
{
    int blockSize;//4 bytes  // Size of free block in bytes
    int offset;   //4 bytes  // Start address of free block given as offset into memory block
};
struct symbolTableEntry
{
    char symbol[ SYMBOL_LENGTH ];// 20 bytes // Variable identifier = [20]
    int type;        // 4 bytes              // The type of the variable: one of INT, CHAR, or BST
    int offset;      // 4 bytes              // Start address of variable in physical memory given as offset
    int noBytes;     // 4 bytes              // Size in bytes used to store variable in physical memory
};

struct bstNode
{
    int key;   //4bytes   A node of a binary search tree ordered on this key value
    int left;  //4bytes   Left child
    int right; //4bytes   Right child
};

symbolTableEntry *symTable = new symbolTableEntry[hashTsize];
int storagecount=0;
int newkey = 0;
int pnum =0;
bstNode *bst;
heapEntry *heapArr;

/////Geting command Input///////
string comarray[5];
string cominput = "";
string com;
string nametemp;
string typetemp;
string numtemp;
string wordtemp;
string command;
stringstream ss(command);
///////////////////////////////


int hashf(string x, int tsize)
{
    int key = 0;
    int xlen = x.length();
    for(int i = 0; i < xlen; i++)
    {
        key += x.at(i);
    }
    key = key % tsize;
    return key;
}

int parent(int i)
{
    return i / 2;
}

int left(int i)
{
    return 2 * i - 1;
}

int right(int i)
{
    return 2 * i;
}


int getOff(string value)
{
    int newvalue = 0;
    if(atoi(value.c_str()) % 4 == 0)
    {
        newvalue = atoi(value.c_str());
    }
    else
    {
        newvalue = atoi(value.c_str())+(4 - (atoi(value.c_str()) % 4) );
    }
    return newvalue;
}

void myMalloc(string value,int type,string sym,string var)
{
    //////TYPE INT//////
    if(type == 0)
    {
        unsigned int num = atoi(value.c_str());
        memcpy(&t[offSet],&num, 4);
        offSet = offSet + 4;
    }
    /////TYPE CHAR/////
    if(type == 1)
    {
        int newval = offSet + getOff(value);
        for(int x = 1; sym.at(x)!= '"' ; x++)
        {
            t[offSet] = sym.at(x);
            t[offSet+1] = '\0';
            offSet++;
        }
        offSet = newval;
    }
    if(type==2)
    {
        unsigned int num = atoi(value.c_str());
        unsigned int F = -1;
        memcpy(&t[offSet],&num, 4);
        offSet = offSet + 4;
        memcpy(&t[offSet],&F, 4);
        offSet = offSet + 4;
        memcpy(&t[offSet],&F, 4);
        offSet = offSet + 4;
    }
}

void allocate(string type, string var,string value,string sym)
{
    int newtype;

    if(type=="INT")
    {
        newtype = 0;
    }
    if(type=="CHAR")
    {
        newtype = 1;
    }
    if(type=="BST")
    {
        newtype = 2;
    }

    myMalloc(value, newtype, sym, var);
}



void add(string var, string value)
{
    int a = 0;
    a = hashf(var,hashTsize);
    int varlen = var.length();
    int checkposition = 0;
    bool confirmed = false;
//hopefully checks correct var position
    while(checkposition < hashTsize && confirmed==false)
    {
        for(int scan = 0; scan <varlen; scan++)
        {
            if(var.at(scan)==symTable[a].symbol[scan])
            {
                if(scan == (varlen))
                {
                    confirmed = true;
                }
                continue;
            }
            else
            {
                break;
            }
        }
        a++;
        a = a%hashTsize;
        checkposition++;
    }
    if(symTable[a].type == 0)
    {
        int pos = symTable[a].offset;

        if(isdigit(value.at(0)))
        {

            int number = 0;
            memcpy(&number,&t[pos], 4);//COPY MEM FROM ORIGINAL VAR
            number = number + atoi(value.c_str());// ADD FOR NEW VALUE
            memcpy(&t[pos],&number, 4); // COPY NEW VALUE TO ORIG MEMORY
            cout<<"The value of "<<var<<" is: "<<number<<endl;
        }
        else
        {
            int key2 = hashf(value,hashTsize);
            int pos2 = symTable[key2].offset;
            if(symTable[key2].type == 0)
            {
                int number = 0;
                int number2 = 0;
                memcpy(&number,&t[pos], 4); //COPY VAL 1
                memcpy(&number2,&t[pos2], 4);//COPY VAL 2
                number = number + number2;//ADD BOTH
                memcpy(&t[pos],&number, 4);//SET NEW NUMBER TO MEMORY
                cout<<"The value of "<<var<<" is: "<<number<<endl;
            }
            else
            {
                cout<<"Error: RHS of add must be type INT."<<endl;
            }
        }
    }
    else
    {
        cout<<"Error: LHS of add must be type INT."<<endl;
    }
}
void map1()
{
    int printcount = 0;
    for(int x = 0; x < inputsize; x++)
    {
        int y = 0;
        while(y<hashTsize)
        {
            if(symTable[y].offset == x && symTable[y].type == 1 )   //CHECK IF X IS CHAR OR HEX
            {
                for(int z = 0; z < symTable[y].noBytes; z++)   //FOR BYTES PRINT LETTERS
                {
                    if(t[x+z]=='\0')
                    {
                        if(printcount % 4 == 0)
                        {
                            printf( "%c ", '|');
                        }
                        if(printcount % pnum == 0&& printcount!=0)
                        {
                            cout<<endl;
                            printf( "%c ", '|');
                        }
                        printf( "%c  ",' ');
                        printcount++;
                    }
                    else
                    {
                        if(printcount % 4 == 0)
                        {
                            printf( "%c ", '|');
                        }
                        if(printcount % pnum == 0&&printcount!=0)
                        {
                            cout<<endl;
                            printf( "%c ", '|');
                        }
                        printf( "%c  ",t[x+z]);
                        printcount++;
                    }
                }
                x = x + symTable[y].noBytes;
            }
            y++;
        }
        y = 0;
        int skip = 0;
        while(y<hashTsize)
        {
            if(symTable[y].offset == x && symTable[y].type == 1 )
            {
                x--;
                skip = 1;
                continue;
            }
            y++;
        }
        if (skip == 1)
        {
            continue;
        }
        else
        {
            if(printcount % 4 == 0)
            {
                printf( "%c ", '|');
            }
            if(printcount % pnum == 0 && printcount!=0)
            {
                cout<<endl;
                printf( "%c ", '|');
            }
            printf( "%02x ", t[x] & 0xff );
            printcount++;
        }
    }
    printf( "%c ", '|');
    cout<<endl;
}

void inorder(int a){    // PRINT IN-ORDER traversal
    if(t[a+4]!= -1)
    {
        inorder(t[a+4]);
    }
    cout<<(int)t[a]<<" ";
    if(t[a+8]!= -1 && t[a+8]!= 0)
    {
        inorder(t[a+8]);
    }
}

void print(string var){
    int key = 0;
    key = hashf(var,hashTsize);
    bool confirmed = false;
    int varlen = var.length();
    int checkposition = 0;
    while(checkposition < hashTsize && confirmed == false){
        for(int scan = 0; scan <varlen; scan++){
            if(var.at(scan) == symTable[key].symbol[scan]){
                if(scan == (varlen)){
                    confirmed = true;
                }
                continue;
            }
            else{
                break;
            }
        }
        key++;
        key = key%hashTsize;
        checkposition++;
    }
    if(symTable[key].type >=0 && symTable[key].type<=2){
        if(symTable[key].type == 0)
        {
            int pos = symTable[key].offset;
            int number = 0;
            memcpy(&number,&t[pos], 4);
            printf("%d ",number);
        }
        if(symTable[key].type == 1)
        {
            int pos = symTable[key].offset;
            for(int b = 0; t[pos+b]!= '\0'; b++)
            {
                printf("%c ",t[pos+b]);
            }
            cout<<endl;
        }
        if(symTable[key].type == 2)
        {
            int pos = symTable[key].offset;
            int number = 0;
            memcpy(&number,&t[pos], 4);

            inorder(symTable[key].offset);
            cout<<endl;

        }
    }
    else
    {
        cout<<"Error: Symbol table lookup failed"<<endl;
    }
}
void strcat(string var, string value)
{
    int a = 0;
    int x = 0; //FOR LENGTH OF FIRST VAR
    int y = 0; //FOR LENGTH OF SECOND VAR (NON STRING)
    a = hashf(var,hashTsize);

    bool confirmed = false;
    int varlen = var.length();
    int checkposition = 0;
    while(checkposition < hashTsize && confirmed==false)
    {
        for(int scan = 0; scan <varlen; scan++)
        {
            if(var.at(scan) == symTable[a].symbol[scan])
            {
                if(scan == (varlen))
                {
                    confirmed = true;
                }
                continue;
            }
            else
            {
                break;
            }
        }
        a++;
        a = a%hashTsize;
        checkposition++;
    }

    int off = symTable[a].offset;
    if(symTable[a].type == 1)
    {
        for(int q = 0; t[off+q] != '\0' ; q++)
        {
            x++;
        }
        if(value.at(0)=='"')
        {
            int length = value.length()- 2;// -2 for the ' " ' marks
            if(symTable[a].noBytes > length + x)
            {
                for(int y = 1; value.at(y)!= '"' ; y++)
                {
                    t[off+x+y-1] = value.at(y);
                    t[off+x+y] = '\0';
                }
                cout<<"The value of "<<var<<" is: ";
                print(var);
                cout<<endl;

            }
            else
            {
                cout<<"Error: LHS insufficient length to perform strcat."<<endl;
            }
        }
        else
        {
            int var2 = hashf(value,hashTsize);
            int off2 = symTable[var2].offset;
            if(symTable[var2].type == 1)
            {
                for(int q = 0; t[off2+q]!='\0'; q++)
                {
                    y++;
                }
                if(symTable[a].noBytes > y + x)
                {
                    for(int j = 0; t[off2+j]!='\0' ; j++)
                    {
                        t[off+x+j] = t[off2+j];
                        t[off+x+j+1] = '\0';
                    }
                    cout<<"The value of "<<var<<" is: ";
                    print(var);
                    cout<<endl;
                }
                else
                {
                    cout<<"Error: LHS insufficient length to perform strcat."<<endl;
                }
            }
            else
            {
                cout<<"Error: RHS of strcat must be type CHAR."<<endl;
            }
        }
    }
    else
    {
        cout<<"Error: LHS of strcat must be type CHAR."<<endl;
    }
}

void myFree(string var)
{
    int key = 0;
    key = hashf(var,hashTsize);
    bool confirmed = false;
    int varlen = var.length();
    int checkposition = 0;
    while(checkposition < hashTsize && confirmed==false)
    {
        for(int scan = 0; scan <varlen; scan++)
        {
            if(var.at(scan) == symTable[key].symbol[scan])
            {
                if(scan == (varlen))
                {
                    confirmed = true;
                }
                continue;
            }
            else
            {
                break;
            }
        }
        key++;
        key = key%hashTsize;
        checkposition++;
    }
    if(symTable[key].type==0 ||symTable[key].type==1||symTable[key].type==2)
    {
        ///////////CHAR///////////
        if(symTable[key].type == 0)
        {
            int pos = symTable[key].offset;
            for(int b = 0; b<4; b++)
            {
                t[pos+b] = 0;
            }
            symTable[key].type    = -1;
            symTable[key].offset  = 0;
            symTable[key].noBytes = 0;
            for(int er=0; symTable[key].symbol[er]!='\0'; er++)
            {
                symTable[key].symbol[er]= '\0';
            }
        }
        ///////////CHAR///////////
        if(symTable[key].type == 1)
        {
            int pos = symTable[key].offset;
            for(int b = 0; b<symTable[key].noBytes; b++)
            {
                t[pos+b] = 0;
            }
            symTable[key].type    = -1;
            symTable[key].offset  = 0;
            symTable[key].noBytes = 0;
            for(int er=0; symTable[key].symbol[er]!='\0'; er++)
            {
                symTable[key].symbol[er]='\0';
            }
        }
        if(symTable[key].type == 2)
        {
            int pos = symTable[key].offset;
            for(int b = 0; b<symTable[key].noBytes; b++)
            {
                t[pos+b] = 0;
            }
            symTable[key].type    = -1;
            symTable[key].offset  = 0;
            symTable[key].noBytes = 0;
            for(int er=0; symTable[key].symbol[er]!='\0'; er++)
            {
                symTable[key].symbol[er]= '\0';
            }
            delete[] bst;
        }
        heapArr[key].offset = 0;
        heapArr[key].blockSize = 0;
        cout<<"Succesfully freed symbol: "<<var<<endl;
    }
    else
    {
        cout<<"Error: Symbol table lookup failed"<<endl;
    }
}

void insertroot(string root,string value)
{
    int val = atoi(value.c_str());
    int key = 0;
    key = hashf(root,hashTsize);
    bool confirmed = false;
    int varlen = root.length();
    int checkposition = 0;

//// CHECK ROOT VALUE ////
    while(checkposition < hashTsize && confirmed == false)
    {
        for(int scan = 0; scan < varlen; scan++)
        {
            if(varlen == 1 && symTable[key].symbol[0]==root.at(0))
            {
                confirmed = true;
            }
            else if(root.at(scan) == symTable[key].symbol[scan])
            {
                if(scan == (varlen-1))
                {
                    confirmed = true;
                }
                continue;
            }
            else
            {
                break;
            }
        }
        if(confirmed == false)
        {
            cout<<"~insert failed"<<endl;
            break;
        }
        else
        {
            cout<<"~insert success"<<endl;
        }
        if(confirmed == false)
        {
            key++;
            key = key % hashTsize;
            checkposition++;
        }
    }

//// END CHECK/ varification of correct variable ////
    int rootoff = symTable[key].offset;
    int rootnum = 0;
    int rright = 8;
    int rleft = 4;
    int side;
    unsigned int F = -1;
    memcpy(&rootnum,&t[rootoff], 4);
    int off = offSet;
    int y = 0;
    //int x = key;
    int apos = 1;
    int aparent=1;
    int LR = 0;
    // SET IN ARRAY//
    bool isset = false;
    symTable[key].noBytes += 12;
    while(isset == false)
    {
        if(bst[apos].key < val)  //GO RIGHT
        {
            aparent = apos;
            apos = (apos*2)+1;
            LR = 1;
        }
        else
        {
            aparent = apos;
            apos = apos*2;
            LR = 0;
        }
        if(bst[apos].key == '\0')
        {
            bst[apos].key = val;
            if(LR == 0)
            {
                bst[aparent].left = apos;
            }
            else
            {
                bst[aparent].right = apos;
            }
            isset = true;
        }
        else
        {
            continue;
        }
    }

    cout<<endl;
    int nodepos= symTable[key].offset;
    int leaf = nodepos;
    while(leaf != -1)    //| if value at position x is not empty
    {
        memcpy(&y,&t[nodepos], 4);  //| Y = X value.
        if(val < y)                 //| if val < X(y)
        {
            memcpy(&leaf,&t[nodepos+4], 4);    //copy left position to x;
            if(leaf != -1)
            {
                nodepos = leaf;
            }
            side = rleft;
        }
        else
        {
            memcpy(&leaf,&t[nodepos+8], 4);
            if(leaf != -1)
            {
                nodepos = leaf;
            }
            side = rright;
        }
    }
    memcpy(&t[nodepos+side],&off, 4);
    memcpy(&t[offSet],&val, 4);
    offSet = offSet+4;
    memcpy(&t[offSet],&F, 4);
    offSet = offSet + 4;
    memcpy(&t[offSet],&F, 4);
    offSet = offSet + 4;
    map1();
}


int main()
{
    cin>>inputsize;
    cin>> hashTsize;
    cin >> numOfCom;
    inputsize = pow(2,inputsize);
    for(int e =0; e<hashTsize; e++)
    {
        int q = 0;
        while(q<hashTsize)
        {
            symTable[e].symbol[q] = '\0';
            q++;
        }
        symTable[e].type    = -1;
        symTable[e].offset  = 0;
        symTable[e].noBytes = 0;
    }
    int heapsize = inputsize/4;
    int bstsize = inputsize/4;
    offSet = 0;
    bst = new bstNode[bstsize];
    heapArr = new heapEntry[heapsize];
    t = new char[inputsize];

    for(int fillh = 0; fillh<bstsize; fillh++)
    {
        bst[fillh].key = 0;
    }


    for(int e =0; e<hashTsize; e++)
    {
        int q = 0;
        while(q<hashTsize)
        {
            symTable[e].symbol[q] = '\0';
            q++;
        }
        symTable[e].type    = -1;
        symTable[e].offset  = 0;
        symTable[e].noBytes = 0;
    }
    cout<<"------start------"<<endl;
//////////////////////////////////////////////////////////
    if(inputsize>62)
    {
        pnum = 32;
    }
    else
    {
        pnum = 16;
    }
    //CLEAN MAP
    for(int y = 0; y < inputsize; y++)
    {
        t[y] = 0;
    }
///////////////////////////////////////////
    map1();
    cout<<endl;

    for(int i = 0; i<numOfCom; i++ )
    {
        newkey = 0;
        int c = 0;
        for(int e =0; e<hashTsize; e++)
        {
            int q = 0;
            if((symTable[e].type!= 0 && symTable[e].type!= 1)&& symTable[e].type != 2)
            {
                while(q < hashTsize)
                {
                    symTable[e].symbol[q] = '\0';
                    q++;
                }
                symTable[e].type    = -1;
                symTable[e].offset  = 0;
                symTable[e].noBytes = 0;
            }
        }

        getline(cin, cominput); // Take in the command
        string line = cominput; // line to seperate the string into an array.
        stringstream ssin(line);
        while (ssin.good() && c < 6)
        {
            ssin >> comarray[c];// store the commands in an array
            ++c;
        }
        com = comarray[0];
        typetemp = comarray[1];
        nametemp = comarray[2];
        numtemp = comarray[3];

        int linelen = line.length();
        int ssub = 0;
        int esub = 0;

        for(int y = 0; y < linelen; y++)
        {
            if (line.at(y)=='"'&& comarray[4].length()>0)
            {
                ssub = y;
                for(int z = 1; z + y < linelen; z++)
                {
                    if (line.at(y+z)=='"')
                    {
                        esub = y+z;
                        comarray[4]=line.substr(ssub,esub);
                    }
                }
            }
        }
        wordtemp = comarray[4];
        if (com == "exit")
        {
            break;
        }
        if(comarray[0]=="")
        {
            i--;
            continue;
        }
        newkey = 0;
        cout<<"\n\n";
        cout<<"--command #"<<i<<"--"<< endl;
        cout<<line<<endl;
        cout<<"---------------"<< endl;


        if(com == "allocate")
        {
            newkey = hashf(nametemp,hashTsize); // get key
            int keycount = 0;
            bool confirm2 = false;
            while(symTable[newkey].type != -1)
            {
                newkey++;
                newkey = newkey % hashTsize;
                keycount++;
                if(keycount>=hashTsize)
                {
                    break;
                }
            }
            if(keycount < hashTsize)
            {
                confirm2 = true;
            }
            if(confirm2 == false)
            {
                cout<<"Error: Hash table full, exiting."<<endl;
            }

            int offtemp = offSet;
            int number = atoi(numtemp.c_str());
            allocate(comarray[1],comarray[2],comarray[3],comarray[4]);

            if(symTable[newkey].type == -1)
            {
                int namelen = nametemp.length();
                for(int bee = 0; bee<namelen; bee++)
                {
                    symTable[newkey].symbol[bee] = nametemp.at(bee);
                }
                if(typetemp=="INT" && symTable[newkey].type == -1)
                {
                    symTable[newkey].offset = offtemp; // set offset
                    symTable[newkey].noBytes = 4;
                    symTable[newkey].type = 0;
                }
                if(typetemp=="CHAR")
                {
                    symTable[newkey].offset = offtemp;
                    symTable[newkey].type = 1;  // 1 is CHAR
                    symTable[newkey].noBytes = getOff(numtemp);
                }
                if(typetemp=="BST")
                {
                    symTable[newkey].offset = offtemp;
                    symTable[newkey].type = 2;  // 1 is CHAR
                    symTable[newkey].noBytes = 12;
                }
            }
            /*
               if(symTable[newkey].type!=-1){
                cout<<"--hash: "<< newkey <<"--"<<endl;
                cout<<"syml: ";
                for(int boob = 0;symTable[newkey].symbol[boob]!= '\0';boob++){
                    cout<<symTable[newkey].symbol[boob];
                }
                cout<<endl;
                cout<<"type: "<<symTable[newkey].type<<endl;
                cout<<"ofst: "<<symTable[newkey].offset<<endl;
                cout<<"byts: "<<symTable[newkey].noBytes<<endl;
                }
                */
            cout<<"The value of ";
            for(int boob = 0; symTable[newkey].symbol[boob]!= '\0'; boob++)
            {
                cout<<symTable[newkey].symbol[boob];
            }
            cout<<" is: ";
            print(comarray[2]);
            cout<<endl;
            ///////// heapArr //////////
            bst[1].key = number;
            heapArr[newkey].offset = symTable[newkey].offset;
            heapArr[newkey].blockSize = symTable[newkey].noBytes;
            map1();
        }
        if(com == "insert")
        {
            insertroot(comarray[1],comarray[2]);
        }
        if(com == "add")
        {
            add(comarray[1],comarray[2]);
        }
        if(com == "map")
        {
            map1();
        }
        if(com == "print")
        {
            print(comarray[1]);
        }
        if(com == "strcat")
        {
            strcat(comarray[1],comarray[2]);
        }
        if(com == "free")
        {
            myFree(comarray[1]);
        }
        if(com == "compact")
        {
            int off[10];
            int freesize[10];
            off[0] = 0;
            freesize[0] = 0;
            int n = 0;
            for(int x = 0; x < inputsize; x++)
            {
                if(t[x] != 0)
                {
                    int y = 0;
                    while(y<hashTsize)
                    {
                        if((symTable[y].offset == x && symTable[y].type != -1)||(symTable[y].offset == x-1 && symTable[y].type != -1))
                        {
                            x = x + symTable[y].noBytes;
                            off[n] = x;
                        }
                        y++;
                    }
                }
                else if(t[x] == 0)
                {
                    int b = 0;
                    while (t[x+b] == 0 && (x+b)<inputsize)
                    {
                        b++;
                    }
                    freesize[n] = b+1;
                    x = x + b;
                    x--;
                    n++;
                }
            }
            for(int y = 0; y<n; y++)
            {
                cout<<"offset: "<< off[y]<<endl;
                cout<<"freesize: "<<freesize[y]<<endl;
                cout<<"--"<<endl;
            }
        }
        if(comarray[0]=="")
        {
            i--;
            continue;
        }
        comarray[0]="";
        comarray[1]="";
        comarray[2]="";
        comarray[3]="";
        comarray[4]="";
    }
    return 0;
}
