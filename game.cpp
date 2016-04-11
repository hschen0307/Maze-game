#include "game.h"
//Hsuan-Chih, Chen
//This file defines all functions game, Level_1 and Level_2 class.
game::game(){}//constructor
game::~game(){}//destructor
void game::start_game(){}//virtual function for starting a game to Level_1 or Level_2


 
Level_2::Level_2(){}//constructor
Level_2::~Level_2(){}//destructor
//start a game, it offer players to play a graph maze. Players have equally initial lives and prizes to get one exit. there is randomly pitfalls and treasure places making players lose lives or win prizes.
void Level_2::start_game()
{
    int hold = 0; //store a number fot keeping the while loop working
    int direction = 0; //store a direction number
    int players = 0;//store total number of players
    haha.create();//create a maze
    cout<<"How many players??"<<endl;
    cin>>players; cin.ignore(100,'\n');
    player* playerlist = new player[players];	//open a list to store player objects.
    for(int i=0;i<players;++i)	//add players information
    {
    	playerlist[i].add_a_player();
    }
    for(int i=0;i<players;++i)	//set every player to play the game
    {
	cout<<"\n-----Player "<<i+1<<" ------\n";
	playerlist[i].display();
	haha.start_point();	//set the start point
	hold = 0;	
    	while(hold==0)
    	{	
		haha.display_curlist();	//display all avaliable directions of the current vertex
		cout<<"which direction do you want to go? : "<<endl;
		cin>>direction; cin.ignore(100,'\n');
		if(!haha.select_direction(direction))	//check the input
		{
			cout<<"You type wrong direction. Please "<<endl;
		}
		else
		{	
			hold = right_direction(playerlist[i]);
		}
    	}
    }
    display_playerlist(playerlist,players);//display all players' scores
    display_maze();	//display the maze
    if(playerlist)	//delete dynamic memory
    {
	delete [] playerlist;
    }
}
//display all players' scores
void Level_2::display_playerlist(player* playerlist,int players)
{
	cout<<"\n===Every player final scores===\n"<<endl;
	if(playerlist)
	{
		for(int i=0;i<players;++i)
		{
			playerlist[i].display();
			playerlist[i].display_scores();
		}
	}	
}
//display the maze and the exit of the maze
void Level_2::display_maze()
{
	char choice = '0';
	cout<<"\nSee the maze and exit (y/n): ";
	cin>>choice; cin.ignore(100,'\n');
	if(choice == 'y')
	{	
		haha.display_all();
	}
}
//combine all steps of right input in this function.(player type in right input)
int Level_2::right_direction(player& a_player)
{
	int hold = 0; //store a number fot keeping the while loop working
    	int prize = 0; //store result from lose_get() 
    	int point = 0;//store value of points to add
	if(haha.check_exit())	//check whether the current is the exit or not 
	{
		cout<<"\nIt's the exit !! Congrat!!\n"<<endl;
		a_player.display();
		a_player.display_scores();
		hold = -1;
	}
	else
	{
		prize = haha.lose_get(); //decide there is pitfall, treasure place, or nothing.
		if(prize == 1)	//treasure place
		{
			point = haha.random_points();
			a_player.add_prize(point); //add points to a player
			cout << "\nThere is a treasure place. "<<endl;		
			cout << "\nYou get " << point << " prize(s)"<<endl;
			if(a_player.extra_life()) //if prizes is over 10, a player can get 1 more life
			{
				cout<<"\n Your Prizes are over ten. You get 1 more life. " <<endl; 
			}	
			a_player.show_life_prize();
		}
		else if(prize == 2) //pitfall
		{
			cout<<"\nThere is a pitfall. So You lose 1 life"<<endl;
			a_player.lose_life(); //minor a life of player
			a_player.show_life_prize();
			if(!a_player.check_life())	//check the life of a player 
			{
				cout<<"----------\nGame Over.\n---------"<<endl;
				a_player.display();
				a_player.display_scores();
				hold = -1;
			}
		}
	}
	return hold;
}



//constructor
Level_1::Level_1(){}
//destructor
Level_1::~Level_1(){}
//start a game, it offer players to play a maze_t. Players have equally initial lives and prizes to get one exit. there is randomly pitfalls and treasure places making players lose lives or win prizes.
void Level_1::start_game()
{
	int players = 0; //store total number of plays
	int total = 12;	//set total nodes in a maze_t
	int direction = 0; //store direction user types.
	int hold = 0; //control the while loop to be stop or keep looping
	cout<<"How many players??"<<endl;
	cin>>players; cin.ignore(100,'\n');
	player* playerlist = new player[players];	//open a list to store player objects.
	insert_players(playerlist,players);		//input name and background for each players
	haha.generator(total);		//create a maze_t.
    	for(int i = 0;i<players;++i)	//for making each player play the same maze_t
    	{
		playerlist[i].display();
		haha.start_maze_t();	//set start point. (so each one is the same.)
		hold = 0; 		
		while(hold == 0)
		{
			cout<<"1. right 2.left 3.back: ";
			cin>>direction;
			cin.ignore(100,'\n');
			if(direction == 1)
			{
				hold = choose_right(playerlist[i]);
			}
			else if(direction == 2)
			{
				hold = choose_left(playerlist[i]);
			}
			else if(direction == 3)
			{
				if(!haha.go_back())
				{
					cout<<"there is no back. "<<endl;
				}
			}
			else	//uncorrect input
			{
				cout<<"You type a wrong option. Please type it again."<<endl;
			}
			cout<<"-----------------------------"<<endl;	
		 }
		 haha.reset_flags();	//reset all nodes' flags for next player replaying
     	}
	display_playerlist(playerlist,players);	//display all players final results 
	if(playerlist)	//delete dynamic memory
	{
		delete [] playerlist;
	}	
}
//combine all steps of choosing right in this function. (user choose going right direction)
//output:: number for hold
int Level_1::choose_right(player & xuan) 
{
	int prize = 0; //store result from lose_get() 
	int point = 0;	//store value of points to add
	int hold = 0; //control the while loop to be stop or keep looping
	if(!haha.go_right()) 	//if there is no road 
	{
		cout<<"\n there is a dead-end. "<<endl;
		cout<<"\nYou lose 1 life"<<endl; 
		xuan.lose_life();
		xuan.show_life_prize();
		if(!xuan.check_life()) //if there is no life. game over 
		{
			cout<<"--------\nGame Over.\n---------"<<endl;
			hold = -1;
		}
	}
	else	//there is a road
	{
		if(haha.check_exit()) //check it is a exit or not
		{	
			cout<<"---------\nYou find the exit !!!\n-----------"<<endl;
			xuan.display();
			hold = -1;
		}
		else
		{
			prize = haha.lose_get(); //decide there is pitfall, treasure place, or nothing.
			if(prize == 1)	//treasure place
			{
				point = haha.random_points();
				xuan.add_prize(point); //add points to a player
				cout << "\nThere is a treasure place. "<<endl;		
				cout << "\nYou get " << point << " prize(s)"<<endl;
				if(xuan.extra_life()) //if prizes is over 10, a player can get 1 more life
				{
					cout<<"\n Your Prizes are over ten. You get 1 more life. " <<endl; 
				}	
				xuan.show_life_prize();
			}
			else if(prize == 2) //pitfall
			{
				cout<<"\nThere is a pitfall. So You lose 1 life"<<endl;
				xuan.lose_life(); //minor a life of player
				if(!xuan.check_life())
				{
					cout<<"----------\nGame Over.\n---------"<<endl;
					hold = -1;
				}
				xuan.show_life_prize();
			}	
		}
	}
	return hold; //return hold for control while loop outside
}
//combine all steps of choosing left in this function. user choose going left direction.
int Level_1::choose_left(player & xuan)
{
	int prize = 0; //store result from lose_get() 
	int point = 0;	//store value of points to add
	int hold = 0; //control the while loop to be stop or keep looping
	if(!haha.go_left()) //there is no road(dead-end)
	{
		cout<<"\n there is a dead-end. "<<endl;
		cout<<"\nYou lose 1 life"<<endl;
		xuan.lose_life();
		xuan.show_life_prize();
		if(!xuan.check_life())
		{
			cout<<"-------\nGame Over\n.---------"<<endl;
			hold = -1;
		}
	}
	else
	{
		if(haha.check_exit())//check it's a exit or not
		{
			cout<<"------------\nYou find the exit !!! Congrats!!\n--------------"<<endl;
			xuan.display();
			hold = -1;
		}
		else	//not a exit
		{
			prize = haha.lose_get();
			if(prize == 1) 
			{
				point = haha.random_points();
				xuan.add_prize(point);
				cout << "\nThere is a treasure place. "<<endl;		
				cout << "\nYou get " << point << " prize(s)"<<endl;
				if(xuan.extra_life())
				{
					cout<<"\n Your Prizes are over ten. You get 1 more life. " <<endl; 
				}	
				xuan.show_life_prize();
			}
			else if(prize == 2)
			{
				cout<<"\nThere is a pitfall. So You lose 1 life"<<endl;
				xuan.lose_life();
				if(!xuan.check_life())
				{
					cout<<"------------\n Game Over.\n------------ "<<endl;
					hold = -1;
				}
				xuan.show_life_prize();
			}
		}
	}
	return hold;//return hold for control while loop outside

}
//insert information of each player in a playerlist. 
void Level_1::insert_players(player* & playerlist, int players) 
{
	for(int i;i<players;++i)
	{
		playerlist[i].add_a_player();
	}
}
//display every player's information in a playerlist.
void Level_1::display_playerlist(player* playerlist,int players_num)
{
	cout<<"\n===Every player final scores===\n"<<endl;
	if(playerlist)
	{
		for(int i=0;i<players_num;++i)
     		{
			playerlist[i].display();
			playerlist[i].display_scores();
     		}
	}
}


















