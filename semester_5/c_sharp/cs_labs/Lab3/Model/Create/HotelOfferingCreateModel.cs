﻿using System.ComponentModel.DataAnnotations;

namespace Lab3.Model.Create;

public class HotelOfferingCreateModel
{
    [MaxLength(100)] 
    public string Name { get; set; }
    [MaxLength(2000)] 
    public string Description { get; set; }
    [Range(0.1, double.MaxValue, ErrorMessage = "Average price must be greater than 0.")]
    public double AveragePrice { get; set; }
}