using Lab3.Entities.Enums;
using Lab3.Entities.Hotel.People;

namespace Lab3.Entities.Hotel.Invoices;

public abstract class Invoice
{
    public long Id { get; set; }
    public DateTime CreatedAt { get; set; }
    public double Cash { get; set; }

    public required InvoiceType Type { get; set; }
    public required Client Client { get; set; }
}