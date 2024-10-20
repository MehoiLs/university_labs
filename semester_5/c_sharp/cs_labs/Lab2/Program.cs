using System;
using System.Collections.Generic;
using Lab2.card;

namespace Lab2
{
    internal static class Program
    {
        public static void Main(string[] args)
        {
            Console.OutputEncoding = System.Text.Encoding.UTF8;
            
            Task0();
            Task1();
            Task2();
            Task3();
        }

        private static void Task0()
        {
            Console.WriteLine("\n\tTask №0");
            var decks = Card.CreateOrderedDecks(
                CardSuit.Clubs,
                CardSuit.Diamonds,
                CardSuit.Hearts,
                CardSuit.Spades,
                CardSuit.Diamonds,
                CardSuit.Clubs
            );
            Console.WriteLine(string.Join(", ", decks));
        }

        private static void Task1()
        {
            Console.WriteLine("\n\tTask №1");

            const string aceSpades = "Ace:Spades";
            Card.TryParse(aceSpades, out var aceOfSpades);
            Console.WriteLine($"Parsed {aceSpades} -> {aceOfSpades}");

            const string sevenHearts = "Seven:Hearts"; 
            Card.TryParse(sevenHearts, out var sevenOfHearts);
            Console.WriteLine($"Parsed {sevenHearts} -> {sevenOfHearts}");
           
            const string jackDiamonds = "Jack:Diamonds";
            Card.TryParse(jackDiamonds, out var jackOfDiamonds);
            Console.WriteLine($"Parsed {jackDiamonds} -> {jackOfDiamonds}");
           
            const string sixHomes = "Six:Homes";
            Card.TryParse(sixHomes, out var sixOfHomes);
            Console.WriteLine($"Parsed {sixHomes} -> {sixOfHomes}");
           
            const string elevenParks = "Eleven:Parks";
            Card.TryParse(elevenParks, out var elevenOfParks);
            Console.WriteLine($"Parsed {elevenParks} -> {elevenOfParks}");
        }


        private static void Task2()
        {
            Console.WriteLine("\n\tTask №2");
            var deck = new List<Card>
            {
                new Card(CardSuit.Clubs, CardRank.Four),
                new Card(CardSuit.Hearts, CardRank.Queen),
                new Card(CardSuit.Hearts, CardRank.Six),
                new Card(CardSuit.Clubs, CardRank.Ace),
                new Card(CardSuit.Hearts, CardRank.Ace),
                new Card(CardSuit.Spades, CardRank.Ace),
                new Card(CardSuit.Hearts, CardRank.Three),
                new Card(CardSuit.Clubs, CardRank.Queen),
                new Card(CardSuit.Diamonds, CardRank.Two),
                new Card(CardSuit.Hearts, CardRank.Jack),
                new Card(CardSuit.Spades, CardRank.Five),
                new Card(CardSuit.Hearts, CardRank.Ten),
                new Card(CardSuit.Clubs, CardRank.Two),
                new Card(CardSuit.Clubs, CardRank.King)
            };
            var sortedDeck = Card.performTask2(deck);
            Console.WriteLine(string.Join(", ", sortedDeck));
        }

        private static void Task3()
        {
            Console.WriteLine("\n\tTask №3");

            Console.WriteLine("\nStreak #1:");
            var deck1 = new List<Card>
            {
                new Card(CardSuit.Clubs, CardRank.Four),
                new Card(CardSuit.Diamonds, CardRank.Five),
                new Card(CardSuit.Spades, CardRank.Six)
            };
            var deck2 = new List<Card>
            {
                new Card(CardSuit.Hearts, CardRank.Seven),
                new Card(CardSuit.Clubs, CardRank.Eight),
                new Card(CardSuit.Hearts, CardRank.Nine)
            };
            var streak1 = Card.CombineStreakDecks(deck1, deck2);
            Console.WriteLine(string.Join(", ", streak1));
            
            Console.WriteLine("\nStreak #2:");
            var deck3 = new List<Card>
            {
                new Card(CardSuit.Clubs, CardRank.Eight),
                new Card(CardSuit.Diamonds, CardRank.Nine),
                new Card(CardSuit.Spades, CardRank.Ten)
            };
            var deck4 = new List<Card>
            {
                new Card(CardSuit.Hearts, CardRank.Ten), // rank repeats
                new Card(CardSuit.Clubs, CardRank.Jack), 
                new Card(CardSuit.Hearts, CardRank.Queen)
            };
            var streak2 = Card.CombineStreakDecks(deck3, deck4);
            Console.WriteLine(string.Join(", ", streak2));
            
            Console.WriteLine("\nStreak #3:");
            var deck5 = new List<Card>
            {
                new Card(CardSuit.Clubs, CardRank.Four),
                new Card(CardSuit.Diamonds, CardRank.Five),
                new Card(CardSuit.Diamonds, CardRank.Six) // suit repeats
            };
            var deck6 = new List<Card>
            {
                new Card(CardSuit.Hearts, CardRank.Seven),
                new Card(CardSuit.Clubs, CardRank.Eight),
                new Card(CardSuit.Hearts, CardRank.Nine)
            };
            var streak3 = Card.CombineStreakDecks(deck5, deck6);
            Console.WriteLine(string.Join(", ", streak3));
        }
    }
}