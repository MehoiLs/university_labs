using Lab3.Entity.Hotel;
using Lab3.Entity.Hotel.People;

namespace Lab3.Service;

public interface IHotelService
{
    public Hotel Create(Hotel hotel);
    public Hotel GetById(long id);
    public List<Hotel> GetAll();


    public Owner CreateOwner(Owner owner);
    public Owner GetOwnerById(long id);
}