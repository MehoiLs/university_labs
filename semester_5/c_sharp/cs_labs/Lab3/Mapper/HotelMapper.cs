using Lab3.Entity.Hotel;
using Lab3.Model.Create;
using Lab3.Model.Update;
using Lab3.Model.View;

namespace Lab3.Mapper;

public static class HotelMapper
{

    public static Hotel ToEntity(HotelCreateModel model)
    {
        return new Hotel
        {
            Name = model.Name,
            Address = model.Address,
            Email = model.Email,
            Phone = model.Phone,
            YearOpenedIn = DateTime.SpecifyKind(model.YearOpenedIn, DateTimeKind.Utc),
            Area = model.Area,
            OwnerId = model.OwnerId
        };
    }
    
    public static Hotel ToEntity(HotelUpdateModel model)
    {
        return new Hotel
        {
            Name = model.Name,
            Address = model.Address,
            Email = model.Email,
            Phone = model.Phone,
            Area = model.Area,
            OwnerId = model.OwnerId
        };
    }

    public static HotelViewModel ToModel(Hotel entity)
    {
        return new HotelViewModel
        {
            Id = entity.Id,
            Name = entity.Name,
            Address = entity.Address,
            Email = entity.Email,
            Phone = entity.Phone,
            YearOpenedIn = entity.YearOpenedIn,
            Area = entity.Area,
            Owner = OwnerMapper.ToPartialModel(entity.Owner),
            Offerings = entity.Offerings?.Select(HotelOfferingMapper.ToPartialModel).ToList()
        };
    }

    public static HotelViewModel ToPartialModel(Hotel entity)
    {
        return new HotelViewModel
        {
            Id = entity.Id,
            Name = entity.Name,
            Address = entity.Address,
            Email = entity.Email,
            Phone = entity.Phone,
            YearOpenedIn = entity.YearOpenedIn,
            Area = entity.Area
        };
    }
    
}