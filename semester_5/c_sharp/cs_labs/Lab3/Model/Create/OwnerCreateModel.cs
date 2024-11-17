using System.ComponentModel.DataAnnotations;

namespace Lab3.Model.Create;

public class OwnerCreateModel
{
    [MaxLength(100)] 
    public required string FullName { get; set; }
}