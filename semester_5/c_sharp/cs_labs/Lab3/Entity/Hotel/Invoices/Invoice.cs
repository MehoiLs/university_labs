using Lab3.Entity.Enums;
using Lab3.Entity.Hotel.People;

namespace Lab3.Entity.Hotel.Invoices;

public abstract class Invoice
{
    public long Id { get; set; }
    public DateTime CreatedAt { get; set; }
    public double Cash { get; set; }

    public required InvoiceType Type { get; set; }
    public required Client Client { get; set; }
}