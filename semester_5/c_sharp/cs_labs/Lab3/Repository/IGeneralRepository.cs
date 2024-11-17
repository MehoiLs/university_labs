using Microsoft.EntityFrameworkCore;

namespace Lab3.Repository;

public interface IGeneralRepository<T> where T : class
{
    IEnumerable<T> GetAll();
    T GetById(long id);
    T Create(T entity);
    T Update(T entity);
    void Delete(long id);

    DbSet<T> GetEntitySet();
}