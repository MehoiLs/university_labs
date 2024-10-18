namespace cs_lab_0._5 
{
    /**
     * A square. Inheritor of [Figure]. 
     */
    public class Square : Figure 
    {
        
        private double side;
        public double Side
        {
            get => side;
            set
            {
                if (value > 0)
                {
                    side = value;
                }
            }
        }

        public Square(double side) 
        {
            this.side = side;
        }

        public override double CalculateArea() 
        {
            return side * side;
        }

        public override double CalculatePerimeter() 
        {
            return 4 * side;
        }
        
    }
}