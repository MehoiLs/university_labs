using System.ComponentModel.DataAnnotations;
using Lab3.Model.View;
using Newtonsoft.Json;

namespace Lab3.Model.Create;

public class ClientCreateModel
{
    [MaxLength(100)] 
    public required string FullName { get; set; }
    [MaxLength(10)] 
    public required string Passport { get; set; }
    
    [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
    public KeyCardViewModel? KeyCard { get; set; }
    
    [JsonProperty(NullValueHandling = NullValueHandling.Ignore)]
    public HotelViewModel? Hotel { get; set; }
}