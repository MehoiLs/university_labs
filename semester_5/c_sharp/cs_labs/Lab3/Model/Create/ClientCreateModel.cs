using System.ComponentModel.DataAnnotations;

namespace Lab3.Model.Create;

public class ClientCreateModel
{
    [MaxLength(100)] 
    public required string FullName { get; set; }
    [MaxLength(10)] 
    public required string Passport { get; set; }
    
    public required long HotelId { get; set; }
    
}