using System.ComponentModel.DataAnnotations;
using Lab3.Entity.Enums;

namespace Lab3.Entity.Hotel.People;

public class Occupation
{
    [Key]
    public long Id { get; set; }
    
    [MinLength(100, ErrorMessage = "Salary must be at least 100$")]
    [MaxLength(100000, ErrorMessage = "Salary cannot be more than 100.000$")]
    public long Salary { get; set; }

    public OccupationType Type { get; set; }
}