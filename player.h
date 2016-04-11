#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>
using namespace std;
///Student:Hsuan-Chih, Chen
//this class declares all function prototypes and protected members in prize, life, and player classes.
//prize class
//this class manages all functions about prizes for players.
class prize
{
	public:
		prize(); //constructor
		prize(int in_prize); //argument constructor
		prize(const prize & to_copy); //copy constructor
		~prize();	//destructor
		void add_prize(int add_point); //add points to a player
		void display();//display points protected member
		void copy_prize(const prize & to_copy);
		int check_prize();//check total current prizes
		int return_points();//get points' values of protected member
	protected:
		int points; //store (player's) points
};



class life
{
	public:
		life();//constructor
		life(int initial_life);//argument constructor
		life(const life & to_copy);//copy constructor
		~life();//destructor
		void lose_life();//let blood value -1
		void add_life();//let blood value +1
		void display();//display blood value
	protected:
		int blood; //stores (player's) life

};



//The player class is derived from a life but "has" an prize. For avoiding multiple inheritance. 
class player:public life		//a derivation list
{
      public:
             player();//constructor
             player(char* in_name, char* in_background,int in_life,int in_prize);//argument constructor
             player(const player & to_copy);//copy constructor
	     ~player();//destructor
             void add_prize(int add_point);//add points to player's points of the prize class
	     void display();   //display name, background,life,prize,and scores of a player
	     void show_life_prize(); //display life and prize
	     int check_life();	//check whether life is 0 or not	
	     void add_a_player(); //input name and background to a player object
	     int extra_life();	//add 1 life if prize is over 10 points 
	     void display_scores();	//display total scores 
      protected:
             prize my_prize;	//player has a prize object 
	     char* name;	//player's name
	     char* background;	//player's background
}; 
