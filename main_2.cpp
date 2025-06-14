#include<iostream>
#include<fstream>
#include<string>

using namespace std;

//file properties
struct file_bench{
    int displacement;
    int out_pos;
    int intermediate_pos;
    int max_fanout;
};

//adjacent vertex
struct adjacent_node{

    string vertex;
    int weight;
    struct adjacent_node *next;

    adjacent_node(string ad_vertex, int size){

        vertex = ad_vertex;
        weight = size;
        next = NULL;

    }
};

//Vertex
struct node{

    bool filled;
    string vertex;
    struct node *next;
    struct adjacent_node *adj_next;
    node (string node){
        filled = 0;
        vertex = node;
        next = NULL;
        adj_next = NULL;

    }
};

//To implement adjacency list
class Graph{
    struct node *front, *rear, *tmp_head, *tmp_addr;
    struct adjacent_node *head, *tmp_header;

    public:
    Graph(){

        front = rear = tmp_head = NULL;
        head = tmp_header = NULL;

    }

    //To Enqueue Vertex
    void Graph_enqueue(string vertex){
        struct node *temp = new node (vertex);
        if (rear == NULL){
            front  = rear = temp;
        }
        else{
            rear -> next = temp;
            rear = temp;
        }

    }

    //To push the adjacent nodes
    void Graph_push(string adj_vertex, int weight){

        struct adjacent_node *temp = new adjacent_node(adj_vertex, weight);
        temp->next = tmp_head->adj_next;
        tmp_head->adj_next = temp;

    }

    bool check_f_r(){
        bool found = false;
        if (front == NULL){
            return true;
        }
        return found;
    }
    
    //Set the pointer to the vertex that needs to be linked
    //with adjacent nodes
    bool set_tmp_head (){
        tmp_addr = front;
        bool found =false;
        while (tmp_addr != NULL){
            if (tmp_addr -> filled == 0){
                tmp_head = tmp_addr;
                found = true;
                break;
            }
            else{
                tmp_addr = tmp_addr->next;
            }
        }
        return found;
        
    }

    //To check if vertex is already enqued
    bool check_queue (string adj_vertex){
        bool found = false;
        tmp_addr = front;
        while (tmp_addr != NULL){
            if (tmp_addr->vertex == adj_vertex){
                found = true;
                break;
            }
            else{
                tmp_addr = tmp_addr->next;
            }
        }
        return found;
    }

    //If vertex is linked with all of its adjacent nodes
    //the vertex node is filled
    void filled_vertex(){

        tmp_head -> filled = 1;

    }

    //Returns Vertex name
    string return_vertex(){
        return tmp_head -> vertex;
    }

    //To visualize adjacency list
    void print_graph(){
        tmp_addr = front;
        while (tmp_addr != NULL){

            cout<<tmp_addr->vertex<<" ----> ";
            
            tmp_header = tmp_addr->adj_next;
            while (tmp_header != NULL){
                cout<<tmp_header->vertex<<", "<<tmp_header->weight<<" ----> ";
                tmp_header = tmp_header->next;
            }
            cout<<endl;
            tmp_addr = tmp_addr->next;
        }
    }

    //Count number of vertices in adjacency list
    int get_no_vertices (){
        int count = 0;
        tmp_addr = front;
        while (tmp_addr != NULL){
            ++count;
            tmp_addr = tmp_addr->next;
        }
        return count;

    }

    //Set a pointer to the 1st adjacent vertex of a node in the queue
    void set_tmp_adj_header(int min_pos){

        int count = 0;
        tmp_addr = front;
        while (tmp_addr != NULL && count < min_pos){
            tmp_addr = tmp_addr->next;
            ++count;

        }
        tmp_header = tmp_addr -> adj_next;


    }

    //Tests if all the adjacent nodes are read
    bool check_adj_header (){
        if (tmp_header == NULL){
            return false;
        }
        else{
            return true;
        }
    }

    //Get position of a vertex in queue
    int get_pos(){
        int count = 0;
        bool found = false;
        tmp_head = front;
        while (tmp_head != NULL && found ==0){
            if ((tmp_head->vertex).compare(tmp_header->vertex) == 0){
                found = 1;
            }
            else{
                ++count;
                tmp_head = tmp_head->next;
            }
        }
        return count;
    }

    //Extract edge weight from adjacent nodes in the adjacency list
    int get_edge_weight(){
        int weight;
        weight = tmp_header->weight;
        return weight;
    }

    //Shifts the pointer to the next node in the queue
    void shift_adj_header(){
        tmp_header = tmp_header->next;
    }

    //Find the output position in the list
    int get_pos_output(string output){
        
        int count = 0;
        bool found = false;
        tmp_head = front;
        while (tmp_head != NULL && found ==0){
            if ((tmp_head->vertex).compare(output) == 0){
                found = 1;
            }
            else{
                ++count;
                tmp_head = tmp_head->next;
            }
        }
        return count;

    }

    //Extract the vertex label based on the order of its position in the queue
    string get_veretx_name(int pos){

        int count = 0;
        tmp_addr = front;
        while (tmp_addr != NULL && count < pos){
            tmp_addr = tmp_addr->next;
            ++count;

        }
        return tmp_addr->vertex;       
        
    }

    //Destructor: To free the pointers
    ~Graph(){

        tmp_addr = front;
        while (tmp_addr != NULL){
            
            tmp_header = tmp_addr->adj_next;
            while (tmp_header != NULL){
                tmp_addr->adj_next = tmp_header->next;
                delete tmp_header;
                tmp_header = tmp_addr->adj_next;
            }
            front = tmp_addr->next;
            delete tmp_addr;
            tmp_addr = front;
        }
        delete front;

    }

};

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
    //To Print adjacency list
    //call below fuction
    //G.print_graph();
    Dijkstra (G, output);

    file.close();   
    return 0;
}
