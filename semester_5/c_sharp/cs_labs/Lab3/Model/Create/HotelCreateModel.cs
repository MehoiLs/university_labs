using System.ComponentModel.DataAnnotations;

namespace Lab3.Model.Create;

public class HotelCreateModel
{
    public required string Name { get; set; }
    public required string Address { get; set; }
    [EmailAddress] public required string Email { get; set; }
    public required string Phone { get; set; }
    public required DateTime YearOpenedIn { get; set; }

    public double Area { get; set; }
    public required long OwnerId { get; set; }
}