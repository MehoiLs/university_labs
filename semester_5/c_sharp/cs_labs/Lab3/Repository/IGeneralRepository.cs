using Microsoft.EntityFrameworkCore;

namespace Lab3.Repository;

public interface IGeneralRepository<T> where T : class
{
    IEnumerable<T> GetAll();
    T GetById(long id);
    void Create(T entity);
    void Update(T entity);
    void DeleteById(long id);

    DbSet<T> GetEntitySet();
}