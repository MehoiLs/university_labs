using System;
using System.Collections.Generic;
using System.Linq;

namespace Lab2.card
{
    public class Card
    {
        private CardSuit Suit { get; }
        private CardRank Rank { get; }

        public Card(CardSuit suit, CardRank rank)
        {
            Suit = suit;
            Rank = rank;
        }

        public static List<Card> CreateOrderedDecks(params CardSuit[] suits)
        {
            return suits
                .SelectMany(suit =>
                {
                    return GetAllRanks()
                        .Select(rank => new Card(suit, rank))
                        .OrderBy(card => card.Rank);
                })
                .ToList();
        }

        /**
         * Consumes [CardRank]:[CardSuit].
         * Example: Spades:Ace
         */
        public static bool TryParse(string str, out Card card)
        {
            var split = str.Split(':');
            var isRankParsed = Enum.TryParse(split[0], out CardRank rank);
            var isSuitParsed = Enum.TryParse(split[1], out CardSuit suit);

            if (!isSuitParsed || !isRankParsed)
            {
                card = null;
                return false;
            }
            
            card = new Card(suit, rank);
            return true;
        }

        /**
         * Prints out all Clubs first having Ace as the lowest rank (ascending),
         * then prints out all Hearts having Ace as the highest rank (ascending).
         */
        public static List<Card> performTask2(List<Card> cards)
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

        public static string Calculate21WinPossibility(List<Card> playersHand, List<Card> deck)
        {
            const int max21WinSum = 21;
            
            if (!Is21Hand(playersHand) || !Is21Hand(deck))
            {
                throw new ArgumentException("Invalid decks. See the rules of the '21' card game");
            }
            
            var currentSum = Count21Ranks(playersHand);
            if (currentSum > max21WinSum)
            {
                return "0%";
            }

            var winCardsCount = deck
                .Count(card => (Get21CardRank(playersHand, card) + currentSum) == max21WinSum);
            
            var winPercent = winCardsCount / deck.Count;
            return $"{winPercent:P1}% ({winCardsCount}/{deck.Count})";
        }
        
        public override string ToString()
        {
            return $"{Rank} of {Suit}";
        }

        private static CardRank[] GetAllRanks()
        {
            return Enum
                .GetValues(typeof(CardRank))
                .Cast<CardRank>()
                .OrderBy(rank => rank)
                .ToArray();
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

        // "21" util
        private static bool Is21Hand(List<Card> cards)
        {
            return cards.All(card => card.Rank.Is21Rank());
        }

        private static int Count21Ranks(List<Card> cards)
        {
            var acePredicate = new Func<Card, bool>(card => card.Rank == CardRank.Ace);

            var noAceSum = cards
                .Where(card => !acePredicate(card))
                .Sum(Get21CardRankNoAce);
            
            var acesCount = cards
                .Where(acePredicate)
                .Count();
            
            return noAceSum + Get21AceRanks(cards, acesCount);
        }

        private static int Get21CardRankNoAce(Card card)
        {
            switch (card.Rank)
            {
                case CardRank.Six:
                    return 6;
                case CardRank.Seven:
                    return 7;
                case CardRank.Eight:
                    return 8;
                case CardRank.Nine:
                    return 9;
                case CardRank.Ten:
                    return 10;
                case CardRank.Jack:
                    return 2;
                case CardRank.Queen:
                    return 3;
                case CardRank.King:
                    return 4;
                
                case CardRank.Ace:
                case CardRank.Two:
                case CardRank.Three:
                case CardRank.Four:
                case CardRank.Five:
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }

        private static int Get21CardRank(List<Card> currentHand, Card card)
        {
            return card.Rank != CardRank.Ace ? Get21CardRankNoAce(card) : Get21AceRanks(currentHand, 1);
        }

        private static int Get21AceRanks(List<Card> currentHand, int acesCount)
        {
            var acePredicate = new Func<Card, bool>(card => card.Rank == CardRank.Ace);
            const int nonExceededAceRank = 11;
            const int exceededAceRank = 1;
            const int exceededSumForAce = 11;
            const int maxCardsOfSameRank = 4;
            
            var acesActualCount = currentHand
                .Count(acePredicate);

            var isAceCountExceeded = 
                acesActualCount > maxCardsOfSameRank
                || acesCount > maxCardsOfSameRank
                || acesActualCount + acesCount > maxCardsOfSameRank;
            
            if (isAceCountExceeded)
            {
                throw new ArgumentException(
                    "Invalid number of aces. " +
                    $"Actual : {acesActualCount}, " +
                    $"Getting : {acesCount}, " +
                    $"Max expected : {maxCardsOfSameRank}"
                );
            }

            var noAceSum = currentHand
                .Where(card => !acePredicate(card))
                .Sum(card => (int) card.Rank + 1);
            
            var isAceSumExceeded = (noAceSum >= exceededSumForAce) || (acesCount > 1) || (acesActualCount > 1);
            return isAceSumExceeded ? (exceededAceRank * acesCount) : nonExceededAceRank;
        }
        
    }
}