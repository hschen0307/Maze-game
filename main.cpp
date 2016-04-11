#include "game.h"
//Hsuan-Chih, Chen
//2015.7.9
//this program offer players to play a Leve1_1(tree) or Level_2(graph) maze by using dynamic binding. Players have equally initial lives and prizes to get one exit. there is randomly pitfalls and treasure places making players lose lives or win prizes.  
int main()
{
	int choice = 0;//store player's choice
	int hold = 0;//store a number for control while looping
	game* ptr;//game pointer, for pointing game's derived class function(virtual)
	while(hold == 0)
	{
		cout<<"Which level do you would like to play ? "<<endl;
		cout<<" 1. Level_1(tree maze) 2. Level_2(graph maze) 3.Exit: "; 
		cin>>choice;	cin.ignore(100,'\n');
		if(choice == 1 || choice == 2)
		{
			if(choice == 1)
			{
				ptr = new Level_1;	//point and create a Level_1 type object(dynamically)
				//ptr->start_game();	//use Level_1 virtual function
				//delete ptr;		//delete the Level_1 type dynamic object memory
			}
			else if(choice == 2)
			{
				ptr = new Level_2;	//point and create a Level_2 type object(dynamically)
				//ptr->start_game();	//use Level_2 virtual function
				//delete ptr;		//delete the Level_2 type dynamic object memory
			}
			ptr->start_game();
			delete ptr;
		}
		else
		{
			hold = -1;		//exit
		}
	}
	return 0;
}
