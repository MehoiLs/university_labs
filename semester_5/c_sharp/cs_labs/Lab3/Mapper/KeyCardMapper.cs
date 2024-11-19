using Lab3.Entity.Hotel;
using Lab3.Entity.Hotel.People;
using Lab3.Model.Create;
using Lab3.Model.Update;
using Lab3.Model.View;

namespace Lab3.Mapper;

public static class KeyCardMapper
{

    public static KeyCardViewModel ToModel(HotelKeyCard entity)
    {
        return new KeyCardViewModel
        {
            Id = entity.Id,
            LastAssignedAt = entity.LastAssignedAt,
            Client = entity.Client != null ? ClientMapper.ToPartialModel(entity.Client) : null
        };
    }

    public static KeyCardViewModel ToPartialModel(HotelKeyCard entity)
    {
        return new KeyCardViewModel
        {
            Id = entity.Id,
            LastAssignedAt = entity.LastAssignedAt
        };
    }
    
}