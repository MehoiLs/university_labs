using Lab3.Data.Context.Default;
using Lab3.Entities.Hotel.People;
using Microsoft.EntityFrameworkCore;

namespace Lab3.Data.Context;

public class PeopleContext(DbContextOptions<PeopleContext> options) : DefaultDbContext<PeopleContext>(options)
{
    public DbSet<Client> Clients { get; set; }
    public DbSet<Employee> Employees { get; set; }
    public DbSet<Occupation> Occupations { get; set; }
    public DbSet<Owner> Owners { get; set; }
}