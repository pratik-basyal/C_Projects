#ifndef MAZE_H
#define MAZE_H

/* Type representing a cell in a maze. */
struct MazeCell
{
  char* item; /* "Potion", "Spellbook", "Wand", or null */

  struct MazeCell* north;
  struct MazeCell* south;
  struct MazeCell* east;
  struct MazeCell* west;
};


/***********************************************************************/
/* Given a location in a maze, returns whether the given sequence of   */
/* steps will let you escape the maze. The steps should be given as    */
/* a string made from N, S, E, and W for north/south/east/west without */
/* spaces or other punctuation symbols, such as "WESNNNS"              */
/*                                                                     */
/* To escape the maze, you need to find the Potion, the Spellbook, and */
/* the Wand. You can only take steps in the four cardinal directions,  */
/* and you can't move in directions that don't exist in the maze.      */
/*                                                                     */
/* It's assumed that the start location is not null.                   */
/*                                                                     */
/* start The start location in the maze.                               */
/* moves The sequence of moves.                                        */
/* Returns 1 if that sequence of moves picks up the needed items       */
/*         without making any illegal moves, 0 if not.                 */
/***********************************************************************/
int isPathToFreedom(struct MazeCell* start, char* moves);

/****************************************/
/* Generates a maze for a given string. */
/* Returns the starting cell.           */
/****************************************/
struct MazeCell* mazeFor(char* name);

/*************************************************/
/* Generates a "twisty" maze for a given string. */
/* Returns the starting cell.                    */
/*************************************************/
struct MazeCell* twistyMazeFor(char* name);

/* Free all cells reachable from this one.*/
void freeMaze(struct MazeCell* maze);


#endif