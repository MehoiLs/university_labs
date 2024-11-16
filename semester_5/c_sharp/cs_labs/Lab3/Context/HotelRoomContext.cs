using Lab3.Context.Default;
using Lab3.Entities.Hotel.Rooms;
using Microsoft.EntityFrameworkCore;

namespace Lab3.Context;

public class HotelRoomContext : DefaultDbContext
{
    public DbSet<Room> Rooms { get; set; }
    public DbSet<RoomFeature> RoomFeatures { get; set; }
    public DbSet<RoomPriceRate> RoomPriceRates { get; set; }
    public DbSet<RoomProperties> RoomProperties { get; set; }
}