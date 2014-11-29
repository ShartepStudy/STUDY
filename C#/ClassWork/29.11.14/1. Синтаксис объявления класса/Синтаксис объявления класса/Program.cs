using System;

namespace Classes
{
    class Program
    {
        static void Main()
        {
            Student student = new Student();

            student.ShowName();

            Student.ShowAcademy();

            Console.WriteLine("Mark: {0}", student.GenerateMark());
        }
    }
}