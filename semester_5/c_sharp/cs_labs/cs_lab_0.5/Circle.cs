using System;

namespace cs_lab_0._5 
{
    /**
     * A circle. Inheritor of [Figure]. 
     */
    public class Circle : Figure 
    {
        
        private double radius;
        public double Radius
        {
            get => radius;
            set
            {
                if (value > 0)
                {
                    radius = value;
                }
            }
        }

        public Circle(double radius) 
        {
            this.radius = radius;
        }

        public override double CalculateArea() 
        {
            return Math.PI * radius * radius;
        }

        public override double CalculatePerimeter() 
        {
            return 2 * Math.PI * radius;
        }
        
    }
}