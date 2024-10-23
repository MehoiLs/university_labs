using System;
using Lab0_5;

namespace Lab1
{
    internal static class Program
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("Creating int list:");
            var intList = new LinkedList<int>();
            intList.InsertLast(1, 2, 3, 4, 5);
            intList.InsertFirst(90, 91, 92, 93, 94);
            Console.WriteLine(intList.ToString());
            
            Console.WriteLine("\nRemoving the first and the last element:");
            intList.RemoveFirst();
            intList.RemoveLast();
            Console.WriteLine(intList.ToString());
            
            Console.WriteLine("\nGetting the first and the last element:");
            Console.WriteLine($"First: {intList.GetFirst()}\nLast: {intList.GetLast()}");
            
            Console.WriteLine("\nCleaning up the list...");
            intList.Clean();
            Console.WriteLine($"Result: {intList}\n");
            
            Console.WriteLine("Inserting new elements into the same list:");
            intList.InsertLast(5, 6, 7, 8, 9);
            Console.WriteLine($"Result: {intList}\n");
            
            Console.WriteLine("Creating figure list:");
            var figureList = new LinkedList<Figure>();
            figureList.InsertLast(
                new Circle(4),
                new Square(6),
                new Triangle(3, 5, 7),
                new Square(22),
                new Circle(100)
            );
            Console.WriteLine(figureList.ToString());
            
        }
    }
}