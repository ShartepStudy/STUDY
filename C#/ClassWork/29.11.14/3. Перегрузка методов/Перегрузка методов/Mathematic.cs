using System;

namespace Classes
{
    class Mathematic
    {
        public static int Sum(int a, int b)
        {
            return a + b;
        }

        public static int Sum(int a, int b, int c = 8)
        {
            return a + b + c;
        }

        public static double Sum(double a, double b)
        {
            return a + b;
        }
    }
}