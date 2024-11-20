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
public class HotelController(IHotelService hotelService) : ControllerBase
{
    [HttpGet("{id:long}")]
    public ActionResult<HotelViewModel> GetHotelById(long id)
    {
        var hotel = hotelService.GetById(id);
        return Ok(hotel);
    }

    [HttpGet]
    public ActionResult<HotelViewModel> GetAllHotels()
    {
        var hotels = hotelService.GetAll();
        return Ok(hotels);
    }
    
    [HttpPost]
    public ActionResult<HotelViewModel> CreateHotel([FromBody] HotelCreateModel model)
    {
        if (!ModelState.IsValid)
        {
            return BadRequest(ModelState);
        }
        var created = hotelService.Create(model);
        return Ok(created);
    }

    [HttpPut]
    public ActionResult<HotelViewModel> UpdateHotel([FromBody] HotelUpdateModel model)
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