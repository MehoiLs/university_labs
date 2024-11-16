using Lab3.Entity.Hotel;
using Microsoft.EntityFrameworkCore;

namespace Lab3.Context;

public static class DbContextExtensions
{
    public static void ConfigureDependentEntities(this ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<Hotel>()
            .Navigation(h => h.Owner)
            .AutoInclude();
        
        // todo: add other
    }
}