namespace Lab3.Data.Exception;

public class NotFoundException : System.Exception
{
    public NotFoundException()
    {
    }

    public NotFoundException(string message) : base(message)
    {
    }

    public NotFoundException(string message, System.Exception inner) : base(message, inner)
    {
    }
}