using Lab3.Entity.Hotel.People;
using Lab3.Model.Create;
using Lab3.Model.Update;
using Lab3.Model.View;

namespace Lab3.Mapper;

public static class OwnerMapper
{

    public static Owner ToEntity(OwnerCreateModel model)
    {
        return new Owner
        {
            FullName = model.FullName
        };
    }
    
    public static Owner ToEntity(OwnerUpdateModel model)
    {
        return new Owner
        {
            FullName = model.FullName
        };
    }
    
    public static OwnerViewModel ToModel(Owner entity)
    {
        return new OwnerViewModel
        {
            Id = entity.Id,
            FullName = entity.FullName,
            Hotels = entity.Hotels.Select(HotelMapper.ToPartialModel).ToList()
        };
    }

    public static OwnerViewModel ToPartialModel(Owner entity)
    {
        return new OwnerViewModel
        {
            Id = entity.Id,
            FullName = entity.FullName
        };
    }
    
}