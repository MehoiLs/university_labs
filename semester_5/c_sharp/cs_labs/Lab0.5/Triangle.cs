using System;

namespace cs_lab_0._5 
{
    /**
     * A triangle. Inheritor of [Figure]. 
     */
    public class Triangle : Figure 
    {
        
        private double a;
        public double A
        {
            get => a;
            set
            {
                if (value > 0)
                {
                    a = value;
                }
            }
        }
        
        private double b;
        public double B
        {
            get => b;
            set
            {
                if (value > 0)
                {
                    b = value;
                }
            }
        }
        
        private double c;
        public double C
        {
            get => c;
            set
            {
                if (value > 0)
                {
                    c = value;
                }
            }
        }

        public Triangle(double a, double b, double c) 
        {
            this.a = a;
            this.b = b;
            this.c = c;
        }

        public override double CalculateArea() 
        {
            var semiPerimeter = (a + b + c) / 2;
            return Math.Sqrt(
                semiPerimeter * (semiPerimeter - a) * (semiPerimeter - b) * (semiPerimeter - c)
            );
        }

        public override double CalculatePerimeter() 
        {
            return a + b + c;
        }
        
    }
}