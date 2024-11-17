using Lab3.Context;
using Lab3.Exception.Filter;
using Lab3.Extensions;
using Microsoft.EntityFrameworkCore;

namespace Lab3;

public static class Program
{
    public static void Main(string[] args)
    {
        var app = CreateWebApplication(args);

        app.InitWebApplication();
        app.ApplyMigrations();
        app.Run();
    }

    private static WebApplication CreateWebApplication(string[] args)
    {
        var builder = WebApplication.CreateBuilder(args);

        builder.Services.AddDbContext<ApplicationDbContext>();
        builder.Services.AddServices();
        builder.Services.AddControllers(options => options.Filters.Add<GlobalExceptionFilter>());
        
        builder.Services.AddControllersWithViews()
            .AddNewtonsoftJson(options =>
                options.SerializerSettings.ReferenceLoopHandling = Newtonsoft.Json.ReferenceLoopHandling.Ignore
            );

        builder.Services.AddEndpointsApiExplorer();
        builder.Services.AddSwaggerGen();

        return builder.Build();
    }

    private static void InitWebApplication(this WebApplication app)
    {
        app.UseSwagger();
        app.UseSwaggerUI();
        app.MapControllers();
    }

    private static void ApplyMigrations(this WebApplication app)
    {
        using var scope = app.Services.CreateScope();
        var dbContext = scope.ServiceProvider.GetRequiredService<ApplicationDbContext>();
        dbContext.Database.Migrate();
    }
}