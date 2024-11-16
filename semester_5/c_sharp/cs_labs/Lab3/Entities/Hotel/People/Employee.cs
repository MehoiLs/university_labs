namespace Lab3.Entities.Hotel.People;

public class Employee
{
    public long Id { get; set; }
    public required string FullName { get; set; }
    public required string Passport { get; set; }
    public required DateTime BirthDate { get; set; }
    
    public required Occupation Occupation { get; set; }
}