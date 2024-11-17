using Lab3.Entity.Hotel;
using Lab3.Entity.Hotel.Invoices;
using Lab3.Entity.Hotel.People;
using Lab3.Entity.Hotel.Rooms;
using Lab3.Entity.Hotel.Stays;
using Microsoft.EntityFrameworkCore;

namespace Lab3.Context;

public static class DbContextExtensions
{
    public static void ConfigureDependentEntities(this ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<Hotel>()
            .Navigation(h => h.Owner)
            .AutoInclude();
        modelBuilder.Entity<Hotel>()
            .HasMany(h => h.Services)
            .WithMany(s => s.Hotels); // todo: might use 'usingEntity => HotelService` as composite PK entity

        modelBuilder.Entity<Fee>()
            .Navigation(f => f.Client)
            .AutoInclude();
        modelBuilder.Entity<Invoice>()
            .Navigation(i => i.Client)
            .AutoInclude();
        modelBuilder.Entity<LivingInvoice>()
            .Navigation(li => li.Staying)
            .AutoInclude();
        modelBuilder.Entity<ServiceInvoice>()
            .HasMany(si => si.Services)
            .WithMany(s => s.Invoices);

        modelBuilder.Entity<Client>()
            .Navigation(c => c.Hotel)
            .AutoInclude();
        modelBuilder.Entity<Employee>()
            .Navigation(e => e.Occupation)
            .AutoInclude();
        modelBuilder.Entity<Occupation>()
            .Navigation(o => o.Hotel)
            .AutoInclude();
        modelBuilder.Entity<Owner>()
            .HasMany(o => o.Hotels)
            .WithOne(h => h.Owner);

        modelBuilder.Entity<Room>()
            .Navigation(r =>
                r.Properties) // todo: try using one and check how it handles queries with a lot of entities
            .AutoInclude();
        modelBuilder.Entity<RoomProperties>()
            .HasMany(rp => rp.Features)
            .WithMany(rf => rf.Properties);
        modelBuilder.Entity<RoomPriceRate>()
            .Navigation(rpr => rpr.Properties)
            .AutoInclude();

        modelBuilder.Entity<Booking>()
            .HasMany(b => b.PreferredRoomFeatures);
        modelBuilder.Entity<Staying>()
            .Navigation(s => s.Client)
            .AutoInclude();
        modelBuilder.Entity<Staying>()
            .Navigation(r => r.Room)
            .AutoInclude();
    }
}