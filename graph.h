#include<iostream>
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