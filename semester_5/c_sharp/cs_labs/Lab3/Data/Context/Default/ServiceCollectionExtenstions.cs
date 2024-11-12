namespace Lab3.Data.Context.Default;

public static class ServiceCollectionExtensions
{
    public static IServiceCollection InitDbContexts(this IServiceCollection services)
    {
        services.AddDbContext<HotelContext>();
        services.AddDbContext<HotelRoomContext>();
        services.AddDbContext<InvoicesContext>();
        services.AddDbContext<PeopleContext>();
        services.AddDbContext<StaysContext>();

        return services;
    }
}