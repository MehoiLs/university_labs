using Lab3.Entity.Enums;

namespace Lab3.Entity.Hotel.Rooms;

public class RoomProperties
{
    public long Id { get; set; }

    public RoomClass Class { get; set; }
    public RoomSize Size { get; set; }

    public Hotel Hotel { get; set; }
    public ICollection<RoomFeature> Features { get; set; } = new List<RoomFeature>();
}