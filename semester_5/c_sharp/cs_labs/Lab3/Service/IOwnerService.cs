using Lab3.Entity.Hotel.People;
using Lab3.Model.Create;
using Lab3.Model.Update;
using Lab3.Model.View;

namespace Lab3.Service;

public interface IOwnerService
{
    public OwnerViewModel Create(OwnerCreateModel owner);
    public OwnerViewModel Update(OwnerUpdateModel owner);
    public void DeleteById(long id);
    public OwnerViewModel GetById(long id);
    public List<OwnerViewModel> GetAll();
}