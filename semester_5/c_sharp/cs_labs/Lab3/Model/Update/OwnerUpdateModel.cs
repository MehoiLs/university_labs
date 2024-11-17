using System.ComponentModel.DataAnnotations;

namespace Lab3.Model.Update;

public class OwnerUpdateModel
{
    [MaxLength(100)] 
    public required string FullName { get; set; }
}