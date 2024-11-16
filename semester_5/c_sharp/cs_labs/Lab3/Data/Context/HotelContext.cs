using Lab3.Data.Context.Default;
using Lab3.Data.Entities.Hotel;
using Microsoft.EntityFrameworkCore;

namespace Lab3.Data.Context;

public class HotelContext : DefaultDbContext
{
    public DbSet<Hotel> Hotels { get; set; }
    public DbSet<Entities.Hotel.Service> Services { get; set; }

}