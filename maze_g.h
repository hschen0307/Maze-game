#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>
using namespace std;
//Student:Hsuan-Chih, Chen
//this file declares all function prototypes and protected members in  edge, tree, and maze classes.
//edge class
//this class manages all functions of one single edge.
class edge
{
	public:
		edge();//default constructor
		~edge();//destructor
		edge *& go_next();//get the next edge of a current eage.
		class vertex*& go_adjacent();//get the next adjacent of a current vertex
		void change_index(int index);//change index number of a edge in protected members
		void change_flag();//change flag from 0 to 1
		int return_flag();//return a flag's value of a vertex(adjacent)
		void reset_flag();//reset flag of vertex from 1 to 0 
		void display();//display a adjacent vertex's index number
		void display_adj();//display adjacenct vertex in a edg
		void change_adj(int to_go,vertex* adjacency_list);//change adjacent's address to be another vertex address  
		int check_vertex();//get edge's vertex(adjacent)'s index value
		//int return_adj();
	protected:
		vertex * adjacent; //vertex pointer, store a vertex's address
		edge * next;//edge pointer, store the next edge
};



//vertex  class
//this class manages all functions of one single vertex.
class vertex
{
	public:
		vertex();//default constructor
		~vertex();//destructor
		int return_head();//check vertex's head edge is not NULL
	        edge*& go_head();//get vertex's edge head's address by reference
		void change_index(int num);//change vertex's index number
		int return_index();//get vertex's index number
		void display();//display the index number of a vertex
		void display_list();//display a vertex's edge list.
		int check_edges(int vertex);//check whether one index number is in vertexes of edge list or not
		void change_flag(); //change vertex's flag value to be 1
		int return_flag();//get vertex's flag value
		void reset_flag();////reset vertex's flag to be 0	
	protected:
		edge* head;//edge's head pointer of a vertex
		int index;//store index number in each vertex
		int flag;//store flag value in each vertex
};



//class graph
//this class is maze's base class. it manage graph's functions and can support maze to use its functions
class graph
{
	//prototypes
	public:
		graph(int size);//constructor
		~graph();//destructor
		void insert_edge(int current_vertex,int to_attach); //Attach an edge to a vertex
		void depth_first(edge* start);//depth first traversal in a graph from a start edge
		int same_index(int num);//check a number is already in the adjacency list or not
		void reset_flags();//make all flags to be zero 
	protected:
		vertex * adjacency_list; //create a adjacency list dynamically
		int list_size;	       //store the list size
};



//class maze
//this class is graph's derived class. it manage all functions for the maze
class maze:public graph
{
	public:
		maze();//constructor
		~maze();//destructor 
		void create();//create a maze
		int random_num();//generate random number
		int select_direction(int to_go);//move in the graph maze
		int find_location(int to_go);//find the adjacency list location number
		void display_curlist();//display the all available directions from the current location 
		void start_point();//set the start point
		int check_edges(int vertex);//check the index number is the edge list or not
	        int check_exit();//check whether is the exit.
		int lose_get();//decide the location is a pitfall ot a treasure place
		int random_points();//give random prizes
		void display_all();//display the maze and the exit
	protected:
		int exit;//store the exit index number
		vertex* current;//point to the current location of a player
};
