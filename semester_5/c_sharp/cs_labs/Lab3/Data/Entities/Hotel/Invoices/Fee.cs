using Lab3.Entities.Enums;
using Lab3.Entities.Hotel.People;

namespace Lab3.Data.Entities.Hotel.Invoices;

public class Fee
{
    public long Id { get; set; }
    public DateTime CreatedAt { get; set; }
    public double Cash { get; set; }

    public required FeeType Type { get; set; }
    public required Client Client { get; set; }
}