namespace Lab3.Entity.Hotel.Rooms;

public class RoomPriceRate
{
    public long Id { get; set; }
    public int PricePerNight { get; set; }
    public DateTime StartDate { get; set; }

    //todo: must be a unique constraint
    public required RoomProperties Properties { get; set; }
}