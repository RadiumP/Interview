#include <iostream>
#include <vector>




#define MAX 100


using namespace std;

//clockwise
void Rotation(int tile[2][2])
{
	int newTile[2][2];

	newTile[0][0] = tile[1][0];
	newTile[0][1] = tile[0][0];
	newTile[1][0] = tile[1][1];
	newTile[1][1] = tile[0][1];

	tile[0][0] = newTile[0][0];
	tile[0][1] = newTile[0][1];
	tile[1][0] = newTile[1][0];
	tile[1][1] = newTile[1][1];
	
}




void Link(char **tiles)
{
	int count = 0;
	int row = 2;
	int col = 2;
	
	int i = 0;

	//linked tiles into a board
	//use int instead of char to avoid garbage value
	
	/*vector<vector<int>> Board;

	Board.resize(MAX);
	for (int i = 0; i < MAX; ++i)
		Board[i].resize(MAX);
	*/
	
	//init target board
	int Board[MAX][MAX];
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			Board[i][j] = -1;

	int rotation = 0;
	bool found = false;

	//get block
	while ((*(tiles + i) != NULL))
	{
		//current tile
		int cur[2][2];
		if (count == 0)
		{
			Board[0][0] = **(tiles + i) - '0';
			Board[0][1] = *(*(tiles + i) + 1) - '0';
			Board[1][0] = **(tiles + i + 1) - '0';
			Board[1][1] = *(*(tiles + i + 1) + 1) - '0';
		}

		else
		{
			
			cur[0][0] = **(tiles + i) - '0';
			cur[0][1] = *(*(tiles + i) + 1) - '0';
			cur[1][0] = **(tiles + i + 1) - '0';
			cur[1][1] = *(*(tiles + i + 1) + 1) - '0';
			
			//Find placement in Board
			
			while (rotation < 4 && !found)//0, 90, 180, 270
			{
				//if find break
				
				//check horizon
				for (int i = 0; i < row; i++)
				{
					for (int j = 0; j < col - 1; j++)
					{
						//cur down 
						if (Board[i][j] == cur[1][0] && Board[i][j+1] == cur[1][1])
						{
							//found in 1st row
							if (i == 0)// ||)
							{
								//shift down
								row += 2;								
								for (int m = 0; m < col; m++)
								{
									for (int n = row - 3; n >= 0; n--)
									{
										Board[(n + 2)][ m] = Board[n][m];
										//replace with -1									
										Board[n][m] = -1;
										
									}
								}							
								//1st row so cur wont have left and right or up now
								Board[(i + 1)][j] = cur[1][0];
								Board[(i + 1)][j + 1] = cur[1][1];
								Board[i][j] = cur[0][0];
								Board[i][j + 1] = cur[0][1];
								
								cout << "Up" << endl;								
							
								found = true;
								break;
								
													
							
							}
							//found in middle rows
							if (i != 0 && Board[(i - 1)][j] < 0 && Board[(i - 1)][j + 1] < 0)
							{
							
								//middle row need to check up
								if ((i - 3 > 0 && ((Board[i - 3][j] > 0 && Board[i - 3][j] != cur[0][0]) || (Board[i - 3][j + 1] > 0 && Board[i - 3][j + 1] != cur[0][1]))) || //check up
									(j - 1 > 0 && ((Board[i - 1][j - 1] > 0 && Board[i - 1][j - 1] != cur[0][0]) || (Board[i - 2][j - 1] > 0 && Board[i - 2][j - 1] != cur[1][0]))) || //check left
									(j + 2 < col && ((Board[i - 1][j + 2] > 0 && Board[i - 1][j + 2] != cur[0][1]) || (Board[i - 2][j + 2] > 0 && Board[i - 2][j + 2] != cur[1][1])))) //checek right
									
								{
									found = false;
								}
								else found = true;


									if (found)
									{
										Board[(i - 1)][j] = cur[1][0];
										Board[(i - 1)][j + 1] = cur[1][1];
										Board[i - 2][j] = cur[0][0];
										Board[i - 2][j + 1] = cur[0][1];

										/*cout << Board[0][0] << endl;
										cout << Board[1][0] << endl;
										cout << Board[2][0] << endl;
										cout << Board[3][0] << endl;*/

										cout << "Up" << endl;

										break;
									}
							}
						}
						
						//cur up
						if (Board[i][j] == cur[0][0] && Board[i][j + 1] == cur[0][1])
						{
							//last row 
							if (i + 1 == row) //|| )
							{
								//shift up
								row += 2;
								//Board = (int *)realloc(Board, sizeof(int) * row * col);
								Board[(i + 1)][j] = cur[0][0];
								Board[(i + 1)][j + 1] = cur[0][1];
								Board[(i + 2)][j] = cur[1][0];
								Board[(i + 2)][j + 1] = cur[1][1];

								/*cout << Board[0][0] << endl;
								cout << Board[1][0] << endl;
								cout << Board[2][0] << endl;
								cout << Board[3][0] << endl;*/
								cout << "Down" << endl;
								found = true;
								break;
							}


							if (i + 1 < row  && Board[(i + 1)][j] < 0 && Board[(i + 1) ][j + 1] < 0)
							{

								//middle row need to check 
								if ((i + 3 < row && ((Board[i + 3][j] > 0 && Board[i + 3][j] != cur[1][0]) || (Board[i + 3][j + 1] > 0 && Board[i + 3][j + 1] != cur[1][1]))) || //check down
									(j - 1 > 0 && ((Board[i + 1][j - 1] > 0 && Board[i + 1][j - 1] != cur[0][0]) || (Board[i + 2][j - 1] > 0 && Board[i + 2][j - 1] != cur[1][0]))) || //check left
									(j + 2 < col && ((Board[i + 1][j + 2] > 0 && Board[i + 1][j + 2] != cur[0][1]) || (Board[i + 2][j + 2] > 0 && Board[i + 2][j + 2] != cur[1][1])))) //checek right

								{
									found = false;
								}
								else found = true;

								if(found)
								{ 
									Board[(i + 1)][j] = cur[0][0];
									Board[(i + 1)][j + 1] = cur[0][1];
									Board[(i + 2)][j] = cur[1][0];
									Board[(i + 2)][j + 1] = cur[1][1];

									/*cout << Board[0][0] << endl;
									cout << Board[1][0] << endl;
									cout << Board[2][0] << endl;
									cout << Board[3][0] << endl;*/
									cout << "Down" << endl;
								}
							
								
								break;
							}
						}
					}
				}
				if (found)break;
			  
				//check vertical
				for (int i = 0; i < row - 1; i++)
				{
					for (int j = 0; j < col; j++)
					{
						//cur right
						if (Board[i][j] == cur[0][1] && Board[(i + 1)][j] == cur[1][1])
						{
							//1st col
							if (j == 0)  // || ()
							{
								//shift right
								col += 2;
								//Board = (int *)realloc(Board, sizeof(int) * row * col);
								
								
								for (int m = 0; m < row; m++)
								{
									for (int n = col - 3; n >= 0; n--)
									{
										Board[m][n + 2] = Board[m][n];									
										Board[m][n] = -1;
										
									}
								}
								

								Board[i][j+1] = cur[0][1];
								Board[(i + 1)][j + 1] = cur[1][1];
								Board[i][j] = cur[0][0];
								Board[(i + 1)][j] = cur[1][0];

								cout << "Left" << endl;
								
								
								found = true;
								break;

							}
							
							//middle col
							if(j != 0 && Board[i][j - 1] < 0 && Board[(i + 1)][j - 1] < 0)
							{
							/*	for (int m = 0; m < row; m++)
								{
									for (int n = col - 3; n >= 0; n--)
									{
										Board[m][n + 2] = Board[m][n];
									}
								}*/
								//middle row need to check 
								if ((i + 2 < row && ((Board[i + 2][j - 1] > 0 && Board[i + 2][j - 1] != cur[1][0]) || (Board[i + 2][j - 2] > 0 && Board[i + 2][j - 2] != cur[1][1]))) || //check down
									(j - 3 > 0 && ((Board[i][j - 3] > 0 && Board[i][j - 3] != cur[0][0]) || (Board[i + 1][j - 3] > 0 && Board[i + 1][j - 3] != cur[1][0]))) || //check left
									(i - 1 > 0 && ((Board[i - 1][j - 1] > 0 && Board[i - 1][j - 1] != cur[0][0]) || (Board[i - 1][j - 2] > 0 && Board[i - 1][j - 2] != cur[0][1])))) //check up

								{
									found = false;
								}
								else found = true;

								if (found)
								{

									Board[i][j - 2] = cur[0][0];
									Board[(i + 1)][j - 2] = cur[1][0];
									Board[i][j - 1] = cur[0][1];
									Board[(i + 1)][j - 1] = cur[1][1];

									cout << "Left" << endl;

									break;
								}
							}
						}

						//cur left
						if (Board[i][j] == cur[0][0] && Board[(i + 1)][j] == cur[1][0])
						{
							if (j == col - 1) //  || )0
							{
								//shift left
								col += 2;
								//Board = (int *)realloc(Board, sizeof(int) * row * col);	
								Board[i][j + 2] = cur[0][1];
								Board[(i + 1)][j + 2] = cur[1][1];
								Board[i][j + 1] = cur[0][0];
								Board[(i + 1)][j + 1] = cur[1][0];

								cout << "Right" << endl;
								found = true;
								break;

							}

							if (j != col - 1 && Board[i][j + 1] < 0 && Board[(i + 1)][j + 1] < 0)
							{

								//middle row need to check 
								if ((i + 2 < row && ((Board[i + 2][j + 1] > 0 && Board[i + 2][j + 1] != cur[1][0]) || (Board[i + 2][j + 2] > 0 && Board[i + 2][j + 2] != cur[1][1]))) || //check down
									(j + 3 > 0 && ((Board[i][j + 3] > 0 && Board[i][j + 3] != cur[0][0]) || (Board[i + 1][j + 3] > 0 && Board[i + 1][j + 3] != cur[1][0]))) || //check right
									(i - 1 > 0 && ((Board[i - 1][j + 1] > 0 && Board[i - 1][j + 1] != cur[0][0]) || (Board[i - 1][j + 2] > 0 && Board[i - 1][j + 2] != cur[0][1])))) //check up

								{
									found = false;
								}
								else found = true;

								if(found)
								{
									Board[i][j + 2] = cur[0][1];
									Board[(i + 1)][j + 2] = cur[1][1];
									Board[i][j + 1] = cur[0][0];
									Board[(i + 1)][j + 1] = cur[1][0];

									cout << "Right" << endl;
									
									break;
								}
								
							}
						}
					}
				}
					

				if (found)break;
				
				//check  insert
				//diagonal
				for (int i = 1; i < row - 1; i++)
					for (int j = 1; j < col - 1; j++)
					{
						if (Board[i][j] < 0 && Board[i][j + 1] < 0 && Board[i + 1][j + 1] < 0 && Board[i + 1][j] < 0)
						{
							//diagonal means only 2 connections exist, otherwise it will be checked in former code
							
							//UL DR
							if ((cur[0][0] == Board[i - 1][j] || cur[0][0] == Board[i][j - 1]) && (cur[1][1] == Board[i + 1][j + 2] || cur[1][1] == Board[i + 2][j + 1]))
							{
								found = true;
								Board[i][j] = cur[0][0];
								Board[i][j + 1] = cur[0][1];
								Board[i + 1][j + 1] = cur[1][1];
								Board[i + 1][j] = cur[1][0];

								break;

							}
							//UR DL
							if ((cur[1][0] == Board[i + 1][j - 1] || cur[1][0] == Board[i + 2][j]) && (cur[0][1] == Board[i - 1][j + 1] || cur[0][1] == Board[i][j + 2]))
							{
								found = true;
								Board[i][j] = cur[0][0];
								Board[i][j + 1] = cur[0][1];
								Board[i + 1][j + 1] = cur[1][1];
								Board[i + 1][j] = cur[1][0];

								break;

							}
													

						}
					}

				if (found)break;
				
				



				Rotation(cur);
				rotation++;
				
				
			} 
			
		}

		count++;
		
		//print
		cout << "Link " << count;
		if (rotation < 4 && rotation > 0)
		{
			cout << "//note this tile had to be rotated " << rotation * 90 << " degrees clockwise" << endl;
		}
		else
		{
			cout << endl;
		}

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
			{
				if (Board[i ][ j] >= 0)
					cout << Board[i][j];
				if (Board[i ][ j] < 0)
				{
					cout << ' ';
				}
				if (j == col - 1)
				{

					cout << ' ' << endl;
				}

				
			}
		rotation = 0;
		found = false;

		if (*(tiles + i + 2) == NULL)break;

		i += 3;
		
	} 
	
	//cout << (*(tiles + 17) == NULL) << *(tiles + i + 1) << endl;
	
	
}


int main()
{
	char *tiles1[] = {
		
		
		"11",     // 1
		"23",
		"",
		"44",     // 2
		"11",
		"",
		
		"16",     // 3
		"36",
		"",
		"51",     // 4. 
		"71",
		"",
		"46",     // 5
		"26",
		"",
		"14",     // 6
		"68",
		0 };
	Link(tiles1);


	char *tiles2[] = {
		"12",	// 1
		"34",
		"",
		"36",	// 2
		"15",
		"",
		"56",	// 3
		"78",
		"",
		"78",	// 4
		"90",
		"",
		"46",	// 5
		"26",
		"",
		"88",	// 6
		"01",
		"",
		"93",	// 7
		"54",
		0 };

	Link(tiles2);

	char *tiles3[] = {
		"11",     // 1
		"12",
		"",
		"12",     // 2
		"93",
		"",
		"93",     // 3
		"99",
		"",
		"39",     // 4
		"98",
		"",
		"95",     // 5
		"86",
		"",
		"57",     // 6
		"66",
		"",
		"77",     // 7
		"57",
		"",
		"13",     // 8
		"24",
		"",
		"45",     // 9
		"47",
		"",
		"24",     // 10
		"39",
		0 };
	
	Link(tiles3);

	char *tiles4[] = {
		"21",     // 1
		"11",
		"",
		"39",     // 2
		"21",
		"",
		"99",     // 3
		"39",
		"",
		"89",     // 4
		"93",
		"",
		"68",     // 5
		"59",
		"",
		"02",     // 6
		"91",
		"",
		"70",     // 7
		"49",
		"",
		
		"05",     // 10
		"87",
		0 };

	Link(tiles4);


	char *tiles5[] = {
		"12",     // 1
		"11",
		"",
		"93",     // 2
		"12",
		"",
		"99",     // 3
		"93",
		"",
		"98",     // 4
		"39",
		"",
		"86",     // 5
		"95",
		"",
		"66",     // 6
		"57",
		"",
		"57",     // 7
		"77",
		"",
		"24",     // 8
		"13",
		"",
		"47",     // 9
		"45",
		"",
		"39",     // 10
		"24",
		0 };

	Link(tiles5);



	cin.get();
	return 0;
}