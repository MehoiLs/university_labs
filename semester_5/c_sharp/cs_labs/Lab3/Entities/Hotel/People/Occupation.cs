using Lab3.Entities.Enums;

namespace Lab3.Entities.Hotel.People;

public class Occupation
{
    public long Id { get; set; }
    public long Salary { get; set; }

    public required Hotel Hotel { get; set; }
    public OccupationType Type { get; set; }
}