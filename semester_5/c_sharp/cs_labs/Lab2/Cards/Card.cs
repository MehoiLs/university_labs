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
            return $"{(char)Rank}{(char)Suit}";
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