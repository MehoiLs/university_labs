using Lab3.Data.Context.Default;
using Lab3.Data.Entities.Hotel;
using Microsoft.EntityFrameworkCore;

namespace Lab3.Data.Context;

public class HotelContext(DbContextOptions<HotelContext> options) : DefaultDbContext<HotelContext>(options)
{
    public DbSet<Hotel> Hotels { get; set; }
    public DbSet<Service> Services { get; set; }
}