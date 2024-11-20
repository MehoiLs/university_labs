using Lab3.Entity.Hotel.People;
using Lab3.Model.Create;
using Lab3.Model.Update;
using Lab3.Model.View;

namespace Lab3.Service;

public interface IClientService
{
    public ClientViewModel Create(ClientCreateModel owner);
    public ClientViewModel Update(ClientUpdateModel owner);
    public void DeleteById(long id);
    public ClientViewModel GetById(long id);
    public List<ClientViewModel> GetAll();
}