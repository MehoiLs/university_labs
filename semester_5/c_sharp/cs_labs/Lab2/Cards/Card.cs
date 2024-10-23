using System;
using System.Collections.Generic;
using System.Linq;

namespace Lab2.Cards
{
    public class Card
    {
        protected internal CardSuit Suit { get; }
        protected internal CardRank Rank { get; }

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
        
        public override string ToString()
        {
            // return $"{Rank} of {Suit}";
            return $"{GetRankShortName(Rank)}{GetSuitShortName(Suit)}";
        }

        protected internal static CardRank[] GetAllRanks()
        {
            return Enum
                .GetValues(typeof(CardRank))
                .Cast<CardRank>()
                .OrderBy(rank => rank)
                .ToArray();
        }
        
        protected internal static CardSuit[] GetAllSuits()
        {
            return Enum
                .GetValues(typeof(CardSuit))
                .Cast<CardSuit>()
                .OrderBy(suit => suit)
                .ToArray();
        }

        private static string GetRankShortName(CardRank rank)
        {
            switch (rank)
            {
                case CardRank.Ace:
                    return "A";
                case CardRank.Two:
                    return "2";
                case CardRank.Three:
                    return "3";
                case CardRank.Four:
                    return "4";
                case CardRank.Five:
                    return "5";
                case CardRank.Six:
                    return "6";
                case CardRank.Seven:
                    return "7";
                case CardRank.Eight:
                    return "8";
                case CardRank.Nine:
                    return "9";
                case CardRank.Ten:
                    return "10";
                case CardRank.Jack:
                    return "J";
                case CardRank.Queen:
                    return "Q";
                case CardRank.King:
                    return "K";
                default:
                    throw new ArgumentOutOfRangeException(nameof(rank), rank, null);
            }
        }

        private static string GetSuitShortName(CardSuit suit)
        {
            switch (suit)
            {
                case CardSuit.Clubs:
                    return "\u2663";
                case CardSuit.Diamonds:
                    return "\u2666";
                case CardSuit.Hearts:
                    return "\u2665";
                case CardSuit.Spades:
                    return "\u2660";
                default:
                    throw new ArgumentOutOfRangeException(nameof(suit), suit, null);
            }
        }
        
        public override bool Equals(object obj)
        {
            if (obj is Card otherCard)
            {
                return Suit == otherCard.Suit && Rank == otherCard.Rank;
            }
            return false;
        }

        public override int GetHashCode()
        {
            return (int)Suit * 31 + (int)Rank;
        }
        
    }
}