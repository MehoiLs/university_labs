using Lab3.Entity.Hotel.People;

namespace Lab3.Entity.Hotel;

public class HotelKeyCard
{
    public long Id { get; set; }
    public DateTime? LastAssignedAt { get; set; }
    
    public long? ClientId { get; set;}
    public Client? Client { get; set; }
    
    public long HotelId { get; set; }
    public Hotel Hotel { get; set; }
}