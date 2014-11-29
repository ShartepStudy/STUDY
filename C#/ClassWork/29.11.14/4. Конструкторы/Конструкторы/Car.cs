using System;

namespace Classes
{
    class Car
    {
        // Текущая скорость.
        private int m_currentSpeed;

        // Имя водителя.
        private string m_driverName;

        public Car() : 
            this("No driver", 0) 
        {}

        public Car(string driverName) : 
            this(driverName, 0) 
        {}

        // Главный конструктор.
        public Car(string driverName, int speed) : this()
        {
            m_currentSpeed = speed;
            m_driverName = driverName;
        }

        public void SetDriver(string driverName)
        {
            m_driverName = driverName;
        }

        // Распечатка текущих данных.
        public void PrintState()
        {
            Console.WriteLine("{0} drives at {1} km/h.", m_driverName, m_currentSpeed);
        }

        // Увеличение скорости.
        public void SpeedUp(int delta)
        {
            m_currentSpeed += delta;
        }
    }
}