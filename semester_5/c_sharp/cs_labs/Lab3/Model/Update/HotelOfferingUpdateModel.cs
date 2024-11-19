namespace Lab3.Model.Update;

public class HotelOfferingUpdateModel
{
    public required long Id { get; set; }
    public string Name { get; set; }
    public string Description { get; set; }
    public double AveragePrice { get; set; }
}