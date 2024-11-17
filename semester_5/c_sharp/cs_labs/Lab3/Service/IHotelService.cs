using Lab3.Entity.Hotel;

namespace Lab3.Service;

public interface IHotelService
{
    public Hotel Create(Hotel hotel);
    public Hotel Update(Hotel hotel);
    public void DeleteById(long id);
    public Hotel GetById(long id);
    public List<Hotel> GetAll();
}