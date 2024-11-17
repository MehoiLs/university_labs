using Lab3.Entity.Hotel;
using Lab3.Repository;
using Microsoft.EntityFrameworkCore;

namespace Lab3.Service.Impl;

public class HotelService(IGeneralRepository<Hotel> hotelRepository) : IHotelService
{
    public Hotel Create(Hotel hotel)
    {
        hotelRepository.Create(hotel);
        return GetById(hotel.Id);
    }

    public Hotel Update(Hotel hotel)
    {
        hotelRepository.Update(hotel);
        return GetById(hotel.Id);
    }

    public void DeleteById(long id)
    {
        hotelRepository.DeleteById(id);
    }

    public Hotel GetById(long id)
    {
        //todo      + use viewModels       
        return hotelRepository.GetEntitySet()
            .Include(h => h.Owner)
            .Include(h => h.Services)
            .First(h => h.Id == id);
    }

    public List<Hotel> GetAll()
    {
        return [..hotelRepository.GetAll()];
    }
}