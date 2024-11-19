using Lab3.Entity.Hotel;
using Lab3.Model.Create;
using Lab3.Model.Update;
using Lab3.Model.View;

namespace Lab3.Service;

public interface IHotelService
{
    public KeyCardViewModel IssueKeyCard(long hotelId);
    public void AssignKeyCard(KeyCardAssignModel model);
    
    public HotelViewModel Create(HotelCreateModel model);
    public HotelViewModel Update(HotelUpdateModel model);
    public void DeleteById(long id);
    public HotelViewModel GetById(long id);
    public List<HotelViewModel> GetAll();
}