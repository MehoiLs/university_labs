using System.ComponentModel.DataAnnotations;
using Lab3.Entity.Hotel.People;

namespace Lab3.Entity.Hotel;

public class Hotel
{
    public long Id { get; set; }
    public required string Name { get; set; }
    public required string Address { get; set; }
    public required string Email { get; set; }
    public required string Phone { get; set; }
    public required string YearOpenedIn { get; set; }
    public double Area { get; set; }

    //  Owner-to-Hotels (One-to-Many)
    [Required]
    public long OwnerId { get; set; }
    public Owner? Owner { get; init; } = null!;
}