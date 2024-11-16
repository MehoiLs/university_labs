using Lab3.Data.Context.Default;
using Lab3.Data.Entities.Hotel.Invoices;
using Microsoft.EntityFrameworkCore;

namespace Lab3.Data.Context;

public class InvoicesContext : DefaultDbContext
{
    public DbSet<Fee> Fees { get; set; }
    public DbSet<Invoice> Invoices { get; set; }
    public DbSet<LivingInvoice> LivingInvoices { get; set; }
    public DbSet<ServiceInvoice> ServiceInvoices { get; set; }
}