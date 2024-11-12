using Lab3.Data.Context.Default;
using Lab3.Data.Entities.Hotel.Stays;
using Microsoft.EntityFrameworkCore;

namespace Lab3.Data.Context;

public class StaysContext(DbContextOptions<StaysContext> options) : DefaultDbContext<StaysContext>(options)
{
    public DbSet<Staying> Stayings { get; set; }
    public DbSet<Booking> Bookings { get; set; }
}