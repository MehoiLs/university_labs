using System.Collections.Generic;

namespace Lab2.Cards
{
    public static class CardExtensions
    {
        public static bool IsRed(this CardSuit suit)
        {
            return suit == CardSuit.Hearts || suit == CardSuit.Diamonds;
        }

        public static int AsInt(this CardRank rank)
        {
            return (int)rank + 1;
        }

        public static bool Is21Rank(this CardRank rank)
        {
            return rank != CardRank.Two 
                   && rank != CardRank.Three
                   && rank != CardRank.Four
                   && rank != CardRank.Five;
        }

        public static string UnfoldToString(this List<Card> list)
        {
            return string.Join(", ", list);
        }
    }
}