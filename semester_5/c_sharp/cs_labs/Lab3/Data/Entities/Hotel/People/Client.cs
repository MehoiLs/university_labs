namespace Lab3.Entities.Hotel.People;

public class Client
{
    public long Id { get; set; }
    public required string FullName { get; set; }
    public required string Passport { get; set; }

    public required Data.Entities.Hotel.Hotel Hotel { get; set; }
}