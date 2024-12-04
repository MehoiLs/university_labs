using System.ComponentModel.DataAnnotations;

namespace Lab3.Entity.Hotel.People;

public class Employee
{
    [Key]
    public long Id { get; set; }
    
    [MinLength(2, ErrorMessage = "Min length of FullName must be 2")]
    public required string FullName { get; set; }
    
    [RegularExpression("^[A-Za-z0-9]{6,15}$", ErrorMessage = "Invalid passport format.")]
    public required string Passport { get; set; }
    
    [Range(typeof(DateTime), "1900-01-01", "2100-12-31", ErrorMessage = "Birthdate must be between 1900 and 2100.")]
    public required DateTime BirthDate { get; set; }
    
    public long HotelId { get; set; }
    public Hotel Hotel { get; set; }
    public long OccupationId { get; set; }  
    public Occupation Occupation { get; set; }
}