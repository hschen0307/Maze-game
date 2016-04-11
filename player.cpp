#include "player.h"
//Hsuan-Chih, Chen
//this file define all functions of prize, life, and player classes. 
//default constructor 
prize::prize()
{
	points = 0; //set initial prizes to be 0.
}
//argument constructor 
//input:: number of points
prize::prize(int in_prize)
{
	points = in_prize;
}
//copy constructor
prize::prize(const prize & to_copy)
{
   	points = to_copy.points;
}
//copy function: for player's copy constructor 
//input:: prize object
void prize::copy_prize(const prize & to_copy)
{
	points = to_copy.points;
}
//destructor
prize::~prize(){}
//add more values to prizes
//input:: number of prizes
void prize::add_prize(int add_point)
{
	points = points + add_point;
}
//display prize
void prize::display()
{
	cout<<"prize : " << points << endl;
}
//check whether prizes is over 10. if it is over 10, it will make points minor 10
//output:: 1, if prizes is over 10. 0, if prizes is less than 10.
int prize::check_prize()
{
	if(points>10)
	{
		points = points - 10;
		return 1;
	}
	else
	{
		return 0;
	}
}
//get current prize's value
//output:: points' value
int prize::return_points()
{
	return points;
}



//default constructor	
life::life()
{
	blood = 3; //set initial life to be 8.
}
//argument constructor 
life::life(int initial_life)
{
	blood = initial_life;
}
//copy constructor
life::life(const life & to_copy)
{
	blood = to_copy.blood;
}
//destructor
life::~life(){}
//minor 1 of player's life 
void life::lose_life()
{
	blood = blood - 1;
}
//add 1 of player's life
void life::add_life()
{
	blood = blood + 1;
}
//display life
void life::display()
{
	cout<<"life : " << blood << endl;
}



//default constructor
player::player()
{
	name = NULL;
	background = NULL;
}
//argument constructor
//input:: name, background, life, and prize
player::player(char* in_name, char* in_background,int in_life, int in_prize):life(in_life),my_prize(in_prize) //use initialization list 
{
	//do deep copy of player's data member
	if(in_name)
       	{
            name = new char[strlen(in_name)+1];
            strcpy(name,in_name); 
       	}
	if(in_background)
	{
	    background = new char[strlen(in_background)+1];
	    strcpy(background,in_background);
	}
}
//copy constructor
//input:: a player object
player::player(const player & to_copy):life(to_copy) //initialization list
{
       //deep copy
       if(to_copy.name)
       {
            name = new char[strlen(to_copy.name)+1];
            strcpy(name,to_copy.name); 
       }
       if(to_copy.background)
       {
            background = new char[strlen(to_copy.background)+1];        
            strcpy(background,to_copy.background);
       }
       my_prize.copy_prize(to_copy.my_prize); //copy prize object
}
//destructor
player::~player()
{
	if(name)
	{	
		delete [] name;
	}
	if(background)
	{
		delete [] background;
	}
}
//input a player's name and background to a player object
void player::add_a_player()
{
	char a_name[50];
	char a_background[100];	
	cout<<"Please type your name : " <<endl;
	cin.get(a_name,50,'\n'); cin.ignore(100,'\n');
	cout<<"Please type your background : " <<endl;
	cin.get(a_background,100,'\n'); cin.ignore(100,'\n');
	name = new char[strlen(a_name)+1];	//use dynamic memory to store
	background = new char[strlen(a_background)+1];
	strcpy(name, a_name);
	strcpy(background,a_background);
}
//add values of prizes from player class to prize class
//input:: number of prizes
void player::add_prize(int add_point)
{
	my_prize.add_prize(add_point);
}
//display all player's information and scores.
void player::display()
{
	cout<<"---------------------------"<<endl;
	cout<<"Name : " << name <<endl;	       
	cout<<"Background : " << background <<endl;
	cout<<"life : " << blood << endl;
	my_prize.display();	
	cout<<"---------------------------"<<endl;
}
//display current life and prize
void player::show_life_prize()
{
	cout<<"---------------------------"<<endl;
	cout<<"life : " << blood << endl;
	my_prize.display();
	cout<<"---------------------------"<<endl;
}
//check whether a player still has life or not
//output:: 0 , life is zero. 1, life is not zero
int player::check_life()
{
	if(blood == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
//if a player's prize is over 10, add 1 life for a player
//output:: 1, add 1 life. 0, prizes is not over 10; 
int player::extra_life()
{
	if(my_prize.check_prize()) //call prize's function to check prizes number
	{
		
		add_life();	//add 1 life
		return 1;	
	}
	else
	{
		return 0;
	}
}	
//calculate total scores of a player. 1 life equals 10 scores. 1 prize equals 1 score.
//output:: scores
void player::display_scores()
{
	cout << "Total scores : " <<blood * 10 + my_prize.return_points() <<endl;
}
