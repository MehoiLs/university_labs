namespace Lab3.Entity.Hotel.People;

public class Client
{
    public long Id { get; set; }
    public string FullName { get; set; }
    public string Passport { get; set; }

    public HotelKeyCard? KeyCard { get; set; }
    
    public long HotelId { get; set; }
    public Hotel Hotel { get; set; }
}