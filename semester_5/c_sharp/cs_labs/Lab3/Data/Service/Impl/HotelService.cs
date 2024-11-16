using Lab3.Data.Context;
using Lab3.Data.Entities.Hotel;
using Lab3.Data.Repository;

namespace Lab3.Data.Service.Impl;

public class HotelService : IHotelService
{
    private readonly GeneralRepository<Hotel> _repository = new(new HotelContext());

    public Hotel Create(Hotel hotel)
    {
        return _repository.Create(hotel);
    }

    public Hotel GetById(long id)
    {
        return _repository.GetById(id);
    }
}