public class playGame
{
	static java.util.Scanner scanner = new java.util.Scanner(System.in);
	
	static int gridSize = 4;
	
	static boolean player1Turn = true;

	static boolean[][] player1Ships = {
		{false, false, true, true},
		{true, false, false, false},
		{true, false, true, false},
		{true, false, true, false}
	};
	
	static boolean[][] player2Ships = {
		{false, false, true, true},
		{true, false, false, false},
		{true, false, true, false},
		{true, false, true, false}
	};
	
	static boolean[][] player1Hits = {
		{false, false, false, false},
		{false, false, false, false},
		{false, false, false, false},
		{false, false, false, false}
	};
	
	static boolean[][] player2Hits = {
		{false, false, false, false},
		{false, false, false, false},
		{false, false, false, false},
		{false, false, false, false}
	};
	
	public static void main(String[] args)
	{
		boolean gameOver = false;
		String player = "";
		
		while (!gameOver)
		{
			renderBoards();

			player = player1Turn ? "Spiller 1" : "Spiller 2";
			boolean[][] targetHits = player1Turn ? player2Hits : player1Hits;
			boolean[][] targetShips = player1Turn ? player2Ships : player1Ships;
			
			int[] coordinates = getInputCoordinates(player, targetHits);
			
			int x = coordinates[0];
			int y = coordinates[1];

			hit(targetHits, x, y);

			if (targetShips[y][x])
			{
				System.out.println("Træffer!");
			}
			else
			{
				System.out.println("Forbier!");
				player1Turn = !player1Turn;
			}

			gameOver = hasLost(targetHits, targetShips);
		}

		System.out.println(player + " har vundet!");
	}

	static int[] getInputCoordinates(String _player, boolean[][] _hits)
	{
		boolean inputIsValid = false;
		int x = 0;
		int y = 0;
				
		while (!inputIsValid)
		{
			System.out.print(String.format("%s indtast koordinater (x, y): ", _player));
			String errorString = "input skal angives som: x, y";

			String[] input = scanner.nextLine().split(", ");
			if (input.length == 2)
			{
				inputIsValid = true;
			}
			
			if (inputIsValid)
			{
				try 
				{
					x = Integer.parseInt(input[0])-1;	
					y = Integer.parseInt(input[1])-1;	

					if (x < 0 || gridSize <= x ||
						y < 0 || gridSize <= y)
					{
						inputIsValid = false;
						errorString = String.format("koordinater skal være mellem 1 og %d", gridSize);
					}
				}
				catch (Exception e)
				{
					inputIsValid = false;
					errorString = "input skal være hele tal.";
				}
			}

			if (inputIsValid)
			{
				if (_hits[y][x])
				{
					inputIsValid = false;
					errorString = "koordinat allerede ramt.";
				}
			}
			
			if (!inputIsValid)
			{
				System.out.println("Ugyldigt input: " + errorString);
			}

			if (inputIsValid)
			{
				System.out.print(String.format("Bekræft affyring mod koordinater: (%d, %d)? (Y/N) ", x+1, y+1));
				
				String answer = scanner.nextLine().toUpperCase();
				
				while (
					!answer.equals("Y") &&
					!answer.equals("N"))
				{
					answer = scanner.nextLine().toUpperCase();
				}

				if (answer.equals("N"))
				{
					inputIsValid = false;
				}
			}
		}

		return new int[]{x, y};
	}

	static void hit(boolean[][] _grid, int _x, int _y)
	{
		_grid[_y][_x] = true;
	}

	static boolean hasLost(boolean[][] _hits, boolean[][] _ships)
	{
		for (int i = 0; i < gridSize; i++)
		{
			for (int j = 0; j < gridSize; j++)
			{
				if (_ships[i][j] && !_hits[i][j]) return false;
			}
		}
		return true;
	}

	static void renderBoards()
	{
		String[] lines = new String[gridSize + 2];
		char[][] player1Board = new char[gridSize][gridSize];
		char[][] player2Board = new char[gridSize][gridSize];

		if (player1Turn)
		{
			for (int i = 0; i < gridSize; i++)
			{
				for (int j = 0; j < gridSize; j++)
				{
					if (player2Hits[i][j] == false &&
						player2Ships[i][j] == false)
					{
						player1Board[i][j] = '.';
						player2Board[i][j] = '.';
					}
					else if (
						player2Hits[i][j] == true &&
						player2Ships[i][j] == false)
					{
						player1Board[i][j] = 'X';
						player2Board[i][j] = 'X';
					}
					else if (
						player2Hits[i][j] == false &&
						player2Ships[i][j] == true)
					{
						player1Board[i][j] = '.';
						player2Board[i][j] = '#';
					}
					else if (
						player2Hits[i][j] == true &&
						player2Ships[i][j] == true)
					{
						player1Board[i][j] = 'O';
						player2Board[i][j] = 'O';
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < gridSize; i++)
			{
				for (int j = 0; j < gridSize; j++)
				{
					if (player1Hits[i][j] == false &&
						player1Ships[i][j] == false)
					{
						player2Board[i][j] = '.';
						player1Board[i][j] = '.';
					}
					else if (
						player1Hits[i][j] == true &&
						player1Ships[i][j] == false)
					{
						player2Board[i][j] = 'X';
						player1Board[i][j] = 'X';
					}
					else if (
						player1Hits[i][j] == false &&
						player1Ships[i][j] == true)
					{
						player2Board[i][j] = '.';
						player1Board[i][j] = '#';
					}
					else if (
						player1Hits[i][j] == true &&
						player1Ships[i][j] == true)
					{
						player2Board[i][j] = 'O';
						player1Board[i][j] = 'O';
					}
				}
			}
		}

		lines[0] = new String(" " + "-".repeat(gridSize) + "   " + "-".repeat(gridSize));
		
		for (int i = 1; i < gridSize+1; i++)
		{
			lines[i] = new String(
					"|" + new String(player1Board[i-1]) + "|" + " " +
					"|" + new String(player2Board[i-1]) + "|");
		}

		lines[gridSize+1] = new String(" " + "-".repeat(gridSize) + "   " + "-".repeat(gridSize));

		String result = String.join(System.lineSeparator(), lines);
		System.out.println(result);
	}
}
