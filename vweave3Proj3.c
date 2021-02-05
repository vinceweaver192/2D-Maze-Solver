#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TRUE 1 
#define FALSE 0

bool debug = false;

typedef struct mazeStruct
{
 //char arr[32][32];  /* allows for a maze of size 30x30 plus outer walls */
 // make dynamic
 char** arr; // compares *'s and .'s and s and e

 int xsize, ysize;
 int xstart, ystart;
 int xend, yend;

 int** Visited; // compares 1 and 0s or true and falses

} maze;

typedef struct linkedList
{
 int xPos;
 int yPos;

 struct linkedList*  next;
 //int size;

}stackList;

typedef struct linkedList linked;
typedef linked* linkedPtr; 


void push (stackList** hd, int xposition, int yposition)
{

  stackList* ptr = (stackList*) malloc (sizeof(stackList));

  ptr->xPos = xposition;
  ptr->yPos = yposition;
  ptr->next = *hd;
  *hd = ptr;
  
}

int isEmpty (stackList* hd)
{
 if (hd == NULL)
   return TRUE;
 else
   return FALSE;
}

linkedPtr top (linkedPtr hd)
{
  // how to reference the top of the stack coordinates
  // top(hd) -> xpos
  // top(hd) -> ypos
 return (hd);
}

void pop (stackList** hd)
{
 stackList * tmp = *hd;

 if (*hd != NULL){
   *hd = (*hd)->next;
   free (tmp);
 }
 
}

int main (int argc, char **argv)
{
  maze m1;

  int xpos, ypos;
  int i,j;

  FILE *src;

  /* verify the proper number of command line arguments were given */
  if(argc != 2) {
     printf("Usage: %s <input file name>\n", argv[0]);
     exit(-1);
  }
   
  /* Try to open the input file. */
  if ( ( src = fopen( argv[1], "r" )) == NULL )
  {
    printf ( "Can't open input file: %s", argv[1] );
    exit(-1);
  }

  /* read in the size, starting and ending positions in the maze */
  fscanf (src, "%d %d", &m1.xsize, &m1.ysize);
  fscanf (src, "%d %d", &m1.xstart, &m1.ystart);
  fscanf (src, "%d %d", &m1.xend, &m1.yend);
  /* print them out to verify the input */
  printf ("size: %d, %d\n", m1.xsize, m1.ysize);
  printf ("start: %d, %d\n", m1.xstart, m1.ystart);
  printf ("end: %d, %d\n", m1.xend, m1.yend);


  //char** arr1; // what the user sees
  //int** arr2d; // what gets compared 

  /* allocate space for x num of intergers */
  m1.arr = (char**) malloc (sizeof(char*) * m1.xsize+2 ); 
  m1.Visited = (int**) malloc (sizeof(int*) * m1.xsize+2);

 /* initialize all array locations to contain the value zero */
  for ( i = 0 ; i < m1.xsize+2 ; i++ ){
      m1.arr[i] = (char*) malloc (sizeof(char) * m1.ysize+2);
  }

  for (i = 0; i < m1.xsize+2 ; i++){
      m1.Visited[i] = (int*) malloc (sizeof(int) * m1.ysize+2);
  }

  // for (i = 0; i < m1.xsize+2; i++){
  //     for (j = 0; j < m1.ysize+2; j++){
  //       arr2d[i][j] = (int**) malloc (sizeof(int*) * m1.ysize+2);;
  //     }
  // }

  /* initialize the maze to empty */
  for (i = 0; i < m1.xsize+2; i++){
     for (j = 0; j < m1.ysize+2; j++){
       m1.arr[i][j] = '.';
       // initialize all positions in maze as unvisited
       m1.Visited[i][j] = FALSE;
     }
  }

  /* mark the borders of the maze with *'s */
  for (i=0; i < m1.xsize+2; i++)
    {
     m1.arr[i][0] = '*';
     m1.arr[i][m1.ysize+1] = '*';
    }
  for (i=0; i < m1.ysize+2; i++)
    {
     m1.arr[0][i] = '*';
     m1.arr[m1.xsize+1][i] = '*';
    }

  /* mark the starting and ending positions in the maze */
  m1.arr[m1.xstart][m1.ystart] = 's';
  m1.arr[m1.xend][m1.yend] = 'e';

  /* allocate memory for positions in the maze */
    for (i=0; i < m1.xsize; i++)
    {
     m1.arr[0][i] = '*';
     m1.arr[m1.xsize+1][i] = '*';
    }
		  
  /* mark the blocked positions in the maze with *'s */
  while (fscanf (src, "%d %d", &xpos, &ypos) != EOF)
    {
     m1.arr[xpos][ypos] = '*';
     m1.Visited[xpos][ypos] = 1;
    }

  /* print out the initial maze */
  for (i = 0; i < m1.xsize+2; i++)
    {
     for (j = 0; j < m1.ysize+2; j++)
       printf ("%c", m1.arr[i][j]);
     printf("\n");
    }

    fclose(src);

  // initialize the starts to be updated
  xpos = m1.xstart;
  ypos = m1.ystart;

  stackList* pHead = NULL;
  stackList* printPtr = NULL;

  push(&pHead, m1.xstart, m1.ystart);
  printf(" %d %d \n", top(pHead)->xPos, top(pHead)->yPos);

  // find route for maze and push and pop stack accordingly
  //while (m1.arr[linkedList->xpos][linkedList->ypos] != m1.arr[m1.xend][m1.yend])
  while (m1.Visited[xpos][ypos] != m1.arr[m1.xend][m1.yend])
  {
    // end of x [] and end of y []

    // if (pHead->xPos == m1.xend && pHead->yPos == m1.yend){
    //   break;
    // }
    if (m1.Visited[m1.xend][m1.yend] == 1){
      break;
    }

    else if ((m1.arr[xpos][ypos+1] != '*') &&
    (m1.Visited[xpos][ypos+1] == FALSE)){ // check right
      
      ypos++;
      push(&pHead, xpos, ypos);
      printf(" %d %d \n", top(pHead)->xPos, top(pHead)->yPos);
      m1.Visited[xpos][ypos] = TRUE;
      
    }
    else if ((m1.arr[xpos+1][ypos] != '*') &&
    (m1.Visited[xpos+1][ypos] == FALSE)){ // check down
      
      xpos++; 
      push(&pHead, xpos, ypos);
      printf(" %d %d \n", top(pHead)->xPos, top(pHead)->yPos);
      m1.Visited[xpos][ypos] = TRUE; 
          
    }
    else if ((m1.arr[xpos][ypos-1] != '*') &&
    (m1.Visited[xpos][ypos-1] == FALSE)){ // check left

      ypos--;
      push(&pHead, xpos, ypos);
      printf(" %d %d \n", top(pHead)->xPos, top(pHead)->yPos);
      m1.Visited[xpos][ypos] = TRUE; 
           
    }
    else if ((m1.arr[xpos-1][ypos] != '*') &&
    (m1.Visited[xpos-1][ypos] = FALSE)){ // check up

      xpos--;   
      push(&pHead, xpos, ypos);
      printf(" %d %d \n", top(pHead)->xPos, top(pHead)->yPos);
      m1.Visited[xpos][ypos] = TRUE; 
        
    }
    else {
      // pop
      pop(&pHead);

      if (isEmpty(pHead) == FALSE){

        xpos = pHead->xPos;
        ypos = pHead->yPos;
      }
      else {
        break;
      }
    }
    //printf("end \n");
    
  }// end of while

  if (xpos == m1.xend && ypos == m1.yend){
    printf(" maze over, solution found \n");
  }
  if ((isEmpty(pHead) == 1) && (xpos != m1.xend) && (ypos != m1.yend)){
    printf(" no solution \n");
  }

  // empty the stack
  while (TRUE){
    if (isEmpty(pHead) == TRUE){
      break;
    }
    else{
      push(&printPtr, top(pHead)->xPos, top(pHead)->yPos);
      pop(&pHead);
     //printf(" deleting \n");
    }
  }

  // print the stack in order
  while (TRUE){
    if (isEmpty(pHead) == TRUE){
      break;
    }
    else{
      printf(" %d %d \n", top(printPtr)->xPos, top(printPtr)->yPos);
      pop(&printPtr);
    }
  }


  for (i = 0; i < m1.xsize+2; i++){
    free(m1.arr[i]);
    free(m1.Visited[i]);
  }
  free(m1.arr);
  free(m1.Visited);

  printf("end \n");
}// end of main
