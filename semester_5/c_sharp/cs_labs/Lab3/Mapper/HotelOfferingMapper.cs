using Lab3.Entity.Hotel;
using Lab3.Model.Create;
using Lab3.Model.Update;
using Lab3.Model.View;

namespace Lab3.Mapper;

public static class HotelOfferingMapper
{

    public static HotelOffering ToEntity(HotelOfferingCreateModel model)
    {
        return new HotelOffering
        {
            Name = model.Name,
            Description = model.Description,
            AveragePrice = model.AveragePrice
        };
    }

    public static HotelOffering ToEntity(HotelOfferingUpdateModel model)
    {
        return new HotelOffering
        {
            Name = model.Name,
            Description = model.Description,
            AveragePrice = model.AveragePrice
        };
    }
    
    public static HotelOfferingViewModel ToModel(HotelOffering entity)
    {
        return new HotelOfferingViewModel
        {
            Id = entity.Id,
            Name = entity.Name,
            Description = entity.Description,
            AveragePrice = entity.AveragePrice,
            Hotels = entity.Hotels?.Select(HotelMapper.ToPartialModel).ToList()
        };
    }

    public static HotelOfferingViewModel ToPartialModel(HotelOffering entity)
    {
        return new HotelOfferingViewModel
        {
            Id = entity.Id,
            Name = entity.Name,
            Description = entity.Description,
            AveragePrice = entity.AveragePrice
        };
    }
    
}