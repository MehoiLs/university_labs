using Lab3.Entity.Hotel.People;

namespace Lab3.Entity.Hotel;

public class Hotel
{
    public long Id { get; set; }
    public string Name { get; set; }
    public string Address { get; set; }
    public string Email { get; set; }
    public string Phone { get; set; }
    public DateTime YearOpenedIn { get; set; }
    public double Area { get; set; }

    //  Owner-to-Hotels (One-to-Many)
    public long OwnerId { get; set; }
    public Owner? Owner { get; set; }

    public ICollection<Service> Services { get; set; } = new List<Service>();
}