using Lab3.Entity.Hotel;
using Lab3.Entity.Hotel.Invoices;
using Lab3.Entity.Hotel.People;
using Lab3.Entity.Hotel.Rooms;
using Lab3.Entity.Hotel.Stays;
using Lab3.Extensions;
using Microsoft.EntityFrameworkCore;

namespace Lab3.Context;

public class ApplicationDbContext : DbContext
{
    private const string DbConnection = "Host=localhost;Database=vsu;Username=postgres;Password=postgres";

    public DbSet<Hotel> Hotels { get; init; }
    public DbSet<HotelOffering> Services { get; init; }
    
    public DbSet<HotelKeyCard> KeyCards { get; init; }

    public DbSet<Room> Rooms { get; init; }
    public DbSet<RoomFeature> RoomFeatures { get; init; }
    public DbSet<RoomPriceRate> RoomPriceRates { get; init; }
    public DbSet<RoomProperties> RoomProperties { get; init; }

    public DbSet<Staying> Stayings { get; init; }
    public DbSet<Booking> Bookings { get; init; }

    public DbSet<Client> Clients { get; init; }
    public DbSet<Employee> Employees { get; init; }
    public DbSet<Occupation> Occupations { get; init; }
    public DbSet<Owner> Owners { get; init; }

    public DbSet<Fee> Fees { get; init; }
    public DbSet<Invoice> Invoices { get; init; }
    public DbSet<LivingInvoice> LivingInvoices { get; init; }
    public DbSet<ServiceInvoice> ServiceInvoices { get; init; }

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        optionsBuilder.UseNpgsql(DbConnection);
    }
}