using Lab3.Entity.Hotel;
using Lab3.Entity.Hotel.People;
using Newtonsoft.Json;

namespace Lab3.Model.View;

public class KeyCardViewModel
{
    public long Id { get; set; }
    public DateTime LastAssignedAt { get; set; }
    
    [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
    public ClientViewModel? Client { get; set; }
    
    [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
    public HotelViewModel? Hotel { get; set; }
}