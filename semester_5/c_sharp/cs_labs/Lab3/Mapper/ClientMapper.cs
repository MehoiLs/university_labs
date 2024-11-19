using Lab3.Entity.Hotel.People;
using Lab3.Model.Create;
using Lab3.Model.Update;
using Lab3.Model.View;

namespace Lab3.Mapper;

public static class ClientMapper
{

    public static Client ToEntity(ClientCreateModel model)
    {
        return new Client
        {
            FullName = model.FullName
        };
    }
    
    public static Client ToEntity(ClientUpdateModel model)
    {
        return new Client
        {
            Id = model.Id,
            FullName = model.FullName,
            Passport = model.Passport
        };
    }
    
    public static ClientViewModel ToModel(Client entity)
    {
        return new ClientViewModel
        {
            Id = entity.Id,
            FullName = entity.FullName,
            Passport = entity.Passport,
            Hotel = HotelMapper.ToPartialModel(entity.Hotel),
            KeyCard = KeyCardMapper.ToPartialModel(entity.KeyCard)
        };
    }

    public static ClientViewModel ToPartialModel(Client entity)
    {
        return new ClientViewModel
        {
            Id = entity.Id,
            FullName = entity.FullName,
            Passport = entity.Passport
        };
    }
    
}