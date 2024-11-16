using Lab3.Data.Entities.Hotel;

namespace Lab3.Data.Service;

public interface IHotelService
{
    public Hotel Create(Hotel hotel);
    public Hotel GetById(long id);
}