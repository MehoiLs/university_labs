namespace cs_lab_0._5
{
    internal static class Program
    {
        public static void Main()
        {
            Figure square = new Square(3);
            Figure circle = new Circle(3);
            Figure triangle = new Triangle(3, 4, 5);
            
            Print("Square. S: {0}, P: {1}", square.CalculateArea(), square.CalculatePerimeter());
            Print("Circle. S: {0}, P: {1}", circle.CalculateArea(), circle.CalculatePerimeter());
            Print("Triangle. S: {0}, P: {1}", triangle.CalculateArea(), triangle.CalculatePerimeter());
        }

        private static void Print(string text, params object[] args)
        {
            System.Console.WriteLine(text, args);
        }
    }
}