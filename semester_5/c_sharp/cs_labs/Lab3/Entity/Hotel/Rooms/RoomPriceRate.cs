using System.ComponentModel.DataAnnotations;

namespace Lab3.Entity.Hotel.Rooms;

public class RoomPriceRate
{
    [Key]
    public long Id { get; init; }
    
    [Range(1, double.MaxValue, ErrorMessage = "Price per night must be greater than 1.")]
    public required int PricePerNight { get; init; }
    
    [Range(typeof(DateTime), "2024-01-01", "2100-12-31", ErrorMessage = "StartDate must be between 2024 and 2100.")]
    public required DateTime StartDate { get; init; }
    
    
    public required RoomProperties Properties { get; init; }
}