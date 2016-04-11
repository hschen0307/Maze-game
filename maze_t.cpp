#include"maze_t.h"
//Hsuan-Chih, Chen
//This file defines all functions in node, tree, and maze_t class.
//default constructor
node::node()
{
    left = NULL;
    right = NULL;
    index_num = 0;
    flag = 0;
}
//argument constructor
//input:: initial node left,right, and index number
node::node(node* in_left, node* in_right, int in_index):left(in_left),right(in_right),index_num(in_index){}
//destructor
node::~node(){}
//go left function: to get node itself left child position by reference
//output:: node's left child by reference
node*& node::go_left()
{
    return left;
}
//go left function: to get node itself right child position by reference
//output:: node's right child by reference
node*& node:: go_right()
{
    return right;
}
//get node's index number
//output:: index number
int node::return_index()
{
	return index_num;	
}
//change node's index number
//input:: index number
void node::change_index(int index)
{
	index_num = index;
}
//get node's flag value(1,0)
//output:: flag value
int node::return_flag()
{
	return flag;
}
//change flag value to 1
void node::change_flag()
{
	flag = 1;
}
//change flag value to 0
void node::reset_flag()
{
	flag = 0;
}
//display node's index number
void node::display()
{
	cout<< "index_num : " << index_num<<endl;
}



//constructor
tree::tree()
{
	root = NULL;
}
//destructor
tree::~tree()
{
	delete_all_nodes(root);	
}
//copy constructor
tree::tree(const tree & source)
{
	copy_tree(root, source.root);
}
//recursively copy a binary tree
//input:: source's root, result's root
void tree::copy_tree(node * & result, node * source)
{
	if(!source)
	{
		return;
      	}
      	result = new node(*source);
      	copy_tree(result->go_left(),source->go_left());
      	copy_tree(result->go_right(),source->go_right());
}
//recursively delete a tree
//input:: a binary tree's root
void tree::delete_all_nodes(node* & root)
{
	if(!root)
	{
		return;
	}
	delete_all_nodes(root->go_left());
	delete_all_nodes(root->go_right());
	delete root;
	root = NULL;
}
//insert a node to a binary tree
//input:: a tree's root, index number of a inserted node  
void tree::insert(node*& root,int index_num)
{
	if(!root)
	{
		root = new node;	//add a new node to be leaf
		root->change_index(index_num);	//give node the index number	
		return;
	}
	if(index_num < root->return_index()) // go left when a inserted node is smaller
	{
		insert(root->go_left(),index_num); 
	}
	else		//go right when a inserted node is larger or equal.
	{
		insert(root->go_right(),index_num);
	}
}
//display a binary tree(wraper)
void tree::display()
{
	display(root);
}
//recursively diplay a binary tree
//input:: a root
void tree::display(node* root)
{
	if(root)
	{
        	display(root->go_left());
		root->display();
		display(root->go_right());
	}
}
//recursively retrieve the node by a index number
//input:: a root, a pointer to point  the position, index
//output:: 1, find. 0, not find.
int tree::retrieve(node* root, node*& to_find, int index)
{
	if(!root)
	{
		return 0;
	}
	if(index == root->return_index())
	{
		to_find = root;
		return 1;
	}
	else if(index < root->return_index())
	{
		return retrieve(root->go_left(),to_find, index);
	}
	else
	{
		return retrieve(root->go_right(),to_find, index);
	}
}
//find the node by a number(index) and delete it from a tree
//input::a number
int tree::remove(int num)
{
	node* to_find = NULL;
	if(retrieve(root, to_find, num)) //call retrieve function
	{
		delete_node(to_find); //delete the node
		return 1;
	}	
	return 0;
}
//delete a node in a tree. There are five different cases.
//input:: a node pointer
void tree::delete_node(node*& root)
{
        if(!root->go_left() && !root->go_right()) //case 1: a node is a leave
        {
                delete root;
                root = NULL;
        }
        else if(!root->go_left())            //case 2: a node just has a right child
        {
                node* temp= root;     //the pointer is for deleting
                root = root->go_right();
                delete temp;
        }
        else if(!root->go_right())           //case 3: a node just has a left child
        {
               	node* temp = root;
                root = root->go_left();
                delete temp;
        }
        else    //two child
        {
                if(!root->go_right()->go_left())  //case 4: a node's right child has no left child
                {
                        node* temp = root->go_right();
                        temp->go_left() = root->go_left();
                        delete root;
                        root = temp;
                }
                else            //case 5: a node's right child has left child(inorder successor)
                {
                        node* current = root->go_right(); //the pointer is for traversing and deleting
                        node* previous = NULL;       //the pointer is for holding the node's address before the inorder successor
                        while(current->go_left() !=NULL)
                        {
                                previous = current;
                                current = current->go_left();
                        }
                        previous->go_left() = current->go_right();
                        root->change_index(current->return_index());
                        delete current;
                 }
        }
}



//constructor
maze_t::maze_t()
{
	current = NULL;
}
//destructor
maze_t::~maze_t(){}
//copy constructor
maze_t::maze_t(const maze_t & source):tree(source) //call tree's copy constructor
{
	current = source.current; //copy data members of maze_t
	exit_num = source.exit_num;
}
//create a maze_t by producing random number for each node and insert it into a tree.
//input:: total numbers of nodes
void maze_t::generator(int total_nodes)
{
	int index;
	srand((unsigned)time(0));	//with rand(), produce random number
	for(int i = 0; i< total_nodes;++i)
	{	
		index = rand()%127;	//make number in a range from 0-126
		if(i == total_nodes - 1) //store the last inserted node's index number. for seting to be exit.
		{
			exit_num = index;
		}
		insert(root,index);	//directly call insert function in tree class(base of maze_t)
	}
}
//set start point(player initial position)  equals to root. 
void maze_t::start_maze_t()
{
	 current=root; //maze_t's protected member. tree's protected member
}
//make current to right child node
//output:: 0, if right child points to NULL. 1, point to right child node successfully.
int maze_t::go_right()
{
	if(!current->go_right())
	{
		return 0;
	}
	current = current->go_right();
	return 1;
}
//make current to left child node
//output::0, if left child points to NULL. 1, point to left child node successfully.
int maze_t::go_left()
{
	if(!current->go_left())
	{
		return 0;
	}
	current = current->go_left();
	return 1;
}
//make current go to its parent.
//output::0, no parent. 1, go back to parent successfully
int maze_t::go_back()
{
	if(!go_back(root,current))
	{
		return 0;
	}
	return 1;
}
//recusively go back function
//output:: 0, go back successfully. 1, go back unsuccessfully
int maze_t::go_back(node* root,node* &current)
{
	if(!root) //no root, stop condition
	{
		return 0;
	}
	if(root->go_right()== current || root->go_left()== current) //stop when root's left or right child is current.
	{
		current = root;	//set current points to the same place as root points
		return 1;
	}
	else 
	{
		return go_back(root->go_left(),current)+	//traverse
			go_back(root->go_right(),current);
	}	
}
//show where does the current points to 
void maze_t::show_position()
{
	current->display();	
}
//check whether e current node's index number equals to exit number.
//output:: 1, exit. 0, not the exit.
int maze_t::check_exit()
{
	if(current->return_index() == exit_num)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
//this function decides a node is a pitfall or a treasure place by index_num of the node.//output:: 0, do nothing. 1, it's a a treasure place. 2, a pitfall
int maze_t::lose_get()
{
	if(current->return_flag()==0) //if flag is 0. Player haven't visited the node
	{
		current->change_flag();//change flag to 1
		return current->return_index()%3; //use mod get 3 results to decide
	}
	else	//already visited the node
	{
		return 0;	
	}
}
//produce random numbers for giving players random prizes when geting a treasure place//output:: 10, if points' number equals 0. Points.  
int maze_t::random_points()
{
	int points = 0;
	srand((unsigned)time(0));		
	points = rand()%10;
	if(points == 0)
	{
		return 10;
	}
	else
	{
		return points;
	}
}
//reset all flags to be 0 for next player playing the same maze_t. All node's flags should be reset.
void maze_t::reset_flags()
{	
	reset_flags(root);
}
//recursively reset all flags
//input::a tree's root
void maze_t::reset_flags(node*& root)
{	
	if(!root)
	{
		return;
	}
	root->reset_flag();
	reset_flags(root->go_left());
	reset_flags(root->go_right());
}

