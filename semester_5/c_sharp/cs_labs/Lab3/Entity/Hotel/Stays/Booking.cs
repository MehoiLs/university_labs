using Lab3.Entity.Enums;
using Lab3.Entity.Hotel.People;
using Lab3.Entity.Hotel.Rooms;

namespace Lab3.Entity.Hotel.Stays;

public class Booking
{
    public long Id { get; set; }
    public required Client Client { get; set; }

    public DateTime CheckingInAt { get; set; }
    public DateTime CheckingOutAt { get; set; }

    public List<RoomClass>? PreferredRoomClasses { get; set; }
    public List<RoomSize>? PreferredRoomSizes { get; set; }
    public List<RoomFeature>? PreferredRoomFeatures { get; set; }
}