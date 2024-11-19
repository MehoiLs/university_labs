using Newtonsoft.Json;

namespace Lab3.Model.View;

public class ClientViewModel
{
    public long Id { get; set; }
    public string FullName { get; set; }
    public string Passport { get; set; }
    
    [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
    public KeyCardViewModel? KeyCard { get; set; }
    [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
    public HotelViewModel? Hotel { get; set; }
}