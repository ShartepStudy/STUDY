using System;

namespace Classes
{
    class Program
    {
        static void Main()
        {
            Console.WriteLine("Default constructor");

            Car car = new Car();

            for (int i = 0; i <= 10; i++)
            {
                car.SpeedUp(5);
                car.PrintState();
            }

            Console.WriteLine("\n\nParametrized constructor");

            car = new Car("Rubens Barrichello");

            for (int i = 0; i <= 10; i++)
            {
                car.SpeedUp(5);
                car.PrintState();
            }
        }
    }
}