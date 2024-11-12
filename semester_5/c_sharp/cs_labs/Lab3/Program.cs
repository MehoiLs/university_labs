using Lab3.Data.Context.Default;

namespace Lab3;

public static class Program
{
    public static void Main(string[] args)
    {
        var builder = WebApplication.CreateBuilder(args);
        builder.Services.InitDbContexts();
        var app = builder.Build();

        app.MapGet("/", () => "Hello World!");

        app.Run();
    }
}