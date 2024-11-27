using Lab3.Entity.Hotel.People;

namespace Lab3.Entity.Hotel;

public class Hotel
{
    //TODO: constraints in db
    //TODO: FILL DATABASE WITH MOCK-DATA!!!
    public long Id { get; set; }
    public string Name { get; set; }
    public string Address { get; set; }
    public string Email { get; set; }
    public string Phone { get; set; }
    public DateTime YearOpenedIn { get; set; }
    public double Area { get; set; }

    //  Owner-to-Hotels (One-to-Many)
    public long OwnerId { get; set; }
    public Owner Owner { get; set; } = null!;

    public ICollection<HotelOffering>? Offerings { get; set; } = new List<HotelOffering>();
    public ICollection<HotelKeyCard>? KeyCards { get; set; } = new List<HotelKeyCard>();
}