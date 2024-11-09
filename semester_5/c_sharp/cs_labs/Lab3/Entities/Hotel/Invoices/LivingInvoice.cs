using Lab3.Entities.Hotel.Stays;

namespace Lab3.Entities.Hotel.Invoices;

public class LivingInvoice : Invoice
{
    public Staying Staying { get; set; }
}