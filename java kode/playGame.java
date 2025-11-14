public class playGame
{
	public static void main(String[] args)
	{
		var scanner = new java.util.Scanner(System.in);

		int gridSize = 4;

		boolean[][] player1Ships = {
			{false, false, true, true},
			{true, false, false, false},
			{true, false, true, false},
			{true, false, true, false}
		};
		boolean[][] player2Ships = {
			{false, false, true, true},
			{true, false, false, false},
			{true, false, true, false},
			{true, false, true, false}
		};
		boolean[][] player1Hits = {
			{false, false, false, false},
			{false, false, false, false},
			{false, false, false, false},
			{false, false, false, false}
		};
		boolean[][] player2Hits = {
			{false, false, false, false},
			{false, false, false, false},
			{false, false, false, false},
			{false, false, false, false}
		};

		boolean gameOver = false;
		boolean player1Turn = true;

		while (!gameOver)
		{
			if (player1Turn)
			{
				System.out.print("Spiller 1 indtast koordinater (x, y): ");
				
				boolean inputIsValid = false;

				while (!inputIsValid)
				{
					String[] input = scanner.nextLine().split(", ");
					if (input.length == 2)
					{

					}
				}
				
				// int x = Integer.parseInt(input[0]);
				// int y = Integer.parseInt(input[1]);

			}
		}
	}

	public void hit(boolean[][] _grid, int _x, int _y)
	{
		_grid[_x][_y] = false;
	}
}
