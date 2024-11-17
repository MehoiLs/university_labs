using Newtonsoft.Json;

namespace Lab3.Model.View;

public class OwnerViewModel
{
    public long Id { get; set; }
    public required string FullName { get; set; }
    
    [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
    public List<HotelViewModel>? Hotels { get; set; }
}