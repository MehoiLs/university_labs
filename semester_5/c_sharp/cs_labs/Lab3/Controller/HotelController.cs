using Lab3.Entity.Hotel;
using Lab3.Exception;
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
        // TODO: something like controller advice?
        try
        {
            var hotel = hotelService.GetById(id);
            return Ok(hotel);
        }
        catch (NotFoundException e)
        {
            return NotFound(e.Message);
        }
    }

    [HttpGet]
    public ActionResult<Hotel> GetAllHotels()
    {
        return Ok(hotelService.GetAll());
    }

    // TODO: viewModel?
    [HttpPost]
    public ActionResult<Hotel> CreateHotel([FromBody] Hotel hotel)
    {
        var created = hotelService.Create(hotel);
        return Ok(created);
    }

    [HttpPut]
    public ActionResult<Hotel> UpdateHotel([FromBody] Hotel hotel)
    {
        try
        {
            var updated = hotelService.Update(hotel);
            return Ok(updated);
        }
        catch (NotFoundException e)
        {
            return NotFound(e.Message);
        }
    }

    [HttpDelete("/{id:long}")]
    public NoContentResult DeleteHotel(long id)
    {
        hotelService.DeleteById(id);
        return NoContent();
    }
}