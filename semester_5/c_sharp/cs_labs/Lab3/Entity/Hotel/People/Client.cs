namespace Lab3.Entity.Hotel.People;

public class Client
{
    public long Id { get; set; }
    public required string FullName { get; set; }
    public required string Passport { get; set; }

    public required Hotel Hotel { get; set; }
}