namespace Lab3.Exception;

public class DefaultException : System.Exception
{
    public DefaultException()
    {
    }

    public DefaultException(string message) : base(message)
    {
    }

    public DefaultException(string message, System.Exception inner) : base(message, inner)
    {
    }
}