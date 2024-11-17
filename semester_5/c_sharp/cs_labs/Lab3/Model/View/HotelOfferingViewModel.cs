using Lab3.Entity.Hotel;
using Newtonsoft.Json;

namespace Lab3.Model.View;

public class HotelOfferingViewModel
{
    public long Id { get; set; }
    public string Name { get; set; }
    public string Description { get; set; }
    public double AveragePrice { get; set; }
    
    [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
    public ICollection<HotelViewModel>? Hotels { get; set; }
}