using Lab3.Entity.Hotel.People;
using Lab3.Exception;
using Lab3.Service;
using Microsoft.AspNetCore.Mvc;

namespace Lab3.Controller;

[ApiController]
[Route("/api/owners")]
public class OwnerController(IOwnerService ownerService) : ControllerBase
{
    [HttpGet("{id:long}")]
    public ActionResult<Owner> GetOwnerById(long id)
    {
        var owner = ownerService.GetById(id);
        return Ok(owner);
    }

    [HttpGet]
    public ActionResult<Owner> GetAllOwners()
    {
        return Ok(ownerService.GetAll());
    }

    // TODO: viewModel?
    [HttpPost]
    public ActionResult<Owner> CreateOwner([FromBody] Owner owner)
    {
        var created = ownerService.Create(owner);
        return Ok(created);
    }

    [HttpPut]
    public ActionResult<Owner> UpdateOwner([FromBody] Owner owner)
    {
        var updated = ownerService.Update(owner);
        return Ok(updated);
    }

    [HttpDelete("{id:long}")]
    public NoContentResult DeleteOwner(long id)
    {
        ownerService.DeleteById(id);
        return NoContent();
    }
}