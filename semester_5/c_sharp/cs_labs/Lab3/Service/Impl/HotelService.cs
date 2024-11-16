using Lab3.Context;
using Lab3.Entities.Hotel;
using Lab3.Repository;

namespace Lab3.Service.Impl;

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