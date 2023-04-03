#include "../Public/BPawn.h"
#include <unistd.h>
#include <termios.h>


BPawn::BPawn() : bDead(false)
{
  //Code Here
  ObjectSpriteModel.SetSprite("");
  this->BPropertyName = "BPawn";
  this->CoordX = 0;
  this->CoordY = 0;
}

BPawn::~BPawn()
{
}


void BPawn::Move()
{
  
}

int BPawn::getch()
{
  int character;
  
  termios Old;
  termios New;

  //Read Current Termial Configuration Settings
  tcgetattr(STDIN_FILENO, &Old);
  
  New = Old;
    
  // Turn Off CANONICAL and ECHO
  New.c_lflag &= ~(ICANON | ECHO);
  
  // Set Minimum Input Character Count to One
  New.c_cc[VMIN] = 1;

  // Set Minimum Read Delay Time to 0
  New.c_cc[VTIME] = 0;

  // Throw Configuration Settings to Terminal
  tcsetattr(STDIN_FILENO, TCSANOW, &New);  

  // Read Inputs From Keyboard
  character = getchar();  

  // Restore to Default Settings
  tcsetattr(STDIN_FILENO, TCSANOW, &Old);  
  
  return character;
}