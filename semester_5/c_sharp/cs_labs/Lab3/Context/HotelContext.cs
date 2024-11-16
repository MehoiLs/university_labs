using Lab3.Context.Default;
using Lab3.Entities.Hotel;
using Microsoft.EntityFrameworkCore;

namespace Lab3.Context;

public class HotelContext : DefaultDbContext
{
    public DbSet<Hotel> Hotels { get; set; }
    public DbSet<Entities.Hotel.Service> Services { get; set; }

}