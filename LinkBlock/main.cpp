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
	int Board[MAX][MAX];
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			Board[i][j] = -1;
	
	int rotation = 0;
	bool found = false;
	int count = 0;
	int row = 2;
	int col = 2;

	int line = 0;


	//get block
	while ((*(tiles + line) != NULL))
	{
		int cur[2][2];
		if (count == 0)
		{
			Board[0][0] = **(tiles + line) - '0';
			Board[0][1] = *(*(tiles + line) + 1) - '0';
			Board[1][0] = **(tiles + line + 1) - '0';
			Board[1][1] = *(*(tiles + line + 1) + 1) - '0';
			
		}
		else
		{
			//diagonally shift to make space
			for (int m = row + 4 - 2; m >= 2; m--)
			{
				for (int n = col + 4 - 2; n >= 2; n--)
				{
					Board[m][n] = Board[m - 2][n - 2];
					//replace with -1									
					Board[m - 2][n - 2] = -1;
				}
			}

			/*for (int i = 0; i < row + 4; i++)
			for (int j = 0; j < col + 4; j++)
			{
			if (Board[i][j] >= 0)
			cout << Board[i][j];
			
			if (j == col + 4 - 1)
			{

				cout << ' ' << endl;
			}


			}*/
			

			//block to add
			cur[0][0] = **(tiles + line) - '0';
			cur[0][1] = *(*(tiles + line) + 1) - '0';
			cur[1][0] = **(tiles + line + 1) - '0';
			cur[1][1] = *(*(tiles + line + 1) + 1) - '0';

			while (rotation < 4)//0, 90, 180, 270
			{
				int curi = 0;
				int	curj = 0;
				int available = 0;

				for (int i = 0; i < row + 4; i++)
				{
					if (found)break;
					for (int j = 0; j < col + 4; j++)
					{
						//find 4 available quads 
						if (Board[i][j] < 0 && Board[i][j + 1] < 0 && Board[i + 1][j] < 0 && Board[i + 1][j + 1] < 0)
						{
							//if i > row or j > col need to shift back

							//1st row and 1st col
							if (i == 0 && j == 0)
							{
								if ((cur[0][1] == Board[i][j + 2]))available++;
								if ((cur[1][1] == Board[i + 2][j + 1] || cur[1][1] == Board[i + 1][j + 2]))available++;
								if ((cur[1][0] == Board[i + 2][j]))available++;

								//double check
								if (available >= 2)
								{
									//check 4 directions
									if (
										(Board[i][j + 2] < 0 || (Board[i][j + 2] >= 0 && Board[i][j + 2] == cur[0][1])) &&
										(Board[i + 1][j + 2] < 0 || (Board[i + 1][j + 2] >= 0 && Board[i + 1][j + 2] == cur[1][1])) &&
										(Board[i + 2][j + 1] < 0 || (Board[i + 2][j + 1] >= 0 && Board[i + 2][j + 1] == cur[1][1])) &&
										(Board[i + 2][j] < 0 || (Board[i + 2][j] >= 0 && Board[i + 2][j] == cur[1][0]))
										)
									{
										//found
										found = true;
										curi = i;
										curj = j;
										break;
									}
								}
								available = 0;
							}

							//1st row and last col
							if (i == 0 && j == col + 4 - 2)
							{
								if ((cur[0][0] == Board[i][j - 1]))available++;
								if ((cur[1][0] == Board[i + 1][j - 1] || cur[1][0] == Board[i + 2][j]))available++;
								if ((cur[1][1] == Board[i + 2][j + 1]))available++;


								//double check
								if (available >= 2)
								{
									//check 4 directions
									if (
										(Board[i][j - 1] < 0 || (Board[i][j - 1] >= 0 && Board[i][j - 1] == cur[0][0])) &&
										(Board[i + 2][j + 1] < 0 || (Board[i + 2][j + 1] >= 0 && Board[i + 2][j + 1] == cur[1][1])) &&
										(Board[i + 2][j] < 0 || (Board[i + 2][j] >= 0 && Board[i + 2][j] == cur[1][0])) &&
										(Board[i + 1][j - 1] < 0 || (Board[i + 1][j - 1] >= 0 && Board[i + 1][j - 1] == cur[1][0]))
										)
									{
										//found
										found = true;
										curi = i;
										curj = j;
										break;
									}
								}
								available = 0;
							}


							//last row and 1st col
							if (i == row + 4 - 2 && j == 0)
							{
								if ((cur[0][0] == Board[i - 1][j]))available++;
								if ((cur[0][1] == Board[i][j + 2] || cur[0][1] == Board[i - 1][j + 1]))available++;
								if ((cur[1][1] == Board[i + 1][j + 2]))available++;

								//double check
								if (available >= 2)
								{
									//check 4 directions
									if (
										(Board[i - 1][j] < 0 || (Board[i - 1][j] >= 0 && Board[i - 1][j] == cur[0][0])) &&
										(Board[i - 1][j + 1] < 0 || (Board[i - 1][j + 1] >= 0 && Board[i - 1][j + 1] == cur[0][1])) &&
										(Board[i][j + 2] < 0 || (Board[i][j + 2] >= 0 && Board[i][j + 2] == cur[0][1])) &&
										(Board[i + 1][j + 2] < 0 || (Board[i + 1][j + 2] >= 0 && Board[i + 1][j + 2] == cur[1][1]))
										)
									{
										//found
										found = true;
										curi = i;
										curj = j;
										break;
									}
								}
								available = 0;
							}
							//last row and last col
							if (i == row + 4 - 2 && j == col + 4 - 2)
							{
								if ((cur[0][0] == Board[i][j - 1] || cur[0][0] == Board[i - 1][j]))available++;
								if ((cur[0][1] == Board[i - 1][j + 1]))available++;
								if ((cur[1][0] == Board[i + 1][j - 1]))available++;


								//double check
								if (available >= 2)
								{
									//check 4 directions
									if (
										(Board[i][j - 1] < 0 || (Board[i][j - 1] >= 0 && Board[i][j - 1] == cur[0][0])) &&
										(Board[i - 1][j] < 0 || (Board[i - 1][j] >= 0 && Board[i - 1][j] == cur[0][0])) &&
										(Board[i - 1][j + 1] < 0 || (Board[i - 1][j + 1] >= 0 && Board[i - 1][j + 1] == cur[0][1])) &&
										(Board[i + 1][j - 1] < 0 || (Board[i + 1][j - 1] >= 0 && Board[i + 1][j - 1] == cur[1][0]))
										)
									{
										//found
										found = true;
										curi = i;
										curj = j;
										break;
									}
								}

								available = 0;
							}
							// 1st row
							if (i == 0 && j > 0 && j < col + 4 - 2)
							{
								if ((cur[0][0] == Board[i][j - 1]))available++;
								if ((cur[0][1] == Board[i][j + 2]))available++;
								if ((cur[1][0] == Board[i + 1][j - 1] || cur[1][0] == Board[i + 2][j]))available++;
								if ((cur[1][1] == Board[i + 2][j + 1] || cur[1][1] == Board[i + 1][j + 2]))available++;


								//double check
								if (available >= 2)
								{
									//check 6 directions
									if (
										(Board[i][j - 1] < 0 || (Board[i][j - 1] >= 0 && Board[i][j - 1] == cur[0][0])) &&
										(Board[i][j + 2] < 0 || (Board[i][j + 2] >= 0 && Board[i][j + 2] == cur[0][1])) &&
										(Board[i + 1][j + 2] < 0 || (Board[i + 1][j + 2] >= 0 && Board[i + 1][j + 2] == cur[1][1])) &&
										(Board[i + 2][j + 1] < 0 || (Board[i + 2][j + 1] >= 0 && Board[i + 2][j + 1] == cur[1][1])) &&
										(Board[i + 2][j] < 0 || (Board[i + 2][j] >= 0 && Board[i + 2][j] == cur[1][0])) &&
										(Board[i + 1][j - 1] < 0 || (Board[i + 1][j - 1] >= 0 && Board[i + 1][j - 1] == cur[1][0]))
										)
									{
										//found
										found = true;
										curi = i;
										curj = j;
										break;
									}
								}
								available = 0;
							}

							//last row
							if (i == row + 4 - 2 && j > 0 && j < col + 4 - 2)
							{
								if ((cur[0][0] == Board[i][j - 1] || cur[0][0] == Board[i - 1][j]))available++;
								if ((cur[0][1] == Board[i][j + 2] || cur[0][1] == Board[i - 1][j + 1]))available++;
								if ((cur[1][0] == Board[i + 1][j - 1]))available++;
								if ((cur[1][1] == Board[i + 1][j + 2]))available++;


								//double check
								if (available >= 2)
								{
									//check 6 directions
									if (
										(Board[i][j - 1] < 0 || (Board[i][j - 1] >= 0 && Board[i][j - 1] == cur[0][0])) &&
										(Board[i - 1][j] < 0 || (Board[i - 1][j] >= 0 && Board[i - 1][j] == cur[0][0])) &&
										(Board[i - 1][j + 1] < 0 || (Board[i - 1][j + 1] >= 0 && Board[i - 1][j + 1] == cur[0][1])) &&
										(Board[i][j + 2] < 0 || (Board[i][j + 2] >= 0 && Board[i][j + 2] == cur[0][1])) &&
										(Board[i + 1][j + 2] < 0 || (Board[i + 1][j + 2] >= 0 && Board[i + 1][j + 2] == cur[1][1])) &&
										(Board[i + 1][j - 1] < 0 || (Board[i + 1][j - 1] >= 0 && Board[i + 1][j - 1] == cur[1][0]))
										)
									{
										//found
										found = true;
										curi = i;
										curj = j;
										break;
									}
								}
								available = 0;
							}

							//1st col
							if (j == 0 && i > 0 && i < row + 4 - 2)
							{
								if ((cur[0][0] == Board[i - 1][j]))available++;
								if ((cur[0][1] == Board[i][j + 2] || cur[0][1] == Board[i - 1][j + 1]))available++;
								if ((cur[1][0] == Board[i + 2][j]))available++;
								if ((cur[1][1] == Board[i + 2][j + 1] || cur[1][1] == Board[i + 1][j + 2]))available++;


								//double check
								if (available >= 2)
								{
									//check 6 directions
									if (

										(Board[i - 1][j] < 0 || (Board[i - 1][j] >= 0 && Board[i - 1][j] == cur[0][0])) &&
										(Board[i - 1][j + 1] < 0 || (Board[i - 1][j + 1] >= 0 && Board[i - 1][j + 1] == cur[0][1])) &&
										(Board[i][j + 2] < 0 || (Board[i][j + 2] >= 0 && Board[i][j + 2] == cur[0][1])) &&
										(Board[i + 1][j + 2] < 0 || (Board[i + 1][j + 2] >= 0 && Board[i + 1][j + 2] == cur[1][1])) &&
										(Board[i + 2][j + 1] < 0 || (Board[i + 2][j + 1] >= 0 && Board[i + 2][j + 1] == cur[1][1])) &&
										(Board[i + 2][j] < 0 || (Board[i + 2][j] >= 0 && Board[i + 2][j] == cur[1][0]))

										)
									{
										//found
										found = true;
										curi = i;
										curj = j;
										break;
									}
								}
								available = 0;
							}


							//last col
							if (j == col + 4 - 2 && i > 0 && i < row + 4 - 2)
							{
								if ((cur[0][0] == Board[i][j - 1] || cur[0][0] == Board[i - 1][j]))available++;
								if ((cur[0][1] == Board[i - 1][j + 1]))available++;
								if ((cur[1][0] == Board[i + 1][j - 1] || cur[1][0] == Board[i + 2][j]))available++;
								if ((cur[1][1] == Board[i + 2][j + 1]))available++;


								//double check
								if (available >= 2)
								{
									//check 6 directions
									if (
										(Board[i][j - 1] < 0 || (Board[i][j - 1] >= 0 && Board[i][j - 1] == cur[0][0])) &&
										(Board[i - 1][j] < 0 || (Board[i - 1][j] >= 0 && Board[i - 1][j] == cur[0][0])) &&
										(Board[i - 1][j + 1] < 0 || (Board[i - 1][j + 1] >= 0 && Board[i - 1][j + 1] == cur[0][1])) &&
										(Board[i + 2][j + 1] < 0 || (Board[i + 2][j + 1] >= 0 && Board[i + 2][j + 1] == cur[1][1])) &&
										(Board[i + 2][j] < 0 || (Board[i + 2][j] >= 0 && Board[i + 2][j] == cur[1][0])) &&
										(Board[i + 1][j - 1] < 0 || (Board[i + 1][j - 1] >= 0 && Board[i + 1][j - 1] == cur[1][0]))
										)
									{
										//found
										found = true;
										curi = i;
										curj = j;
										break;
									}
								}
								available = 0;
							}



							//not border
							if (i > 0 && i < row + 4 - 2 && j > 0 && j < col + 4 - 2)
							{
								if ((cur[0][0] == Board[i][j - 1] || cur[0][0] == Board[i - 1][j]))available++;
								if ((cur[0][1] == Board[i][j + 2] || cur[0][1] == Board[i - 1][j + 1]))available++;
								if ((cur[1][0] == Board[i + 1][j - 1] || cur[1][0] == Board[i + 2][j]))available++;
								if ((cur[1][1] == Board[i + 2][j + 1] || cur[1][1] == Board[i + 1][j + 2]))available++;


								//double check
								if (available >= 2)
								{
									//check 8 directions
									if (
										(Board[i][j - 1] < 0 || (Board[i][j - 1] >= 0 && Board[i][j - 1] == cur[0][0])) &&
										(Board[i - 1][j] < 0 || (Board[i - 1][j] >= 0 && Board[i - 1][j] == cur[0][0])) &&
										(Board[i - 1][j + 1] < 0 || (Board[i - 1][j + 1] >= 0 && Board[i - 1][j + 1] == cur[0][1])) &&
										(Board[i][j + 2] < 0 || (Board[i][j + 2] >= 0 && Board[i][j + 2] == cur[0][1])) &&
										(Board[i + 1][j + 2] < 0 || (Board[i + 1][j + 2] >= 0 && Board[i + 1][j + 2] == cur[1][1])) &&
										(Board[i + 2][j + 1] < 0 || (Board[i + 2][j + 1] >= 0 && Board[i + 2][j + 1] == cur[1][1])) &&
										(Board[i + 2][j] < 0 || (Board[i + 2][j] >= 0 && Board[i + 2][j] == cur[1][0])) &&
										(Board[i + 1][j - 1] < 0 || (Board[i + 1][j - 1] >= 0 && Board[i + 1][j - 1] == cur[1][0]))
										)
									{
										//found
										found = true;
										curi = i;
										curj = j;
										break;
									}
								}
								available = 0;

							}

						}
					}
				}
				if (found == true)
				{
					Board[curi][curj] = cur[0][0];
					Board[curi][curj + 1] = cur[0][1];
					Board[curi + 1][curj] = cur[1][0];
					Board[curi + 1][curj + 1] = cur[1][1];

					if (curi != 0 && curj != 0)
					{
						//shift back;
						for (int m = 2; m < row + 4; m++)
						{
							for (int n = 2; n < col + 4; n++)
							{
								Board[m - 2][n - 2] = Board[m][n];
								//replace with -1									
								Board[m][n] = -1;
							}
						}

						if(curi + 1 == row + 4 - 1 || curi + 1 == row + 4 - 2)row += 2;
						if(curj + 1 == col + 4 - 1 || curi + 1 == col + 4 - 2)col += 2;
						//row += 2;
						//col += 2;
					}	

					if (curi == 0)
					{
						//shift left;
						for (int m = 0; m < row + 4; m++)
						{
							for (int n = 2; n < col + 4; n++)
							{
								Board[m][n - 2] = Board[m][n];
								//replace with -1									
								Board[m][n] = -1;
							}
						}

						row += 2;
					}

					if (curj == 0)
					{
						//shift up;
						for (int m = 2; m < row + 4; m++)
						{
							for (int n = 0; n < col + 4; n++)
							{
								Board[m - 2][n] = Board[m][n];
								//replace with -1									
								Board[m][n] = -1;
							}
						}
						col += 2;
					}
					break;
				}

				Rotation(cur);
				rotation++;
			}

		}

		
		//new block is guaranteed to be added
		count++;
		//print
		cout << "\nLink " << count;
		if (rotation < 4 && rotation > 0)
		{
			cout << "//note this tile had to be rotated " << rotation * 90 << " degrees clockwise" << endl;
		}
		else
		{
			cout << endl;
		}

		//cout << row << col << endl;
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)			
			{
				if (Board[i][j] >= 0)
					cout << Board[i][j];
				if (Board[i][j] < 0)
				{
					cout << ' ';
					//cout << Board[i][j];
				}
				if (j == col - 1)
				{

					cout << ' ' << endl;
				}


			}


		/*for (int i = 0; i < 50; i++)
			for (int j = 0; j < 50; j++)
			{
				if (Board[i][j] >= 0)
					cout << Board[i][j];
				if (Board[i][j] < 0)
				{
					cout << ' ';
				}
				if (j == 50 - 1)
				{

					cout << ' ' << endl;
				}


			}*/

		
		rotation = 0;
		found = false;



		if (*(tiles + line + 2) == NULL)break;

		line += 3;

	}

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
