using Microsoft.EntityFrameworkCore;
using Lab3.Entity.Hotel.People;
using Lab3.Extensions;
using Lab3.Mapper;
using Lab3.Model.Create;
using Lab3.Model.Update;
using Lab3.Model.View;
using Lab3.Repository;

namespace Lab3.Service.Impl;

public class ClientService(IGeneralRepository<Client> repository) : IClientService
{
    public ClientViewModel Create(ClientCreateModel model)
    {
        var client = ClientMapper.ToEntity(model);
        repository.Create(client);
        return GetById(client.Id);
    }

    public ClientViewModel Update(ClientUpdateModel model)
    {
        var client = ClientMapper.ToEntity(model);
        repository.Update(client);
        return GetById(client.Id);
    }

    public void DeleteById(long id)
    {
        repository.DeleteById(id);
    }

    public ClientViewModel GetById(long id)
    {
        var client = repository.GetEntitySet()
            .Include(c => c.Hotel)
            .Include(c => c.KeyCard)
            .FirstOrThrow(c => c.Id == id);
        return ClientMapper.ToModel(client);
    }

    public List<ClientViewModel> GetAll()
    {
        return [..repository.GetAll().Select(ClientMapper.ToPartialModel)];
    }
}