public class Main 
{
    public static void main(String[] args) 
    {
        if (args.length != 5)
        {   
            System.out.println("Wrong format, example: ./pandemic grid_size rounds infection_threshold recovery_threshold {<y,x>,<y,x>}");
            return ;
        } 
        try 
        {
            GameRules game = new GameRules(args); 
            game.simulate();
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}