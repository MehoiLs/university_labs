using System;
using System.Collections.Generic;
using System.Linq;

namespace Lab2.Cards.Tasks
{
    public static class CardTasks
    {
        
        /**
        * Prints out all Clubs first having Ace as the lowest rank (ascending),
        * then prints out all Hearts having Ace as the highest rank (ascending).
        */
        public static List<Card> PerformTask2(List<Card> cards)
        {
            var clubsPredicate = new Func<Card, bool>(card => card.Suit == CardSuit.Clubs);
            var heartsNoAcePredicate = new Func<Card, bool>(card => card.Suit == CardSuit.Hearts && card.Rank != CardRank.Ace);
            var heartsOfAcePredicate = new Func<Card, bool>(card => card.Suit == CardSuit.Hearts && card.Rank == CardRank.Ace);
            
            var clubs = cards
                .Where(clubsPredicate)
                .OrderBy(card => card.Rank)
                .ToList();
            var hearts = cards
                .Where(heartsNoAcePredicate)
                .OrderBy(card => card.Rank)
                .Concat(cards
                    .Where(heartsOfAcePredicate)
                )
                .ToList();
            return clubs
                .Concat(hearts)
                .ToList();
        }

        public static List<Card> CombineStreakDecks(List<Card> deck1, List<Card> deck2)
        {
            var cards = deck1.Concat(deck2).ToList();
            return IsStreakList(cards) ? cards : new List<Card>();
        }
        
        private static bool IsStreakList(List<Card> cards)
        {
            return cards
                .Zip(cards.Skip(1), 
                    (first, second) => new { First = first, Second = second }
                )
                .All(pair =>
                    pair.Second.Rank == pair.First.Rank + 1
                    && pair.Second.Suit.IsRed() == !pair.First.Suit.IsRed()
                );
        }
        
    }
} 