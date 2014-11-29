using System;

namespace Classes
{
    class Bank
    {
        private static double s_bonus;

        private double m_currentBalance;

        public Bank(double balance)
        {
            m_currentBalance = balance;
        }

        static Bank()
        {
            s_bonus = 1.04;
            Console.WriteLine("static ctor");
        }

        public static double GetBonus()
        {
            return s_bonus;
        }

        public static void SetBonus(double bonus)
        {
            s_bonus = bonus;
        }

        public double CalculatePercentage(double sum)
        {
            double result = -1;

            if (m_currentBalance - sum > 0)
            {
                double percent = sum * s_bonus;

                m_currentBalance -= percent;

                result = percent;
            }

            return result;
        }
    }
}