using Lab3.Entity.Hotel;
using Lab3.Mapper;
using Lab3.Model.Create;
using Lab3.Model.Update;
using Lab3.Model.View;
using Lab3.Repository;
namespace Lab3.Service.Impl;

public class HotelOfferingService(
    IGeneralRepository<HotelOffering> repository
) : IHotelOfferingService
{

    public HotelOfferingViewModel Create(HotelOfferingCreateModel model)
    {
        var offering = HotelOfferingMapper.ToEntity(model);
        repository.Create(offering);
        return GetById(offering.Id);
    }

    public HotelOfferingViewModel Update(HotelOfferingUpdateModel model)
    {
        var offering = HotelOfferingMapper.ToEntity(model);
        repository.Update(offering);
        return GetById(offering.Id);
    }

    public void DeleteById(long id)
    {
        repository.DeleteById(id);
    }

    public HotelOfferingViewModel GetById(long id)
    {
        var offering = repository.GetById(id);
        return HotelOfferingMapper.ToModel(offering);
    }

    public List<HotelOfferingViewModel> GetAll()
    {
        return [..repository.GetAll().Select(HotelOfferingMapper.ToPartialModel)];
    }
}