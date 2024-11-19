using System.ComponentModel.DataAnnotations;

namespace Lab3.Model.Update;

public class OwnerUpdateModel
{
    public required long Id { get; set; }
    [MaxLength(100)] 
    public required string FullName { get; set; }
}