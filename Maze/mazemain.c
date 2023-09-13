#include <stdio.h>
#include "maze.h"
#include "paths.h"

int main(int argc, char** argv)
{
  struct MazeCell* start;

  start = mazeFor(YOUR_NAME);
  /* Set a breakpoint here to explore your maze! */
  if(isPathToFreedom(start, PATH_OUT_OF_MAZE))
  {
    printf("Congratulations! You've found a way out of your labyrinth.\n");
  }
  else
  {
    printf("Sorry, but you're still stuck in your labyrinth.\n");
  }
  freeMaze(start);

  start = twistyMazeFor(YOUR_NAME);
  /* Set a breakpoint here to explore your twisty maze! */
  if(isPathToFreedom(start, PATH_OUT_OF_TWISTY_MAZE))
  {
    printf("Congratulations! You've found a way out of your twisty labyrinth.\n");
  }
  else
  {
    printf("Sorry, but you're still stuck in your twisty labyrinth.\n");
  }
  freeMaze(start);

  return 0;
}

north->
south->
north->
east->
west->
north->
north->
south->
south->
north->
west->
east->
south->
south->
east->
east->
north->
east