using System.ComponentModel.DataAnnotations;

namespace Lab3.Model.Create;

public class HotelCreateModel
{
    [MaxLength(100)] 
    public required string Name { get; set; }

    [MaxLength(200)]
    public required string Address { get; set; }

    [EmailAddress] 
    public required string Email { get; set; }

    [RegularExpression(@"^\+?[0-9]{7,15}$", ErrorMessage = "Invalid phone number format.")]
    public required string Phone { get; set; }

    [Range(typeof(DateTime), "1900-01-01", "2100-12-31", ErrorMessage = "YearOpenedIn must be between 1900 and 2100.")]
    public required DateTime YearOpenedIn { get; set; }

    [Range(0.1, double.MaxValue, ErrorMessage = "Area must be greater than 0.")]
    public double Area { get; set; }

    [Range(1, long.MaxValue, ErrorMessage = "OwnerId must be greater that 0.")]
    public required long OwnerId { get; set; }

    public List<long>? OfferingIds { get; set; } = null!;
}