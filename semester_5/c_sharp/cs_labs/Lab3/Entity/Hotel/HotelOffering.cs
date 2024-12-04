using System.ComponentModel.DataAnnotations;
using Lab3.Entity.Hotel.Invoices;

namespace Lab3.Entity.Hotel;

public class HotelOffering
{
    [Key]
    public long Id { get; set; }
    
    [MaxLength(100, ErrorMessage = "Name cannot be longer than 100 characters.")]
    public required string Name { get; init; }
    
    [MaxLength(1000, ErrorMessage = "Description cannot be longer than 100 characters.")]
    public required string Description { get; init; }
    
    [Range(0.1, double.MaxValue, ErrorMessage = "AveragePrice must be greater than 0.")]
    public double AveragePrice { get; init; }
    

    public ICollection<ServiceInvoice>? Invoices { get; init; }
    public ICollection<Hotel>? Hotels { get; init; }
}