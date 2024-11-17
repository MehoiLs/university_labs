using Lab3.Entity.Hotel;
using Lab3.Model.Create;
using Lab3.Model.Update;
using Lab3.Model.View;

namespace Lab3.Service;

public interface IHotelOfferingService
{
    public HotelOfferingViewModel Create(HotelOfferingCreateModel model);
    public HotelOfferingViewModel Update(HotelOfferingUpdateModel model);
    public void DeleteById(long id);
    public HotelOfferingViewModel GetById(long id);
    public List<HotelOfferingViewModel> GetAll();
}