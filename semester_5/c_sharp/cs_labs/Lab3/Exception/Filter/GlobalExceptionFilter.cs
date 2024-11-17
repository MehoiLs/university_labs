using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Filters;

namespace Lab3.Exception.Filter;

public class GlobalExceptionFilter : IExceptionFilter
{
    public void OnException(ExceptionContext ctx)
    {
        var exception = ctx.Exception;
        ctx.Result = exception switch
        {
            NotFoundException e 
                => CreateResult("Resource not found", StatusCodes.Status404NotFound, e),
            ArgumentException e 
                => CreateResult("Invalid argument", StatusCodes.Status400BadRequest, e),
            InvalidOperationException e 
                => CreateResult("Operation not allowed", StatusCodes.Status400BadRequest, e),
            _ => CreateResult("Unexpected error", StatusCodes.Status500InternalServerError)
        };
        ctx.ExceptionHandled = true;
    }

    private static ObjectResult CreateResult(string msg, int code, System.Exception? e = null)
    {
        return new ObjectResult(new
        {
            message = msg,
            error = e?.Message
        })
        {
            StatusCode = code
        };
    }
}