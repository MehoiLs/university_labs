using Lab3.Data.Entities.Hotel;
using Lab3.Data.Exception;
using Lab3.Data.Service;
using Microsoft.AspNetCore.Mvc;

namespace Lab3.Data.Controller;

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

    // TODO: viewModel?
    [HttpPost]
    public ActionResult<Hotel> CreateHotel([FromBody] Hotel hotel)
    {
        var created = hotelService.Create(hotel);
        return Ok(created);
    }
}