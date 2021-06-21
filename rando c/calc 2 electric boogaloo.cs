using System;

namespace calc2_electric_boogaloo
{
    class Program
    {
        static void Main(string[] args)
        {
            double Dispute (double j, double g, double r, double w)
            {
                double dis = j * Math.Pow(Math.Abs(500 - g), 1/3) / Math.Pow((6 - r), w);
                return dis;
            }

            double Gift (double e, double j, double p, double g, double r)
            {
                double gif = e * (j+p) * Math.Pow(Math.Abs(500 - g), 1 / 3) / (6 - r);
                return gif;
            }

            Console.WriteLine("welcome to the super special calculator! \n for any complaints about the formula, @jack over it, i just coded this thing");
            Console.WriteLine("would you like to run a dispute calc or a gift card calc? \n type dispute or gift");
            string calc = Console.ReadLine();

            if (calc == "dispute")
            {
                Console.Write("\n what's their joke rating? ");
                string joke = Console.ReadLine();
                double j = Convert.ToDouble(joke);

                Console.Write("\n how many google results does this game have? please give the result in millions! ");
                string google = Console.ReadLine();
                double g = Convert.ToDouble(google);

                Console.Write("\n how many stars does the game have? please type 4 if you cannot find a rating. ");
                string rating = Console.ReadLine();
                double r = Convert.ToDouble(rating);

                Console.Write("\n how nice was this player? 0 = nice, 1 = average, 2 = rude. decimals are accepted. ");
                string nice = Console.ReadLine();
                double w = Convert.ToDouble(nice);

                double dispute = Dispute(j, g, r, w);

                Console.WriteLine("\nthis player's dispute score is: " + dispute);
            }

            else if (calc == "gift")
            {
                double gift = 0;
                int count = 1;

                while (count != 6)
                {
                    Console.Write("\n what's the player's rating? ");
                    string player = Console.ReadLine();
                    double p = Convert.ToDouble(player);

                    Console.Write("\n what's their joke rating? ");
                    string joke = Console.ReadLine();
                    double j = Convert.ToDouble(joke);

                    Console.Write("\n did they enjoy the tournament? 1 = yes, 0.5 = no ");
                    string enjoyment = Console.ReadLine();
                    double e = Convert.ToDouble(enjoyment);

                    Console.Write("\n how many google results does this game have? please give the result in millions! ");
                    string google = Console.ReadLine();
                    double g = Convert.ToDouble(google);

                    Console.Write("\n how many stars does the game have? please type 4 if you cannot find a rating. ");
                    string rating = Console.ReadLine();
                    double r = Convert.ToDouble(rating);

                    Console.Write("\n did they play a quagnag mirror? 1 = yes, 0 = no");
                    string not_tcgo = Console.ReadLine();
                    double n = Convert.ToDouble(not_tcgo);

                    gift = gift + Gift(e, j, p, g, r) + (n * Gift(e, j, p, g, r));

                    count ++;

                }

                Console.WriteLine("\nthis player's gift card score is: " + gift);
            }

            Console.ReadKey();
        }
    }
}
