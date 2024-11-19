using Lab3.Entity.Hotel;
using Lab3.Entity.Hotel.People;
using Lab3.Exception;
using Lab3.Extensions;
using Lab3.Mapper;
using Lab3.Model.Create;
using Lab3.Model.Update;
using Lab3.Model.View;
using Lab3.Repository;
using Microsoft.EntityFrameworkCore;

namespace Lab3.Service.Impl;

public class HotelService(
    IGeneralRepository<Owner> ownerRepository,
    IGeneralRepository<Hotel> hotelRepository,
    IGeneralRepository<HotelOffering> offeringRepository,
    IGeneralRepository<HotelKeyCard> keyCardRepository
) : IHotelService
{
    public KeyCardViewModel IssueKeyCard(long hotelId)
    {
        var keyCard = new HotelKeyCard
        {
            HotelId = hotelId
        };
        keyCardRepository.Create(keyCard);
        return new KeyCardViewModel(); // TODO: keycard mapper to view model
    }

    public void AssignKeyCard(KeyCardAssignModel model)
    {
        throw new NotImplementedException();
    }
    
    // TODO: also implement client CRUD 

    public HotelViewModel Create(HotelCreateModel model)
    {
        if (!ownerRepository.ExistsById(model.OwnerId))
        {
            throw new NotFoundException("Owner not found");
        }

        var hotel = HotelMapper.ToEntity(model);
        HandleOfferings(hotel, model.OfferingIds);
        
        hotelRepository.Create(hotel);
        return GetById(hotel.Id);
    }

    public HotelViewModel Update(HotelUpdateModel model)
    {
        if (!ownerRepository.ExistsById(model.OwnerId))
        {
            throw new NotFoundException("Owner not found");
        }
        
        var hotel = HotelMapper.ToEntity(model);
        HandleOfferings(hotel, model.OfferingIds);
        
        hotelRepository.Update(hotel);
        return GetById(hotel.Id);
    }

    public void DeleteById(long id)
    {
        hotelRepository.DeleteById(id);
    }

    public HotelViewModel GetById(long id)
    {
        var hotel = hotelRepository.GetEntitySet()
            .Include(h => h.Owner)
            .Include(h => h.Offerings)
            .FirstOrThrow(h => h.Id == id);
        return HotelMapper.ToModel(hotel);
    }

    public List<HotelViewModel> GetAll()
    {
        return [..hotelRepository.GetAll().Select(HotelMapper.ToPartialModel)];
    }

    private void HandleOfferings(Hotel hotel, List<long>? offeringIds)
    {
        if (offeringIds == null) return;
        var offerings = offeringRepository.GetEntitySet()
            .Where(hs => offeringIds.Contains(hs.Id))
            .ToList();
        hotel.Offerings = offerings;
    }
}