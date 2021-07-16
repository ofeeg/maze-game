#include <iostream>
#include <array>
#include <unistd.h>
#include <fstream>
//#include <ncurses.h>

std::array<char, 111> maze_arr{};
const char WALL = '#';

struct player{
  const char PLAYER = 'M';
  char location = 48;
};
unsigned int index_num = 0;

void load_maze(std::array<char, 111> &maze, std::ifstream &file); 
void clear();
char get_input();
void char_swap(char &first, char last, std::array<char, 111> &arr);
short position_checker(unsigned char location, char next);

player me{};

int main(){
  maze_arr.fill(' ');
  //maze_arr[10] = '\n';
  /*code for basic empty maze
    for(index_num; index_num < 10; ++index_num)
    {
      if(index_num > 0){
	maze_arr[(index_num * 11) - 2] = WALL;
	maze_arr[(index_num * 11)] = WALL;
	maze_arr[110 - (11 - index_num )] = WALL;
	maze_arr[(index_num * 11) - 1] = '\n';
      }
      maze_arr[index_num] = WALL;
      //std::cout << index_num << '\n';
      }*/
  std::ifstream maze_file{"maze.txt"};
  load_maze(maze_arr, maze_file);
  maze_arr[me.location] = me.PLAYER; 
  //maze_arr[110] = '\n';
  clear();
  for(unsigned int i=0; i < 110; ++i){
    std::cout << maze_arr[i];
  }
  std::cout << '\n';
  char maze_input;
  // unsigned char player_step=0;
  //maze_arr[78] = 'F';
  while(1)
    {
      maze_input = get_input();
      //switch maze_input
      std::cout << maze_input << '\n';
      char_swap(me.location, me.location+maze_input, maze_arr);
      me.location += maze_input;
      clear();
      for(unsigned int i=0; i < 110; ++i){
	std::cout << maze_arr[i];
      }
    }
  return 0;
}



void clear() {
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
};

char get_input()
{
  char i;
  std::cin >> i;
  switch(i)
    {
    case 'w':
      if(position_checker(me.location, -11) == 0) break;
      if(position_checker(me.location, -11) == 2){std::cout<<"You did it!" << std::endl; usleep(5000000); break;}
      i = -11;
      return i;
    case 'a':
      if(position_checker(me.location, -1) == 0) break;
      if(position_checker(me.location, -1) == 2){std::cout<<"You did it!" << std::endl; usleep(5000000); break;}
      i = -1;
      return i;
    case 's':
      if(position_checker(me.location, 11) == 0) break;
      if(position_checker(me.location, 11) == 2){std::cout<<"You did it!" << std::endl; usleep(5000000); break;}
      i = 11;
      return i;
    case 'd':
      if(position_checker(me.location, 1) == 0) break;
      if(position_checker(me.location, 1) == 2){std::cout<<"You did it!" << std::endl; usleep(5000000); break;}
      i = 1;
      return i;
    default:
      get_input();
    }
  return 0;
};

void char_swap(char &first, char last, std::array<char, 111> &arr){
  char last_cp  = arr[last];
  arr[last] = arr[first];
  arr[first] = last_cp;
}; 

short position_checker(unsigned char location, char next){
  if(maze_arr[location+next] == '#') return 0;
  else if(maze_arr[location+next] == 'F') return 2;
  else return 1;
};  
  
void load_maze(std::array<char, 111> &maze, std::ifstream &file){
  //file.open();
  char c;
  for(unsigned short i=0; i < 111; ++i)
    {
     
      c=file.get();
      std::cout << c << i << std::endl;
      maze[i] = c;
      
    }
  usleep(5000000);
  file.close();
};
