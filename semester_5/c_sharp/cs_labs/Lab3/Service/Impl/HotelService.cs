using Lab3.Entity.Hotel;
using Lab3.Model.Create;
using Lab3.Model.Update;
using Lab3.Repository;
using Microsoft.EntityFrameworkCore;

namespace Lab3.Service.Impl;

public class HotelService(IGeneralRepository<Hotel> hotelRepository) : IHotelService
{
    public Hotel Create(HotelCreateModel model)
    {
        var hotel = new Hotel
        {
            Name = model.Name,
            Address = model.Address,
            Email = model.Email,
            Phone = model.Phone,
            YearOpenedIn = model.YearOpenedIn,
            Area = model.Area,
            OwnerId = model.OwnerId
        };
        hotelRepository.Create(hotel);
        return GetById(hotel.Id);
    }

    public Hotel Update(HotelUpdateModel model)
    {
        var hotel = new Hotel
        {
            Name = model.Name,
            Address = model.Address,
            Email = model.Email,
            Phone = model.Phone,
            Area = model.Area,
            OwnerId = model.OwnerId
        };
        hotelRepository.Update(hotel);
        return GetById(hotel.Id);
    }

    public void DeleteById(long id)
    {
        hotelRepository.DeleteById(id);
    }

    public Hotel GetById(long id)
    {
        return hotelRepository.GetEntitySet()
            .Include(h => h.Owner)
            .Include(h => h.Services)
            .FirstOrThrow(h => h.Id == id);
    }

    public List<Hotel> GetAll()
    {
        return [..hotelRepository.GetAll()];
    }
}