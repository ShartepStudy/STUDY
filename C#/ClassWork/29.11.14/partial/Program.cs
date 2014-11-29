using System;

partial class Test
{
    public void A()
    {
        Console.WriteLine("A");
    }
}

partial class Test
{
    public void B()
    {
        Console.WriteLine("B");
    }
}

class Sample
{
    static void Main(string[] args)
    {
        Test obj = new Test();
        obj.A();
    }
}