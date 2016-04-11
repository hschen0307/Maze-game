#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>
using namespace std;
//Student:Hsuan-Chih, Chen
//this file declares all function prototypes and protected members in  node, tree, and maze_t classes.
//node class
//this class manages all functions of one single node.

class node
{
      public:
	     node();//constructor
	     node(node* in_left, node* in_right, int in_index);//argument constructor
	     ~node();//destructor	
             node *& go_left();//return a left child point by referece
             node *& go_right();//return a left child point by referece
	     void change_index(int index);//change index number of a node in protected members
	     int return_index();//get index number of a node in protected members
	     void change_flag();//change flag from 0 to 1
	     int return_flag();//return a flag's value
	     void reset_flag();//reset flag from 1 to 0
	     void display();//display a node's index number
      protected:
	     node * left; //store node's left child
	     node * right; //store node's  right child
	     int index_num;//store a index number
	     int flag;	//store a flag to record the position a player already passed
};



//tree class
//this class manages data structure of a binary search tree,
class tree
{
	public:
		tree();	//constructor
		~tree();//destructor
		tree(const tree & source);//copy constructor 
		void copy_tree(node * & result, node * source);
		void delete_all_nodes(node* &root); //delete all nodes in the maze_t
		void insert(node*& root,int index_num);//insert a node
		void display();	//wraper display function
		void display(node* root);//display all nodes of a tree recursively      
		int retrieve(node* root, node*& to_find,int index);//get a node position by its index number
		int remove(int num);//find the node by a number and delete it
		void delete_node(node*& root); //delete a node in tree
	protected:
		node* root; //store tree's root(start point)
};



//maze_t class
//this class manages functions to track a player's position and give some randomly prizes and pitfalls.
class maze_t:public tree //maze is derived from tree
{
	public:
		maze_t();//constructor
		~maze_t();//destructor
		
		maze_t(const maze_t & source); //copy constructor 
		void generator(int total_nodes); //produce a maze_t
		void start_maze_t(); //reset a player position to be start point  
		int go_right();//move to itself right child  
		int go_left();//move to itself child
		int go_back();//(wraper function)move back to the last positon
		int go_back(node* root,node* &current);//move back to the last position.   
		void show_position(); //display a player's current position
	        int check_exit(); //check whether current position is maze_t's exit or not
		int lose_get();//decide a node which is losing life or getting point 
		int random_points();//give a ramdom number for adding points
		void reset_flags();//(wraper)reset all nodes' flags to be zero
		void reset_flags(node*& root);//recusively reset all flags to be zero
	protected:
		node* current;//use a pointer to point current postion(player)
		int exit_num;//store number of exit node 
		
};





