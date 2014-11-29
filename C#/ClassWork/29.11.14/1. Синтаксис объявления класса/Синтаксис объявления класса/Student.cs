using System;

namespace Classes
{
    class Student
    {
        private static string s_academy = "Computer Academy \"Step\"";

        private string m_group;
        private string m_name = "John";
        private int m_studentID;
        private string m_surname;
        private const Student s = null;

        public int GenerateMark()
        {
            return new Random().Next(1, 12);
        }

        public static void ShowAcademy()
        {
            Console.WriteLine(s_academy);
        }

        public void ShowName()
        {
            Console.WriteLine(m_name);
        }
    }
}