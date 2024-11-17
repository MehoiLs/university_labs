using Lab3.Entity.Hotel;
using Lab3.Entity.Hotel.People;
using Lab3.Repository;

namespace Lab3.Service.Impl;

public class HotelService(
    IGeneralRepository<Hotel> hotelRepository,
    IGeneralRepository<Owner> ownerRepository
) : IHotelService
{
    public Hotel Create(Hotel hotel)
    {
        return hotelRepository.Create(hotel);
    }

    public Hotel GetById(long id)
    {
        //todo      + use viewModels       
        return hotelRepository.GetById(id);
    }

    public List<Hotel> GetAll()
    {
        return [..hotelRepository.GetAll()];
    }


    public Owner CreateOwner(Owner owner)
    {
        return ownerRepository.Create(owner);
    }

    public Owner GetOwnerById(long id)
    {
        return ownerRepository.GetById(id);
    }
}