namespace Lab3.Entity.Hotel.Rooms;

public class RoomFeature
{
    public long Id { get; set; }
    public string Name { get; set; }
    public string? Description { get; set; }

    public ICollection<RoomProperties> Properties { get; set; } = new List<RoomProperties>();
}