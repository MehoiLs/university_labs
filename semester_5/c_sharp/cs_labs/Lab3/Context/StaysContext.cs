using Lab3.Context.Default;
using Lab3.Entities.Hotel.Stays;
using Microsoft.EntityFrameworkCore;

namespace Lab3.Context;

public class StaysContext : DefaultDbContext
{
    public DbSet<Staying> Stayings { get; set; }
    public DbSet<Booking> Bookings { get; set; }
}