namespace Lab3.Entity.Hotel.Invoices;

public class ServiceInvoice : Invoice
{
    public ICollection<Service> Services { get; set; } = new List<Service>();
}