using System.ComponentModel.DataAnnotations;

namespace Lab3.Entity.Hotel.People;

public class Client
{
    [Key]
    public long Id { get; set; }
    
    [MinLength(2, ErrorMessage = "Min length of FullName must be 2")]
    public required string FullName { get; set; }
    
    [RegularExpression("^[A-Za-z0-9]{6,15}$", ErrorMessage = "Invalid passport format.")]
    public required string Passport { get; set; }

    public HotelKeyCard? KeyCard { get; set; }
    
    public long HotelId { get; set; }
    public Hotel Hotel { get; set; }
}