using Lab3.Entity.Hotel;
using Lab3.Entity.Hotel.People;
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


    [HttpGet("/api/owner/{id:long}")]
    public ActionResult<Owner> GetOwnerById(long id)
    {
        try
        {
            var owner = hotelService.GetOwnerById(id);
            return Ok(owner);
        }
        catch (NotFoundException e)
        {
            return NotFound(e.Message);
        }
    }

    [HttpPost("/api/owner")]
    public ActionResult<Owner> CreateOwner([FromBody] Owner owner)
    {
        var created = hotelService.CreateOwner(owner);
        return Ok(created);
    }
}