using Lab3.Exception;

namespace Lab3.Extensions;

public static class RepositoryExtensions
{
    
    public static T FirstOrThrow<T>(this IQueryable<T> source, Func<T, bool> predicate)
    {
        return FirstOrThrow(source, predicate, new NotFoundException());
    }
    public static T FirstOrThrow<T>(this IQueryable<T> source, Func<T, bool> predicate, System.Exception exception)
    {
        var result = source.FirstOrDefault(predicate) ?? throw exception;
        return result;
    }
    
}