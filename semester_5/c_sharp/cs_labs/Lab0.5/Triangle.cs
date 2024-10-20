using System;

namespace Lab0_5 
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
                if (value <= 0)
                {
                    throw new ArgumentException("a must be greater than 0.");
                }
                a = value;
                AssertTriangle();
            }
        }
        
        private double b;
        public double B
        {
            get => b;
            set
            {
                if (value <= 0)
                {
                    throw new ArgumentException("b must be greater than 0.");
                }
                b = value;
                AssertTriangle();
            }
        }
        
        private double c;
        public double C
        {
            get => c;
            set
            {
                if (value <= 0)
                {
                    throw new ArgumentException("c must be greater than 0.");
                }
                c = value;
                AssertTriangle();
            }
        }

        public Triangle(double a, double b, double c) 
        {
            this.a = a;
            this.b = b;
            this.c = c;
            AssertTriangle();
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
        
        public override string ToString()
        {
            return $"Triangle (a = {a}; b = {b}; c = {c})" +
                   $"(P = {CalculatePerimeter()})(S = {CalculateArea()}";
        }

        private void AssertTriangle()
        {
            if (a + b <= c || a + c <= b || b + c <= a)
            {
                throw new InvalidOperationException($"Triangle with given values (a={a}; b={b}; c={c}) cannot exist");
            }
        }
        
    }
}