using System.Data.Entity;
using Lab3.Entity.Hotel.People;
using Lab3.Repository;

namespace Lab3.Service.Impl;

public class OwnerService(IGeneralRepository<Owner> repository) : IOwnerService
{
    public Owner Create(Owner owner)
    {
        repository.Create(owner);
        return GetById(owner.Id);
    }

    public Owner Update(Owner owner)
    {
        repository.Update(owner);
        return GetById(owner.Id);
    }

    public void DeleteById(long id)
    {
        repository.DeleteById(id);
    }

    public Owner GetById(long id)
    {
        return repository.GetEntitySet()
            .Include(o => o.Hotels)
            .First(o => o.Id == id);
    }

    public List<Owner> GetAll()
    {
        return [..repository.GetAll()];
    }
}