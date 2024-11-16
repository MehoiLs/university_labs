using Lab3.Entities.Hotel;

namespace Lab3.Service;

public interface IHotelService
{
    public Hotel Create(Hotel hotel);
    public Hotel GetById(long id);
}