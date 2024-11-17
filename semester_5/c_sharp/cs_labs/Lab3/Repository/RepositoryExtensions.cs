using Lab3.Exception;

namespace Lab3.Repository;

public static class RepositoryExtensions
{
    
    public static T FirstOrThrow<T>(this IQueryable<T> source, Func<T, bool> predicate)
    {
        var result = source.FirstOrDefault(predicate) ?? throw new NotFoundException();
        return result;
    }
    public static T FirstOrThrow<T>(this IQueryable<T> source, Func<T, bool> predicate, System.Exception exception)
    {
        var result = source.FirstOrDefault(predicate) ?? throw exception;
        return result;
    }
    
}