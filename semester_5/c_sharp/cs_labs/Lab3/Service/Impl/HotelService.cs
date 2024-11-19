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
        return GetKeyCardById(keyCard.Id);
    }

    public List<KeyCardViewModel> GetAllKeyCards()
    {
        return [..keyCardRepository.GetAll().Select(KeyCardMapper.ToPartialModel)];
    }

    public KeyCardViewModel GetKeyCardById(long id)
    {
        var hotel = keyCardRepository.GetEntitySet()
            .Include(kc => kc.Hotel)
            .Include(kc => kc.Client)
            .FirstOrThrow(h => h.Id == id);
        return KeyCardMapper.ToModel(hotel);
    }

    public void AssignKeyCard(KeyCardAssignModel model)
    {
        var keyCard = keyCardRepository.GetById(model.KeyCardId);
        keyCard.ClientIt = model.ClientId;
        keyCardRepository.Update(keyCard);
    }

    public void DeAssignKeyCard(long keyCardId)
    {
        var keyCard = keyCardRepository.GetById(keyCardId);
        keyCard.ClientIt = null;
        keyCardRepository.Update(keyCard);
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