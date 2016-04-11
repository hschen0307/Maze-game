#include "maze_g.h"
#include "maze_t.h"
#include "player.h"
using namespace std;
//Student:Hsuan-Chih, Chen
//this file declares all function prototypes and protected members in game, Level_1, Level_2 classes.
//game class
//a abstract base class to Level_1 and Level_2
class game
{
	public:
		game();//constructor
		virtual ~game();//destructor
		virtual void start_game()=0;//virtual function for starting a game to Level_1 or Level_2
	protected:
};



//Level_1 class
//manage all functions for players to play Level_1.
class Level_1:public game
{
	public:
		Level_1();//constructor
		~Level_1();//destructor
		void start_game();//start a game(virtual)
		int choose_right(player & xuan); //combine all steps of choosing right in this function. (user choose going right direction.)
		int choose_left(player & xuan); //combine all steps of choosing left in this function. user choose going left direction.
		void insert_players(player* & playerlist, int players);//insert information of each player in a playerlist. 
		void display_playerlist(player* playerlist,int players_num);//display every player's information in a playerlist.
	protected:
		maze_t haha; //store a object of the tree maze
};



//Level_1 class
//manage all functions for players to play Level_2.
class Level_2:public game
{
	public:
		Level_2();//constructor
		~Level_2();//destructor
		void start_game();//start a game(virtual)
		int right_direction(player& a_player);
		void display_playerlist(player* playerlist,int players);//display every player's information in a playerlist.
		void display_maze();//display the maze
	protected:
		maze haha;//store a object of the gragh maze
};
