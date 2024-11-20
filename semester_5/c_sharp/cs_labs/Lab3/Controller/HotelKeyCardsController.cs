using Lab3.Entity.Hotel;
using Lab3.Exception;
using Lab3.Model.Create;
using Lab3.Model.Update;
using Lab3.Model.View;
using Lab3.Service;
using Microsoft.AspNetCore.Mvc;

namespace Lab3.Controller;

[ApiController]
[Route("/api/hotels")]
public class HotelKeyCardsController(IHotelService hotelService) : ControllerBase
{
    [HttpGet("{hotelId:long}/keycards")]
    public ActionResult<List<KeyCardViewModel>> GetAllKeyCards(long hotelId)
    {
        var keyCards = hotelService.GetAllKeyCards(hotelId);
        return Ok(keyCards);
    }

    [HttpPost("{hotelId:long}/keycards")]
    public ActionResult<KeyCardViewModel> IssueKeyCard(long hotelId)
    {
        var keyCard = hotelService.IssueKeyCard(hotelId);
        return Ok(keyCard);
    }
    
    [HttpGet("keycards/{id:long}")]
    public ActionResult<List<KeyCardViewModel>> GetKeyCardById(long id)
    {
        var keyCards = hotelService.GetKeyCardById(id);
        return Ok(keyCards);
    }
    
    [HttpPatch("keycards/{id:long}/assign")]
    public NoContentResult AssignKeyCard(long id, [FromBody] KeyCardAssignModel model)
    {
        hotelService.AssignKeyCard(id, model);
        return NoContent();
    }
    
    [HttpPatch("keycards/{id:long}/de-assign")]
    public NoContentResult DeAssignKeyCard(long id)
    {
        hotelService.DeAssignKeyCard(id);
        return NoContent();
    }
    
    [HttpDelete("keycards/{id:long}")]
    public NoContentResult DeleteKeyCard(long id)
    {
        hotelService.DeleteById(id);
        return NoContent();
    }
    
}