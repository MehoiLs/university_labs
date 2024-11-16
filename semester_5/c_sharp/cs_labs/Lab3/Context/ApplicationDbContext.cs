using Lab3.Entity.Hotel;
using Lab3.Entity.Hotel.Invoices;
using Lab3.Entity.Hotel.People;
using Lab3.Entity.Hotel.Rooms;
using Lab3.Entity.Hotel.Stays;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Internal;

namespace Lab3.Context;

public class ApplicationDbContext : DbContext
{
    public DbSet<Hotel> Hotels { get; set; }
    public DbSet<Entity.Hotel.Service> Services { get; set; }

    public DbSet<Room> Rooms { get; set; }
    public DbSet<RoomFeature> RoomFeatures { get; set; }
    public DbSet<RoomPriceRate> RoomPriceRates { get; set; }
    public DbSet<RoomProperties> RoomProperties { get; set; }

    public DbSet<Staying> Stayings { get; set; }
    public DbSet<Booking> Bookings { get; set; }

    public DbSet<Client> Clients { get; set; }
    public DbSet<Employee> Employees { get; set; }
    public DbSet<Occupation> Occupations { get; set; }
    public DbSet<Owner> Owners { get; set; }

    public DbSet<Fee> Fees { get; set; }
    public DbSet<Invoice> Invoices { get; set; }
    public DbSet<LivingInvoice> LivingInvoices { get; set; }
    public DbSet<ServiceInvoice> ServiceInvoices { get; set; }
    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        if (!optionsBuilder.IsConfigured)
            optionsBuilder.UseNpgsql("Host=localhost;Database=vsu;Username=postgres;Password=postgres");
    }
}