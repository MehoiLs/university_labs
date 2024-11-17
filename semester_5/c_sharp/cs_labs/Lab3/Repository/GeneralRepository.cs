using Lab3.Context;
using Lab3.Exception;
using Microsoft.EntityFrameworkCore;
using EntityState = Microsoft.EntityFrameworkCore.EntityState;

namespace Lab3.Repository;

public class GeneralRepository<T>(ApplicationDbContext ctx) : IGeneralRepository<T>
    where T : class
{
    private readonly DbSet<T> _dbSet = ctx.Set<T>();

    public IEnumerable<T> GetAll()
    {
        return _dbSet.ToList();
    }

    public T GetById(long id)
    {
        return _dbSet.Find(id) ?? throw new NotFoundException();
    }

    public void Create(T entity)
    {
        ArgumentNullException.ThrowIfNull(entity);
        _dbSet.Add(entity);

        ctx.SaveChanges();
    }

    public void Update(T entity)
    {
        ArgumentNullException.ThrowIfNull(entity);
        _dbSet.Attach(entity);
        var entry = ctx.Entry(entity) ?? throw new NotFoundException();
        entry.State = EntityState.Modified;

        ctx.SaveChanges();
    }

    public void DeleteById(long id)
    {
        var entity = _dbSet.Find(id) ?? throw new NotFoundException();
        _dbSet.Remove(entity);

        ctx.SaveChanges();
    }

    public DbSet<T> GetEntitySet()
    {
        return _dbSet;
    }
}