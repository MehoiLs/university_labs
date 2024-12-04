using System.ComponentModel.DataAnnotations;
using Lab3.Entity.Hotel.People;

namespace Lab3.Entity.Hotel;

public class Hotel
{

    [Key]
    public long Id { get; init; }
    
    [MaxLength(100, ErrorMessage = "Name cannot be longer than 100 characters.")]
    public required string Name { get; init; }

    [MaxLength(200, ErrorMessage = "Address cannot be longer than 200 characters.")]
    public required string Address { get; init; }

    [EmailAddress(ErrorMessage = "Invalid email address.")]
    [MaxLength(100, ErrorMessage = "Email cannot be longer than 100 characters.")]
    public required string Email { get; init; }
    
    [RegularExpression(@"^\+?[0-9]{7,15}$", ErrorMessage = "Invalid phone number format.")]
    public required string Phone { get; init; }

    [Range(typeof(DateTime), "1900-01-01", "2100-12-31", ErrorMessage = "YearOpenedIn must be between 1900 and 2100.")]
    public DateTime YearOpenedIn { get; init; }

    [Range(0.1, double.MaxValue, ErrorMessage = "Area must be greater than 0.")]
    public required double Area { get; init; }

    [Range(1, long.MaxValue, ErrorMessage = "OwnerId must be greater than 0.")]
    public required long OwnerId { get; set; }

    //  Owner-to-Hotels (One-to-Many)
    public Owner Owner { get; init; } = null!;

    public ICollection<HotelOffering>? Offerings { get; set; } = new List<HotelOffering>();
    public ICollection<HotelKeyCard>? KeyCards { get; set; } = new List<HotelKeyCard>();
}