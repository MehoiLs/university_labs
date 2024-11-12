using Lab3.Data.Entities.Hotel.Stays;

namespace Lab3.Data.Entities.Hotel.Invoices;

public class LivingInvoice : Invoice
{
    public Staying Staying { get; set; }
}