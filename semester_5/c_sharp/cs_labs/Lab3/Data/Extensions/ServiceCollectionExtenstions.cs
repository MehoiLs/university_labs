using Lab3.Data.Context;
using Lab3.Data.Service;
using Lab3.Data.Service.Impl;

namespace Lab3.Data.Extensions;

public static class ServiceCollectionExtensions
{
    public static IServiceCollection AddDbContexts(this IServiceCollection services)
    {
        services.AddDbContext<HotelContext>();
        services.AddDbContext<HotelRoomContext>();
        services.AddDbContext<InvoicesContext>();
        services.AddDbContext<PeopleContext>();
        services.AddDbContext<StaysContext>();

        return services;
    }

    public static IServiceCollection AddServices(this IServiceCollection services)
    {
        services.AddScoped<IHotelService, HotelService>();

        return services;
    }
}