using Newtonsoft.Json;

namespace Lab3.Model.View;

public class HotelViewModel
{
    public long Id { get; set; }
    public string Name { get; set; }
    public string Address { get; set; }
    public string Email { get; set; }
    public string Phone { get; set; }
    public DateTime YearOpenedIn { get; set; }
    public double Area { get; set; }

    [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
    public OwnerViewModel? Owner { get; set; }
    
    [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
    public List<HotelOfferingViewModel>? Offerings { get; set; }
}