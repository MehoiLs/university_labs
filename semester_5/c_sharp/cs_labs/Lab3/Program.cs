using Lab3.Extensions;

namespace Lab3;

public static class Program
{
    public static void Main(string[] args)
    {
        var app = CreateWebApplication(args);
        InitWebApplication(app);

        app.Run();
    }

    private static WebApplication CreateWebApplication(string[] args)
    {
        var builder = WebApplication.CreateBuilder(args);

        builder.Services.AddDbContexts();
        builder.Services.AddServices();

        builder.Services.AddControllers();
        builder.Services.AddEndpointsApiExplorer();
        builder.Services.AddSwaggerGen();

        return builder.Build();
    }

    private static void InitWebApplication(WebApplication app)
    {
        app.UseSwagger();
        app.UseSwaggerUI();
        app.MapControllers();
    }
}