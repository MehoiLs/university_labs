namespace Lab1
{
    internal class Program
    {
        public static void Main(string[] args)
        {
            var list = new LinkedList<int>();
            
            list.InsertFirst(1);
            list.InsertFirst(2);
            list.InsertFirst(3);
            
            System.Console.WriteLine(list.ToString());
        }
    }
}