using Lab3.Entities.Enums;

namespace Lab3.Entities.Hotel.Rooms;

public class RoomProperties
{
    public long Id { get; set; }

    // room properties may vary in different hotels
    //todo: unique constraint in db
    public required Hotel Hotel { get; set; }
    public RoomClass Class { get; set; }
    public RoomSize Size { get; set; }
    
    public List<RoomFeature> Features { get; set; }
}