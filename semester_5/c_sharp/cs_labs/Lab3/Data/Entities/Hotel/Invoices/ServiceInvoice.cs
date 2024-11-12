namespace Lab3.Data.Entities.Hotel.Invoices;

public class ServiceInvoice : Invoice
{
    public List<Service> Services { get; set; }
}