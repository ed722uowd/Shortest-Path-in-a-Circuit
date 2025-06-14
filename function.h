#include<iostream>
#include<fstream>
#include<string>

#include "graph.h"

using namespace std;

//Inital input check
bool check_input (char* argv[], int &argc, fstream &file, file_bench &f){

     if (argc != 4){
        cout<<"Incorrect number of arguments"<<endl;
        return false;
    }

    string start = argv[1];
    string input = argv[2];
    string out = argv[3];
    file.open(start.c_str(),ios::binary|ios::in);

    if (!file.is_open()){
        cout<<"Wrong File Name"<<endl;
        return false;
    }

    string line;
    string intitial_out;
    char c, delimiter;

   bool found_in = false ;
   bool found_out = false;
   int displacement = 0;
   int count = 0;
   int pos;
   bool loop = true;
   bool first_out = false;
   bool first_intermediate = false;
    
    while (getline(file,line,'\n')){
 
        c = file.get();

        if (c=='I' && found_in == false){
            getline(file,line,'(');
            getline(file,line,')');

            if (input.compare(line) == 0){
                found_in = true;
            }
        }
        else if (c=='O' && found_out == false){
            if (first_out == 0){
                f.out_pos = file.tellg();
                f.out_pos -= 1;
            }

            if (found_in == true){
                getline(file,line,'(');
                getline(file,line,')');
                if (out.compare(line) == 0){
                    found_out = true;
                }
                if (first_out == false){
                    first_out = true;
                }
            }
            else{
                cout<<"Signal "<<input<<" not found in "<<start;
                return 0;
            }
        }
        else if (c == 'G'){            
            if (found_out == true){
                if (first_intermediate == false){
                    f.intermediate_pos = file.tellg();
                    f.intermediate_pos -= 1;
                    first_intermediate = true;
                    break;
                }  
            }
            else{
                cout<<"Signal "<<out<<" not found in "<<start;
                return 0;
            }
        }
        
        pos = file.tellg();
        file.seekg(pos -1);

    }

    file.clear();

    return true;


}

//Function to find vertices from the bench file for the adjacency list
bool find_vertex(fstream & file, file_bench &f, string input, string &child, int &pos){

    bool initial = false;
    bool found_vertex= false;
    int pos1;
    int length1, length2;

    string line, vertex;
    char delimiter;

    while(getline(file, line, ' ')&& !file.eof()){
        child = line;
        getline(file, line, '(');
        getline(file, line);
        pos = file.tellg();

        for (int i = 0; i < line.length(); ++i){
            if (line[i] == 'G'){
                initial = true;
                pos1 = i;
            }
            if (initial == true && (line[i]==',' || line[i]==')')){
                vertex = line.substr(pos1,i-pos1);
                initial = false;
                if (vertex.compare(input)==0){
                    found_vertex=true;
                    break;
                }

            }
        }

        if (found_vertex==true){
            break;
        }     

    }
    return found_vertex; 
    
}

//Function to create adjacency list
void create_graph(fstream & file, file_bench &f, string input, Graph &G){

    bool initial = false;
    bool found;
    int pos, vertex_pos;
    int weight = 0;
    bool found_vertex = false;
    bool found_child = false;

    string line, line_2;
    string child, curr_child;
    char delimiter;
    file.clear();
    pos = f.intermediate_pos;
    file.seekg(pos);
    while (true){
        bool check;
        check = G.check_f_r();
        if (check == true){
            initial = true;
            G.Graph_enqueue(input);            
        }
        else{
            found = G.set_tmp_head();
            if (found == false){
                break;
            }
            else{
                input = G.return_vertex();
                file.clear();
                pos = f.intermediate_pos;
                file.seekg(pos);
            }
        }
        while(!file.eof()){
            found_vertex = find_vertex(file, f, input, child, pos);
            if (initial == true){
                G.set_tmp_head();
                initial = false;
            }
            vertex_pos = pos;
            curr_child = child;
            
            while(!file.eof() && found_vertex == true){
                found_child=find_vertex(file, f, curr_child, child, pos);
                if (found_child == true){
                    ++weight;
                }
            }
            if (found_vertex == true){
                G.Graph_push(curr_child,weight);
                bool check_queue;
                check_queue = G.check_queue(curr_child);
                if (check_queue == false){
                    G.Graph_enqueue(curr_child);
                }
                weight = 0;
                file.clear();
                file.seekg(vertex_pos);
                found_vertex = false;
                found_child = false;
            }
            else{
                break;
            }
         }
        G.filled_vertex();
    }
}

//To find the position of the minimum distance when implementing Dijkstra
int find_min(int *distance, bool *visited, int vertices){

    int min_pos = -1;

    for (int i =0; i < vertices; ++i){
        if(visited[i] == false && (min_pos == -1 || distance[i]<distance[min_pos])){
            min_pos = i;

        }
    }

    return min_pos;

}

//Function that implements Dijkstra
void Dijkstra (Graph &G, string output){

    int vertices;
    int min_pos, pos;
    int count;
    int edge_weight;
    bool check;
    string line;
    vertices = G.get_no_vertices();

    int *distance = new int[vertices];
    bool *visited = new bool[vertices];
    int *prev_node = new int[vertices];

    for (int i = 0; i < vertices; ++i){
        distance[i] = INT_MAX;
        visited[i] = false;
        prev_node[i] = -1;
    }

    distance[0] = 0;
    prev_node[0] = 0;

    for (int i = 0; i < vertices - 1; ++i){
        min_pos = find_min(distance, visited, vertices);
        visited[min_pos] = true;
        G.set_tmp_adj_header(min_pos);
        while(check = G.check_adj_header()){
            pos = G.get_pos();
            edge_weight = G.get_edge_weight();
            if (visited[pos] == false){
                int dist = distance[min_pos] + edge_weight;
                if (dist < distance[pos]){
                    distance[pos] = dist;
                    prev_node[pos] = min_pos;
                }
            }
            G.shift_adj_header();
            

        }


    }

    pos = G.get_pos_output(output);
    int *connect = new int[pos+1];

    if (distance[pos]!=INT_MAX){
        int size = pos+1;

        for (int i = 0; i < size; ++i){
            connect[i] = -1;
        }    
        int counter = 0;
        while(pos!=0){
            connect[counter] = pos;
            pos = prev_node[pos];
            ++counter;
        }
        connect[counter] = pos;

        for (int i = size-1; i >=0 ; --i){
            if (connect[i] != -1 ){

                cout<<G.get_veretx_name(connect[i]);
                if (i>0){
                    cout<<"-->";
                }

            }
        }
    }
    else{
        cout<<"No path to output: "<<output<<endl;
    }
    
    delete connect;
    delete distance;
    delete visited;
    delete prev_node;
    
}