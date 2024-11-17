namespace Lab3.Entity.Hotel.Invoices;

public class ServiceInvoice : Invoice
{
    public ICollection<HotelOffering> Services { get; set; } = new List<HotelOffering>();
}