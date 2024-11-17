using Lab3.Entity.Hotel.Invoices;

namespace Lab3.Entity.Hotel;

public class Service
{
    public long Id { get; set; }
    public string Name { get; set; }
    public string Description { get; set; }
    public double AveragePrice { get; set; }

    public ICollection<ServiceInvoice>? Invoices { get; set; }
    public ICollection<Hotel>? Hotels { get; set; }
}