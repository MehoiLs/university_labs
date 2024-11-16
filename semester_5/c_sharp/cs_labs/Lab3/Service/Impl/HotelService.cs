﻿using Lab3.Context;
using Lab3.Entity.Hotel;
using Lab3.Entity.Hotel.People;
using Lab3.Exception;
using Lab3.Repository;
using Microsoft.EntityFrameworkCore;

namespace Lab3.Service.Impl;

public class HotelService : IHotelService
{
    private static readonly ApplicationDbContext Ctx = new();
    private readonly GeneralRepository<Hotel> _hotelRepository = new(Ctx);
    private readonly GeneralRepository<Owner> _ownerRepository = new(Ctx);

    public Hotel Create(Hotel hotel)
    {
        return _hotelRepository.Create(hotel);
    }

    public Hotel GetById(long id)
    {
        //todo      + use viewModels       
        return _hotelRepository.GetById(id);
    }


    public Owner CreateOwner(Owner owner)
    {
        return _ownerRepository.Create(owner);
    }

    public Owner GetOwnerById(long id)
    {
        return _ownerRepository.GetById(id);
    }
}