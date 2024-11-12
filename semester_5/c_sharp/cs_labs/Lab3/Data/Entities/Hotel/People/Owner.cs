namespace Lab3.Entities.Hotel.People;

public class Owner
{
    public long Id { get; set; }
    public required string FullName { get; set; }
    public List<Data.Entities.Hotel.Hotel>? Hotels { get; set; }
}