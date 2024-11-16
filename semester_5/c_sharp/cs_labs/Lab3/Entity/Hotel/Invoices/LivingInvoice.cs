using Lab3.Entity.Hotel.Stays;

namespace Lab3.Entity.Hotel.Invoices;

public class LivingInvoice : Invoice
{
    public Staying Staying { get; set; }
}