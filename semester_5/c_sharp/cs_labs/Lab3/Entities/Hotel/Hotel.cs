using Lab3.Entities.Hotel.People;

namespace Lab3.Entities.Hotel;

public class Hotel
{
    public long Id { get; set; }
    public required string Name { get; set; }
    public required string Address { get; set; }
    public required string Email { get; set; }
    public required string Phone { get; set; }
    public required string YearOpenedIn { get; set; }
    public double Area { get; set; }

    public required Owner Owner { get; set; }
    // public required List<Employee> Employees { get; set; }
    // public required List<Client> Clients { get; set; }
}