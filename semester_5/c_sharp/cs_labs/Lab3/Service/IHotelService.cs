using Lab3.Entity.Hotel;
using Lab3.Model.Create;
using Lab3.Model.Update;

namespace Lab3.Service;

public interface IHotelService
{
    public Hotel Create(HotelCreateModel model);
    public Hotel Update(HotelUpdateModel model);
    public void DeleteById(long id);
    public Hotel GetById(long id);
    public List<Hotel> GetAll();
}