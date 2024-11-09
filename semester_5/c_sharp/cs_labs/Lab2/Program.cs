using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Lab2.Cards;
using Lab2.Cards.Tasks;

namespace Lab2
{
    internal static class Program
    {
        public static void Main(string[] args)
        {
            Console.OutputEncoding = Encoding.UTF8;
            
            Task0();
            Task1();
            Task2();
            Task3();
            Task4();
        }

        private static void Task0()
        {
            Console.WriteLine("\n\n\tTask №0");
            Console.WriteLine("Sorting cards by given suit order and rank ascending...");
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
            Console.WriteLine("\n\n\tTask №1");

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
            Console.WriteLine("\n\n\tTask №2");
            Console.WriteLine("Printing out all Clubs first having Ace as the lowest rank (ascending);\n" +
                              "all Hearts having Ace as the highest rank (ascending)...");
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
            var sortedDeck = CardTasks.PerformTask2(deck);
            Console.WriteLine(string.Join(", ", sortedDeck));
        }

        private static void Task3()
        {
            Console.WriteLine("\n\n\tTask №3");

            Console.WriteLine("Streak #1:");
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
            var streak1 = CardTasks.CombineStreakDecks(deck1, deck2);
            Console.WriteLine(CardStreakToString(streak1));
            
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
            var streak2 = CardTasks.CombineStreakDecks(deck3, deck4);
            Console.WriteLine(CardStreakToString(streak2));
            
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
            var streak3 = CardTasks.CombineStreakDecks(deck5, deck6);
            Console.WriteLine(CardStreakToString(streak3));
            
            Console.WriteLine("\nStreak #4:");
            var deck7 = new List<Card>
            {
                new Card(CardSuit.Spades, CardRank.Two), 
                new Card(CardSuit.Hearts, CardRank.Seven), // streak is interrupted
                new Card(CardSuit.Spades, CardRank.Eight) 
            };
            var deck8 = new List<Card>
            {
                new Card(CardSuit.Diamonds, CardRank.Nine),
                new Card(CardSuit.Clubs, CardRank.Ten),
                new Card(CardSuit.Hearts, CardRank.Jack)
            };
            var streak4 = CardTasks.CombineStreakDecks(deck7, deck8);
            Console.WriteLine(CardStreakToString(streak4));
            
            Console.WriteLine("\nStreak #5:");
            var deck9 = new List<Card>
            {
                new Card(CardSuit.Spades, CardRank.Four), 
                new Card(CardSuit.Hearts, CardRank.Five),
                new Card(CardSuit.Spades, CardRank.Six),
                new Card(CardSuit.Diamonds, CardRank.Seven),
                new Card(CardSuit.Clubs, CardRank.Eight),
                new Card(CardSuit.Diamonds, CardRank.Nine),
                new Card(CardSuit.Clubs, CardRank.Ten),
            };
            var deck10 = new List<Card>
            {
                new Card(CardSuit.Hearts, CardRank.Jack),
                new Card(CardSuit.Spades, CardRank.Queen),
                new Card(CardSuit.Hearts, CardRank.King)
            };
            var streak5 = CardTasks.CombineStreakDecks(deck9, deck10);
            Console.WriteLine(CardStreakToString(streak5));
        }

        private static string CardStreakToString(List<Card> streak)
        {
            return (streak.Count == 0) ? " [no streak]" : streak.UnfoldToString();
        }

        private static void Task4()
        {
            Console.WriteLine("\n\n\tTask №4");
            
            var hand1 = new List<Card>
            {
                new Card(CardSuit.Clubs, CardRank.Six),
                new Card(CardSuit.Diamonds, CardRank.Seven),
            };
            var deck1 = new List<Card>
            {
                new Card(CardSuit.Clubs, CardRank.Eight),
                new Card(CardSuit.Hearts, CardRank.Eight),
                new Card(CardSuit.Hearts, CardRank.Nine),
                new Card(CardSuit.Hearts, CardRank.Ten),
                new Card(CardSuit.Hearts, CardRank.Jack),
                new Card(CardSuit.Hearts, CardRank.Queen),
                new Card(CardSuit.Hearts, CardRank.King),
                new Card(CardSuit.Hearts, CardRank.Ace),
            };
            
            var result1 = Card21Game.Calculate21WinPossibility(hand1, deck1);
            Console.WriteLine(" Entry #1.\n " +
                              $"- Hand: {hand1.UnfoldToString()} (sum: {Card21Game.Count21Ranks(hand1)})\n " +
                              $"- Deck: {deck1.UnfoldToString()}\n " +
                              $"=> Result: {result1}"
            );
            
            var hand2 = new List<Card>
            {
                new Card(CardSuit.Clubs, CardRank.Ace),
                new Card(CardSuit.Diamonds, CardRank.Ace),
                new Card(CardSuit.Diamonds, CardRank.Eight),
            };
            var deck2 = Card21Game.GetFullDeck()
                .Except(hand2)
                .ToList();
            
            var result2 = Card21Game.Calculate21WinPossibility(hand2, deck2);
            Console.WriteLine("\n Entry #2.\n " +
                              $"- Hand: {hand2.UnfoldToString()} (sum: {Card21Game.Count21Ranks(hand2)})\n " +
                              $"- Deck: {deck2.UnfoldToString()}\n " +
                              $"=> Result: {result2}"
            );
            
            var hand3 = new List<Card>
            {
                new Card(CardSuit.Hearts, CardRank.Eight),
                new Card(CardSuit.Spades, CardRank.Nine),
                new Card(CardSuit.Spades, CardRank.Ten),
            };
            var deck3 = Card21Game.GetFullDeck()
                .Except(hand3)
                .ToList();
            
            var result3 = Card21Game.Calculate21WinPossibility(hand3, deck3);
            Console.WriteLine("\n Entry #3.\n " +
                              $"- Hand: {hand3.UnfoldToString()} (sum: {Card21Game.Count21Ranks(hand3)})\n " +
                              $"- Deck: {deck3.UnfoldToString()}\n " +
                              $"=> Result: {result3}"
            );
            
            var hand4 = new List<Card>
            {
                new Card(CardSuit.Hearts, CardRank.Jack),
                new Card(CardSuit.Spades, CardRank.Queen),
                new Card(CardSuit.Clubs, CardRank.King),
                new Card(CardSuit.Diamonds, CardRank.Ace),
            };
            var deck4 = Card21Game.GetFullDeck()
                .Except(hand4)
                .ToList();
            
            var result4 = Card21Game.Calculate21WinPossibility(hand4, deck4);
            Console.WriteLine("\n Entry #4.\n " +
                              $"- Hand: {hand4.UnfoldToString()} (sum: {Card21Game.Count21Ranks(hand4)})\n " +
                              $"- Deck: {deck4.UnfoldToString()}\n " +
                              $"=> Result: {result4}"
            );
            
            var hand5 = new List<Card>
            {
                new Card(CardSuit.Hearts, CardRank.Six),
                new Card(CardSuit.Spades, CardRank.King),
            };
            var deck5 = new List<Card>
            {
                new Card(CardSuit.Hearts, CardRank.Ace),
                new Card(CardSuit.Spades, CardRank.Ace),
                new Card(CardSuit.Diamonds, CardRank.Ace),
                new Card(CardSuit.Clubs, CardRank.Ace),
            };
            
            var result5 = Card21Game.Calculate21WinPossibility(hand5, deck5);
            Console.WriteLine("\n Entry #5.\n " +
                              $"- Hand: {hand5.UnfoldToString()} (sum: {Card21Game.Count21Ranks(hand5)})\n " +
                              $"- Deck: {deck5.UnfoldToString()}\n " +
                              $"=> Result: {result5}"
            );
        }
        
        
    }
}