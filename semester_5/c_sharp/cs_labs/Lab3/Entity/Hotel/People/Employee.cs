namespace Lab3.Entity.Hotel.People;

public class Employee
{
    public long Id { get; set; }
    public string FullName { get; set; }
    public string Passport { get; set; }
    public DateTime BirthDate { get; set; }
    public Occupation Occupation { get; set; }
}