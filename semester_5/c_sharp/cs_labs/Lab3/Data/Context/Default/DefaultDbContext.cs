using Microsoft.EntityFrameworkCore;

namespace Lab3.Data.Context.Default;

public class DefaultDbContext<T>(DbContextOptions<T> options) : DbContext(options)
    where T : DbContext
{
    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
    {
        if (!optionsBuilder.IsConfigured)
        {
            optionsBuilder.UseNpgsql("Host=localhost;Database=vsu;Username=postgres;Password=postgres");
        }
    }
}