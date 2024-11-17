using System.Data.Entity;
using Lab3.Entity.Hotel.People;
using Lab3.Extensions;
using Lab3.Mapper;
using Lab3.Model.Create;
using Lab3.Model.Update;
using Lab3.Model.View;
using Lab3.Repository;

namespace Lab3.Service.Impl;

public class OwnerService(IGeneralRepository<Owner> repository) : IOwnerService
{
    public OwnerViewModel Create(OwnerCreateModel model)
    {
        var owner = OwnerMapper.ToEntity(model);
        repository.Create(owner);
        return GetById(owner.Id);
    }

    public OwnerViewModel Update(OwnerUpdateModel model)
    {
        var owner = OwnerMapper.ToEntity(model);
        repository.Update(owner);
        return GetById(owner.Id);
    }

    public void DeleteById(long id)
    {
        repository.DeleteById(id);
    }

    public OwnerViewModel GetById(long id)
    {
        var owner = repository.GetEntitySet()
            .Include(o => o.Hotels)
            .FirstOrThrow(o => o.Id == id);
        return OwnerMapper.ToModel(owner);
    }

    public List<OwnerViewModel> GetAll()
    {
        return [..repository.GetAll().Select(OwnerMapper.ToPartialModel)];
    }
}