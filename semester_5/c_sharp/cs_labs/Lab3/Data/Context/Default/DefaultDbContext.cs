using Microsoft.EntityFrameworkCore;

namespace Lab3.Data.Context.Default;

public class DefaultDbContext : DbContext
{
    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        if (!optionsBuilder.IsConfigured)
            optionsBuilder.UseNpgsql("Host=localhost;Database=vsu;Username=postgres;Password=postgres");
    }
}