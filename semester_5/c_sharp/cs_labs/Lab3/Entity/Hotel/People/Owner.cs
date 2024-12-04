using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace Lab3.Entity.Hotel.People;

public class Owner
{
    [Key]
    public long Id { get; set; }
    
    [MinLength(2, ErrorMessage = "Min length of FullName must be 2")]
    public required string FullName { get; set; }

    //  Hotels-to-Owner (Many-to-One)
    public ICollection<Hotel>? Hotels { get; set; } = new List<Hotel>();
}