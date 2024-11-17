using Lab3.Entity.Hotel;
using Lab3.Exception;
using Lab3.Model.Create;
using Lab3.Model.Update;
using Lab3.Service;
using Microsoft.AspNetCore.Mvc;

namespace Lab3.Controller;

[ApiController]
[Route("/api/hotels")]
public class HotelController(IHotelService hotelService) : ControllerBase
{
    [HttpGet("{id:long}")]
    public ActionResult<Hotel> GetHotelById(long id)
    {
        var hotel = hotelService.GetById(id);
        return Ok(hotel);
    }

    [HttpGet]
    public ActionResult<Hotel> GetAllHotels()
    {
        return Ok(hotelService.GetAll());
    }
    
    [HttpPost]
    public ActionResult<Hotel> CreateHotel([FromBody] HotelCreateModel model)
    {
        if (!ModelState.IsValid)
        {
            return BadRequest(ModelState);
        }
        var created = hotelService.Create(model);
        return Ok(created);
    }

    [HttpPut]
    public ActionResult<Hotel> UpdateHotel([FromBody] HotelUpdateModel model)
    {
        if (!ModelState.IsValid)
        {
            return BadRequest(ModelState);
        }
        var updated = hotelService.Update(model);
        return Ok(updated);
    }

    [HttpDelete("/{id:long}")]
    public NoContentResult DeleteHotel(long id)
    {
        hotelService.DeleteById(id);
        return NoContent();
    }
}