using Lab3.Entity.Hotel.People;
using Lab3.Exception;
using Lab3.Model.Create;
using Lab3.Model.Update;
using Lab3.Model.View;
using Lab3.Service;
using Microsoft.AspNetCore.Mvc;

namespace Lab3.Controller;

[ApiController]
[Route("/api/clients")]
public class ClientController(IClientService clientService) : ControllerBase
{
    [HttpGet("{id:long}")]
    public ActionResult<ClientViewModel> GetClientById(long id)
    {
        var client = clientService.GetById(id);
        return Ok(client);
    }

    [HttpGet]
    public ActionResult<ClientViewModel> GetAllClients()
    {
        return Ok(clientService.GetAll());
    }
    
    [HttpPost]
    public ActionResult<ClientViewModel> CreateClient([FromBody] ClientCreateModel model)
    {
        var created = clientService.Create(model);
        return Ok(created);
    }

    [HttpPut]
    public ActionResult<ClientViewModel> UpdateClient([FromBody] ClientUpdateModel model)
    {
        var updated = clientService.Update(model);
        return Ok(updated);
    }

    [HttpDelete("{id:long}")]
    public NoContentResult DeleteClient(long id)
    {
        clientService.DeleteById(id);
        return NoContent();
    }
}