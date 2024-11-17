using Lab3.Entity.Hotel;
using Lab3.Model.Create;
using Lab3.Model.Update;
using Lab3.Model.View;

namespace Lab3.Service;

public interface IHotelService
{
    public HotelViewModel Create(HotelCreateModel model);
    public HotelViewModel Update(HotelUpdateModel model);
    public void DeleteById(long id);
    public HotelViewModel GetById(long id);
    public List<HotelViewModel> GetAll();
}