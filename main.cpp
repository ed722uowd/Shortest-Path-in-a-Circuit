#include<iostream>
#include<fstream>

#include"function.h"

using namespace std;

//Main Function
int main (int argc, char* argv[]){

    bool check;
    fstream file;
    file_bench f;
    Graph G;
    check = check_input (argv, argc, file, f);

    if (check == false){
        file.close();
        return 0;
    }

    string file_name = argv[1] ;
    string input  = argv[2];
    string output  = argv[3];
    file.open(file_name.c_str(),ios::binary|ios::in);

    create_graph(file, f, input, G);
    /*
    To Print adjacency list
     call/uncomment the below fuction
    */
    G.print_graph();
    
    Dijkstra (G, output);

    file.close();   
    return 0;
}
