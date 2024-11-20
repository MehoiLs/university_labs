using Lab3.Entity.Hotel.People;
using Lab3.Exception;
using Lab3.Model.Create;
using Lab3.Model.Update;
using Lab3.Model.View;
using Lab3.Service;
using Microsoft.AspNetCore.Mvc;

namespace Lab3.Controller;

[ApiController]
[Route("/api/owners")]
public class OwnerController(IOwnerService ownerService) : ControllerBase
{
    [HttpGet("{id:long}")]
    public ActionResult<OwnerViewModel> GetOwnerById(long id)
    {
        var owner = ownerService.GetById(id);
        return Ok(owner);
    }

    [HttpGet]
    public ActionResult<OwnerViewModel> GetAllOwners()
    {
        return Ok(ownerService.GetAll());
    }
    
    [HttpPost]
    public ActionResult<OwnerViewModel> CreateOwner([FromBody] OwnerCreateModel model)
    {
        var created = ownerService.Create(model);
        return Ok(created);
    }

    [HttpPut]
    public ActionResult<OwnerViewModel> UpdateOwner([FromBody] OwnerUpdateModel model)
    {
        var updated = ownerService.Update(model);
        return Ok(updated);
    }

    [HttpDelete("{id:long}")]
    public NoContentResult DeleteOwner(long id)
    {
        ownerService.DeleteById(id);
        return NoContent();
    }
}