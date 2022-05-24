import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class GameRules 
{
	public static final int HEALTHY = 0;
	public static final int INFECTED = 1;

	int grid_size;
	int rounds;
	int infection_threshold;
	int recovery_threshold;
	int [][]map;
	int [][]next_round_map;
	
	private void print_game()
	{
		for (int i = 0; i < grid_size; i++)
		{
			for (int j = 0; j < grid_size; j++)
			{
				if (map[i][j] == INFECTED)
					System.out.print("🤢");
				else
					System.out.print("😀");

			}
			System.out.print('\n');
		}
	}

	//checks if healthy or infected acoording to adjecency rules
	private boolean infected_adjacency(int y, int x)
	{
		int count = 0;
		int edges = 8;

		for (int i = -1; i < 2; i++)
		{	
			for (int j = -1; j < 2; j++)
			{
				if (i != 0 || j != 0)
				{
					if (y + i >= 0 && y + i < grid_size && x + j >= 0 && x + j < grid_size)
					{
						if (map[y + i][x + j] == INFECTED)
							count++;
					}
					else
						edges--;
				}
			}
		}
		if (map[y][x] == HEALTHY)
		{
			if (count > infection_threshold)
				return (true);
			return (false);
		}
		if (edges - count > recovery_threshold)
			return (false);
		return (true);
	}

	//main simulation
	public void simulate()
	{
		System.out.println("//-------start-------//");
		this.print_game();
		for (int i = 0; i < rounds; i++)
		{	
			for (int y = 0; y < grid_size; y++)
			{
				for (int x = 0; x < grid_size; x++)
				{
					if (infected_adjacency(y, x))
						next_round_map[y][x] = INFECTED;
					else
						next_round_map[y][x] = HEALTHY;
				}
			}
			for (int y = 0; y < grid_size; y++)
				for (int x = 0; x < grid_size; x++)
					map[y][x] = next_round_map[y][x];
		}
		System.out.println("//-------end-------//");
		this.print_game();
	}

	private Boolean verify_values(String[] av)
	{
		if (grid_size < 0 || rounds < 0 || infection_threshold < 0 || recovery_threshold < 0)
			return (true);
		if (av[4].charAt(0) != '{' || av[4].charAt(av[4].length() - 1) != '}')
			return (true);
		av[4] = av[4].replace("{", "");
		av[4] = av[4].replace("}", "");
		return (false);
	}
	
	public GameRules(String[] av) throws Exception
	{
		//allocate/initialize vars
		grid_size = Integer.parseInt(av[0]);
		rounds = Integer.parseInt(av[1]);
		infection_threshold = Integer.parseInt(av[2]);
		recovery_threshold = Integer.parseInt(av[3]);
		map = new int[grid_size][grid_size];
		next_round_map = new int [grid_size][grid_size];
		for (int i = 0; i < grid_size; i++)
			for (int j = 0; j < grid_size; j++)
				map[i][j] = HEALTHY;
		
		//verifiy valid values
		if (verify_values(av))
			throw new Exception("wrong value in arguments");
		if (!av[4].matches("(<\\d+,\\d+>,)*(<\\d+,\\d+>)"))
			throw new Exception("invalid formatting");
		
		//parse stating coordinates
		String[] coords = av[4].split(">,<");
		for (int i = 0; i < coords.length; i++)
		{
			coords[i] = coords[i].replace("<", "");
			coords[i] = coords[i].replace(">", "");
			Matcher matcher = Pattern.compile("\\d+").matcher(coords[i]);
			matcher.find();
			int y = Integer.valueOf(matcher.group());
			matcher.find();
			int x = Integer.valueOf(matcher.group());

			if (x < 0 || y < 0 || x >= grid_size || y >= grid_size)
				throw new Exception("number out of range");
			map[y][x] = INFECTED;
		}
	}
}
