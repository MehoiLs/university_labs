﻿using Lab3.Data.Exception;
using Microsoft.EntityFrameworkCore;
using EntityState = Microsoft.EntityFrameworkCore.EntityState;

namespace Lab3.Data.Repository;

public class GeneralRepository<T>(DbContext ctx)
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

    public T Create(T entity)
    {
        ArgumentNullException.ThrowIfNull(entity);
        _dbSet.Add(entity);

        ctx.SaveChanges();
        return entity;
    }

    public T Update(T entity)
    {
        ArgumentNullException.ThrowIfNull(entity);
        _dbSet.Attach(entity);
        var entry = ctx.Entry(entity) ?? throw new NotFoundException();
        entry.State = EntityState.Modified;

        ctx.SaveChanges();
        return entity;
    }

    public void Delete(long id)
    {
        var entity = _dbSet.Find(id) ?? throw new NotFoundException();
        _dbSet.Remove(entity);

        ctx.SaveChanges();
    }
}