using System;

namespace Classes
{
    class Program
    {
        static void Main()
        {
            Bank.GetBonus();
            Console.WriteLine("-----------------");
            Bank bank = new Bank(1000000);

            double bonus = 10000;

            Console.WriteLine("Current bonus percentage: " + Bank.GetBonus());
            Console.WriteLine("Your deposit: {0:C}", bonus);
            Console.WriteLine("Available: {0:C}", bank.CalculatePercentage(bonus));
        }
    }
}