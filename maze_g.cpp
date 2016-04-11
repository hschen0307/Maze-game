#include"maze_g.h"
//Hsuan-Chih, Chen
//This file defines all functions in edge, graph and maze class.
//default constructor
edge::edge()
{
    adjacent = NULL;
    next = NULL; 
}
//destructor
edge::~edge(){}
//go next function: to get edge itself next edge position by reference
//output:: edge's next edge by reference
edge*& edge::go_next()
{
	return next;
}
//change edge's vertex(adjacent)'s index number
void edge::change_index(int index)
{
	adjacent->change_index(index);
}
//change edge's vertex(adjacent)'s flag
//change flag value to 1
void edge::change_flag()
{
	adjacent->change_flag();
}
//reset edge's vertex(adjacent)'s flag
//change flag value to 0
void edge::reset_flag()
{
	adjacent->reset_flag();
}
//display edge's vertex(adjacent)'s data members
void edge::display_adj()
{
	adjacent->display();
}
//get edge's vertex(adjacent)'s index value
//output::vertex's index number
int edge::check_vertex()
{
	return adjacent->return_index();
}
//get edge's vertex(adjacent)'s address by reference
//output::vertex(adjacent)'s address by reference
vertex*& edge::go_adjacent()
{
	return adjacent;
}
//get edge's vertex(adjacent)'s flag value(0 or 1)
//output: flag value(1 or 0)
int edge::return_flag()
{
	return adjacent->return_flag();
}
//change adjacent's address to another vertex(to_go)
void edge::change_adj(int to_go,vertex* adjacency_list)
{
	adjacent = adjacency_list + to_go;
}



//default constructor
vertex::vertex()
{
	head = NULL;
	index = 0;
	flag = 0;
}
//destructor
vertex::~vertex(){}
//if vertex's head edge is not NULL, return 1. 
//if head is NULL return 0
int vertex::return_head()
{	
	if(!head)
		return 0;
	return 1;
}
//get vertex's index number
//output:: index number
int vertex::return_index()
{
	return index;
}
//get vertex's edge head's address by reference
//output:: vertex's edge head's address by reference
edge*& vertex::go_head()
{
	return head;
}
//display a vertex's edge list.
void vertex::display_list()
{   
	if(head) //if head is not NULL
	{
		edge* current = head;
		while(current)	//traverse the edge list
		{
			current->display_adj();	//call edge display function
			current = current->go_next(); 
		}
	}
}
//check whether one index number is in vertexes of edge list or not//input:: index number
//output:: 1, the index number is in the vertex of edge list. otherwise, 0. 
int vertex::check_edges(int vertex)
{
	if(head)
	{
		edge* current = head;
		while(current)
		{
			if(current->check_vertex()==vertex)//call edge's function to get each edge's vertex's index number.
			{
				return 1;//get match return 1
			}
			current = current->go_next();
		}
		return 0;
	}
	return 0;
}
//change vertex index number
//input::index number
void vertex::change_index(int num)
{
	index = num;
}
//display the index number of a vertex
void vertex::display()
{
	cout<<index<< "  " ;
}
//get vertex's flag value
//output::flag's value(0 or 1)
int vertex::return_flag()
{
	return flag;
}
//change vertex's flag value to be 1
void vertex::change_flag()
{
	flag = 1;
}
//reset vertex's flag to be 0;
void vertex::reset_flag()
{
	flag = 0;
}



//constructor
//inicialize all private members
graph::graph(int size)//we can put size from maze(derived class)'s constructor initialization list.
{
      //Allocate the adjacency list 
      list_size = size;
      adjacency_list = new vertex[list_size];	
}
//destructor
//deallocate all dynamic memory
graph::~graph()
{
	for(int i=0; i<list_size; ++i)
	{
		edge* current = adjacency_list[i].go_head();	//delete all edge lists
		edge* temp = NULL;
		while(current)
		{
			temp = current;
			current = current->go_next();
			temp->go_adjacent() = NULL;
			delete temp;
		}
	}
	delete [] adjacency_list;    //delete the adjacency_list
}
//Attach an edge to a vertex
//input:: number of a current vertex, number of another vertex 
//output::success,1. fail,0.
void graph::insert_edge(int current, int to_attach)
{
       edge* temp = new edge;//add a new edge to a edge list of a vertex
       temp->change_adj(to_attach,adjacency_list);	//store attach vertex's address in the adjacent pointer of the edge .
       temp->go_next() = adjacency_list[current].go_head();//connect(add the beginning of the edge list)
       adjacency_list[current].go_head() = temp;//set the temp to be head
}
//if the input number is already in the adjacency list return 1
//input:: index number 
//output:: 1, number is already in the adjacency_list.
//otherwise, return 0.
int graph::same_index(int num)
{
	for(int i = 0;i<list_size;++i)
	{
		if(adjacency_list[i].return_index()== num)
		{
			return 1;
		}
	}
	return 0;
}
//Recursively function to display every edge in all edge lists.
//input::A edge pointer
//output::none
void graph::depth_first(edge* start)
{
	if(!start)
	{
		return;
	}	
	if(start->return_flag()==0)	//if the vertex haven't displayed(flag = 0), then display it and set its flag to be 1.
	{
		start->display_adj();
		start->change_flag();
		depth_first(start->go_adjacent()->go_head());	//for depth first traversal, directly go to another eage list first.
	}
	depth_first(start->go_next());			//if the edge already display, then go to the next edge in the same edge list. 
}
//reset all flags in adjacency list to be zero.
void graph::reset_flags()
{
	for(int i = 0;i<list_size;++i)
	{
		adjacency_list[i].reset_flag();
	}
}




//default constructor
maze::maze():graph(15) //set graph adjacency list size to be 15(inicialize list)
{
	current = NULL;
}
//destructor
maze::~maze(){}
//create a maze by using random number build the adjacency list. Set the last vertex is the exit. 
void maze::create()
{
	int num=0; //store a random number
	int edges=0;//store a certain total nodes' number for a edge list 
	int count = 0;//store current total nodes' number of the edge list
	srand((unsigned)time(0));//with rand(), produce random number
	for(int i = 0; i< list_size;++i)
	{	
	   do{
		num = (rand()%15)+1;
	      }while(same_index(num)); //check wether the same index number is already in the list or not. 
		if(i==list_size-1) //set the last vertex to be the exit 
		{
			exit = num;	
		}
		adjacency_list[i].change_index(num); //set the number to be one index number of adjacency list
	} 		
	int j = 0; //store a attching number 
	srand((unsigned)time(0));	
	for(int i = 0; i<list_size-1; ++i) //list_size-1, I don't want the exit vertex to attach to any vertex
	{			
		edges = adjacency_list[i].return_index()%5; //decide how many edges need to be added, at most 5.
		count = 0;
		while(count <edges+1)
		{
			j = rand()%list_size;//decide which vertex need to be added
			if(j != i && adjacency_list[j].return_flag()==0)//if the attaching vertex is the current vertex itself or it already be added in the same edge, we don't add it in the edge
			{
				insert_edge(i,j);//add edge in the edge list
				adjacency_list[j].change_flag(); //set the vertex already added
				++count;
			}
		}
		reset_flags();//reset all flags for next adding	
	}
}
//generate random number
//output:: a random number
int maze::random_num()
{
	srand((unsigned)time(0));		
	return rand();
}
//decide a vertex is a pitfall or a treasure place by index_num of the vertex.
//output:: 0, do nothing. 1, it's a a treasure place. 2, a pitfall
int maze::lose_get()
{
	return current->return_index()%3; //use mod get 3 results to decide	
}
//produce random numbers for giving players random prizes when geting a treasure place
//output:: 10, if points' number equals 0. Points.  
int maze::random_points()
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
//display the graph maze and the exit number 
void maze::display_all()
{
	cout<<"\nThe exit is : " << exit <<endl;
	cout<<"\nThere is the maze of graph."<<endl;
	for(int i = 0;i<list_size;++i)
	{
		cout<<"# "<<adjacency_list[i].return_index()<<" : ";
		adjacency_list[i].display_list();
		cout<<"\n --------------------\n";
	}
}
//let player can move in the graph maze
//input:: a index number in a vertex
//output:: 1, good input. 0, bad input.
int maze::select_direction(int to_go)
{
	int position = 0;//store the attching adjacency list location number
	position=find_location(to_go);//find the location of list
	if(position != -1 && check_edges(to_go) ==1)//check the location is in the adjacency list and also in the edge list of the certain vertex
	{
		current = adjacency_list+position;//set vertex current pointer to point to new vertex
		return 1;
	}
	else
	{
		return 0;
	}
}
//find the adjacency list location number from a vertex's index number.
//input:: vertex's index number.
//output:: the adjacency list location number. -1, the index number is not in the adjacency list 
int maze::find_location(int to_go)
{
	for(int i=0;i<list_size;++i)
	{
		if(adjacency_list[i].return_index()== to_go)
		{
			return i;
		}
	}
	return -1;
}
//check the index number is the edge list or not
//intput:: vertex's index number.
//output:: 0, the index number is not in the vertex of  the edge list. 1, the index number is in vertex of the edge list.
int maze::check_edges(int vertex)
{
	if(!current->check_edges(vertex))
	{
		return 0;
	}
	return 1;
}
//set the current to be the first vertex in the adjacency_list
void maze::start_point()
{
	current = adjacency_list;
}
//display the edge list of the current vertex
void maze::display_curlist()
{
	if(current)
		current->display_list();
}
//check the current vertex's index number is the exit or not
//output:: 1, the exit. 0, not the exit.
int maze::check_exit()
{
	if(current->return_index()==exit)
		return 1;
	return 0;
}
