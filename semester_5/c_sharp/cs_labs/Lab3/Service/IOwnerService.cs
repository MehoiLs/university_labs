using Lab3.Entity.Hotel.People;

namespace Lab3.Service;

public interface IOwnerService
{
    public Owner Create(Owner owner);
    public Owner Update(Owner owner);
    public void DeleteById(long id);
    public Owner GetById(long id);
    public List<Owner> GetAll();
}