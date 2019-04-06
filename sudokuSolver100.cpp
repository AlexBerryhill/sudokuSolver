/*************************************************************************
* Program:                                                                 
*    Project Final, Sudoku Solver                                          
*    Brother Ridges, CS124                                                 
* Author:                                                                  
*    Alexander Berryhill                                                   
* Summary:                                                                 
*    Sudoku will allow you to play a game of sudoku. Or the program        
*    will play for you.                                                    
*                                                                          
*                                                                          
*                                                                          
*    Estimated:  5.5 hrs                                                   
*    Actual:     6.5 hrs                                                   
*      The most difficult part was getting the input in interact to work   
*************************************************************************/

#include <fstream>
#include <iostream>
using namespace std;

/*************************************************************************
 * getIFile will get the input fileName                                    
 ************************************************************************/
void getIFile(char fileName[])
{
   cout << "Where is your board located? ";
   cin >> fileName;
   cin.ignore(256, '\n');
   return;
}

/*************************************************************************
 * readFile will read the input file and put it in a board.                
 ************************************************************************/
void readFile(char fileName[], char board[9][9], int plEdits[2][256])
{
   ifstream fin;
   fin.open(fileName);
   if (fin.fail())
      cout << "Could not open " << fileName << endl;
   for (int i = 0; i < 9; i++)
   {
      for (int j = 0; j < 9; j++)
      {
         fin >> board[i][j];
      }
   }
   for (int i = 0; i < 81 && fin >> plEdits[0][i]; i++)
      fin >> plEdits[1][i];
   for (int i = 0; plEdits[0][i]; i++)
   {
      cout << "(" << plEdits[1][i] << ", " << plEdits[0][i] << ")\n";
   }
   fin.close();
   return;
}

/*************************************************************************
 * getOFile will get an output fileName                                    
 ************************************************************************/
void getOFile(char fileName[])
{
    cin >> fileName;
   cin.ignore(256, '\n');
   return;
}

/*************************************************************************
 * writeFile will save your game onto a file                               
 ************************************************************************/
void writeFile(char fileName[], char board[9][9], int plEdits[2][256])
{
   ofstream fout;
   fout.open(fileName);
   if (fout.fail())
      cout << "Could not open " << fileName << endl;
   for (int i = 0; i < 9; i++)
   {
      for (int j = 0; j < 9; j++)
      {
         fout << board[i][j];
      }
      fout << endl;
   }
   for (int i = 0; i < 81 && fout << plEdits[0][i]; i++)
      fout << ' ' << plEdits[1][i] << ' ';
   fout.close();
   return;
}

/*************************************************************************
 * save will save the game (used to be bigger)                             
 ************************************************************************/
 void save(char board[9][9], int plEdits[2][256], char fileName[])
{
   getOFile(fileName);
   writeFile(fileName, board, plEdits);
   cout << "Board written successfully\n";
   return;
}

/*************************************************************************
 * empty will empty 1D arrays                                              
 ************************************************************************/
void empty(char array[])
{
   for (int i = 0; array[i]; i++)
   {
      array[i] = '\0';
   }
   return;
}

/*************************************************************************
 * isCoord will return if you can write on a coordinate                    
 ************************************************************************/
bool isCoord(char board[9][9], char x, char y)
{
   if ((y - 48) < 1 || (y - 48) > 9)
   {
      cout << "ERROR: Square \'" << x << y << "\' is invalid\n";
      return false;
   }
   else if (toupper(x) - 64 < 1 || toupper(x) - 64 > 9)
   {
             return false;
   }
   else if (board[y - 49][toupper(x) - 65] != '0')
   {
      cout << "ERROR: Square \'" << x << y << "\' is filled\n";
      return false;
   }
   return true;
}

/*************************************************************************
 * getCoord will get a pair of coordinates                                 
 ************************************************************************/
bool getCoord(char board[9][9], char &x, char &y)
{
   cout << "What are the coordinates of the square: ";
   cin >> x;
   if (x > '9')
      cin >> y;
   else
   {
      y = x;
      cin >> x;
   }
   return isCoord (board, x, y);
}

/*************************************************************************
 * computeValues will compute what is allowed and display if prompted.     
 ************************************************************************/
void computeValues(char board[9][9], char canVal[], char x, char y,
                   bool promp)
{
   char notVal[3][9];
   if (promp)
   {
      getCoord(board, x, y);
   }
   int ix = toupper(x) - 65;
   int iy = y - 49;                //to int form int x and int y           

   for (int i = 0; i < 9; i++)     //column as 0                           
   {
      notVal[0][i] = board[i][ix];
   }
   for (int i = 0; i < 9; i++)     //row as 1                              
   {
      notVal[1][i] = board[iy][i];
   }
   int blockX = 0;                 //block as 2                            
   for (int i = ((iy / 3) * 3); i < ((iy / 3) * 3) + 3; i++)
   {
      for (int j = ((ix / 3) * 3); j < ((ix / 3) * 3) + 3; j++)
      {
         notVal[2][blockX++ ] = board[i][j];
      }
   }

   int canX = 0;
   empty(canVal);
   for (int n = 1; n <= 9; n++)
   {
      bool isN = true;
            for (int i = 0; i < 3; i++)
      {
         for (int j = 0; j < 9; j++)
         {
            if (notVal[i][j] == cn)
            {
               isN = false;
            }
            for (int k = 0; canVal[k]; k++)
            {
               if (notVal[i][j] == canVal[k])
                  isN = false;
            }
         }
      }
      if (isN)
         canVal[ canX++ ] = cn;
   }

   if (promp)
   {
      cout << "The possible values for \'" << x << y << "\' are: ";
      for (int i = 0; canVal[i]; i++)
      {
         cout << canVal[i];
         if (canVal[i + 1])
            cout << ", ";
      }
      cout << endl;
   }
   return;
}

/*************************************************************************
 * isValidNew will check if the new value is valid                         
 ************************************************************************/
bool isValidNew(char board[9][9], char n, char x, char y)
{
   char canVal[9];
   computeValues(board, canVal, x, y, false);

   if (n < '1' || n > '9')
   {
      cout << "ERROR: Value \'" << n << "\' in square \'" << x << y <<
         "\' is invalid\n";
      return false;
   }
   for (int i = 0; canVal[i]; i++)
   {
      if (canVal[i] == n)
      {
         return true;
      }
   }
   cout << "ERROR: Value \'" << n << "\' in square \'" << x << y <<
      "\' is invalid\n";
   return false;
}

/*************************************************************************
 * getNew will get a new value                                             
 ************************************************************************/
bool getNew(char board[9][9], char &n, char x, char y)
{
      cout << "What is the value at \'" << x << y << "\': ";
   cin >> n;
   return isValidNew (board, n, x, y);
}

/*************************************************************************
 * edit will edit one spot                                                 
 ************************************************************************/
void edit(char board[9][9], int plEdits[2][256], int ix, int iy, char n,
          bool inter)
{
   char x = 'A' + ix;
   char y = '1' + iy;
   int i = 0;

   if (inter)
   {
      if (!getCoord(board, x, y))
         return;
      if (!getNew(board, n, x, y))
         return;
   }
   else
   {
      if (!isCoord(board, x, y))
         return;
      if (!isValidNew(board, n, x, y))
         return;
   }

   board[y - '1'][toupper(x) - 'A'] = n;
   
     for (i = 0; plEdits[0][i]; i++); //to next open spot                    
      if (i < 256)
      {
         plEdits[0][i] = (y - '1');
         plEdits[1][i] = (toupper(x) - 'A');
      }

   return;
}


/*************************************************************************
 * display will display the board                                          
 ************************************************************************/
void display(char board[9][9], int plEdits[2][256])
{
   cout << "   A B C D E F G H I\n";
   for (int i = 0; i < 9; i++)
   {
      if ((i) % 3 == 0 && i != 0)
         cout << "   -----+-----+-----\n";
      cout << i + 1 << "  ";
      for (int j = 0; j < 9; j++)
      {
         char d;
         bool green = true;

         if (board[i][j] == '0')
            d = ' ';
         else
            d = board[i][j];
            
                     for (int k = 0; plEdits[0][k]; k++)
         {
            if (plEdits[0][k] == i && plEdits[1][k] == j)
               green = false;
         }

         if (green)
            cout << "\E[22;32m";
         if (((j + 1) % 3) == 0 && j != 8)
            cout << d << "\E[0m|";
         else if (j == 8)
            cout << d << "\E[0m";
         else
            cout << d << "\E[0m ";
      }
      cout << endl;
   }
   return;
}

/*************************************************************************
 * toInt converts my board into integers because I am stupid.              
 ************************************************************************/
void toInt(char board[9][9], int iboard[9][9])
{
   for (int i = 0; i < 9; i++)
   {
      for (int j = 0; j < 9; j++)
      {
         iboard[i][j] = board[i][j] - '0';
      }
   }
      return;
}

/*************************************************************************
 * toChar converts my board into chars because I am stupid.                
 ************************************************************************/
void toChar(int iboard[9][9], char board[9][9])
{
   for (int i = 0; i < 9; i++)
   {
      for (int j = 0; j < 9; j++)
      {
         board[i][j] = iboard[i][j] + '0';
      }
   }
   return;
}

/*************************************************************************
 * findEmpty searches the grid to find a spot that is still 0.             
 ************************************************************************/
bool findEmpty(int board[9][9], int &y, int &x)
{
   for (y = 0; y < 9; y++)
      for (x = 0; x < 9; x++)
         if (board[y][x] == 0)
            return true;
   return false;
}

/*************************************************************************
 * inRow returns whether any number in the y matches the num.    
  ************************************************************************/
bool inRow(int board[9][9], int y, int num)
{
   for (int x = 0; x < 9; x++)
      if (board[y][x] == num)
         return true;
   return false;
}

/*************************************************************************
 * inCol returns whether any number in the x matches the num.              
 ************************************************************************/
bool inCol(int board[9][9], int x, int num)
{
   for (int y = 0; y < 9; y++)
      if (board[y][x] == num)
         return true;
   return false;
}

/*************************************************************************
 * inBlock returns whether any number within the block matches the num.    
 ************************************************************************/
bool inBlock(int board[9][9], int blockY, int blockX, int num)
{
   for (int y = 0; y < 3; y++)
      for (int x = 0; x < 3; x++)
         if (board[y + blockY][x + blockX] == num)
            return true;
   return false;
}

/*************************************************************************
 * isSafe returns whether it will be safe to assign num to the given       
 * x, y location.                                                          
 ************************************************************************/
bool isSafe(int board[9][9], int y, int x, int num)
{
   return !inRow (board, y, num) && !inCol (board, x, num) &&
      !inBlock (board, y - y % 3 , x - x % 3, num);
}

/*************************************************************************
 * solve solves the given board. First it checks if it is empty, then      
 ************************************************************************/
bool solve(int board[9][9], int plEdits[2][256])
{
   int y;
   int x;
   char cboard[9][9];

   if (!findEmpty(board, y, x))//Check if it is empty                      
      return true;
   for (int num = 1; num <= 9; num++)//try every number                    
   {
      if (isSafe(board, y, x, num))//if it works                           
      {
         board[y][x] = num;//couldn't get edit to work for some reason     
         if (solve(board, plEdits)) //do it again                          
            return true;    //until you can't                              
         board[y][x] = 0;
      }
   }
   return false;
}

/*************************************************************************
 * solve1 is the safest but least adaptive method "naked single boxes"     
 ************************************************************************/
bool solve1 (char board[9][9], int plEdits[2][256])
{
   int numVal;
   bool lv1 = false;
   char canVal[9];

   for (int y = 0; y < 9; y++)
   {
      for (int x = 0; x < 9; x++)
      {
         if (board[y][x] == '0')
         {
            computeValues (board, canVal, x, y, false);
            for (numVal = 0; canVal[numVal]; numVal++);
            if (numVal == 1)
            {
               edit (board, plEdits, x, y, canVal[0], false);
               lv1 = true;
            }
         }
      }
   }
   return lv1;
}

/*************************************************************
 * options will display the options                                        
 ************************************************************************/
void options()
{

   cout << "Options:\n   ?  Show these instructions\n   D  Display the ";
   cout << "board\n   E  Edit one square\n   S  Show the possible values";
   cout << " for a square\n   Q  Save and Quit\n   ";
   cout << "A  Solve the board (breaks green number for now)\n\n";
   return;
}

/*************************************************************************
 * interact will loop around taking input and reacting to it, when it      
 * ends the game ends.                                                     
 ************************************************************************/
void interact(char board[9][9], int plEdits[2][256], char fileName[])
{
   char choice;
   bool play = true;

   options();
   display(board, plEdits);

   while (play)
   {
      cout << "\n> ";
      cin >> choice;
      cin.ignore(256, '\n');
      switch (choice)
      {
        case '?'://bring up options                                       
            options();
            break;
         case 'D'://display board as green, player edits as white          
            display(board, plEdits);
            break;
         case 'E'://run edit                                               
            edit(board, plEdits, 0, 0, 0, true);
            break;
         case 'S'://run computeValues prompt display values as true        
            char canVal[9];                          //this and            
            computeValues(board, canVal, 0, 0, true);//0, 0, true so I can
            break;                                //use this in isValidNew
         case 'Q'://Save and quit                                          
            save(board, plEdits, fileName);
            play = false;
            break;
         case 'L':
            while (solve1(board, plEdits));
            display(board, plEdits);
            break;
         case 'A'://Solve the board                                        
            int iboard[9][9];
            cout << "This takes a while, be patient(1 - 40 seconds)\n";
            toInt (board, iboard);

            if (solve(iboard, plEdits))
            {
               toChar (iboard, board);
               display(board, plEdits);
            }
            else
            {
                               cout << "ERROR: Invalid board\n";
               toChar (iboard, board);
               display(board, plEdits);
            }
            break;
         default:
            cout << "ERROR: Invalid command\n";
      }
   }
   return;
}

/*************************************************************************
 * main will initialize fileName and board, then fill them. Then push the 
 * rest of the work onto interact.                                         
 ************************************************************************/
int main()
{
   char fileName[256];
   char board[9][9];
   int plEdits[2][256];

   getIFile(fileName);//get In File                                        
   readFile(fileName, board, plEdits);//read it and put int board          
   interact(board, plEdits, fileName);//everything else                    

   return 0;
}

            }