using Lab3.Data.Entities.Hotel.Rooms;

namespace Lab3.Entities.Hotel.Rooms;

public class Room
{
    public long Id { get; set; }
    public int Floor { get; set; }
    public long RoomNumber { get; set; }

    public RoomProperties Properties { get; set; }
}