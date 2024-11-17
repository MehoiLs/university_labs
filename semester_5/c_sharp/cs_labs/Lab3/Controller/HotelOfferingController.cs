using Lab3.Entity.Hotel;
using Lab3.Exception;
using Lab3.Model.Create;
using Lab3.Model.Update;
using Lab3.Service;
using Microsoft.AspNetCore.Mvc;

namespace Lab3.Controller;

[ApiController]
[Route("/api/hotels/offerings")]
public class HotelOfferingController(IHotelOfferingService offeringService) : ControllerBase
{
    [HttpGet("{id:long}")]
    public ActionResult<HotelOffering> GetOfferingById(long id)
    {
        var offering = offeringService.GetById(id);
        return Ok(offering);
    }

    [HttpGet]
    public ActionResult<HotelOffering> GetAllOfferings()
    {
        return Ok(offeringService.GetAll());
    }
    
    [HttpPost]
    public ActionResult<HotelOffering> CreateOffering([FromBody] HotelOfferingCreateModel model)
    {
        if (!ModelState.IsValid)
        {
            return BadRequest(ModelState);
        }
        var created = offeringService.Create(model);
        return Ok(created);
    }

    [HttpPut]
    public ActionResult<HotelOffering> UpdateOffering([FromBody] HotelOfferingUpdateModel model)
    {
        if (!ModelState.IsValid)
        {
            return BadRequest(ModelState);
        }
        var updated = offeringService.Update(model);
        return Ok(updated);
    }

    [HttpDelete("{id:long}")]
    public NoContentResult DeleteOffering(long id)
    {
        offeringService.DeleteById(id);
        return NoContent();
    }
}