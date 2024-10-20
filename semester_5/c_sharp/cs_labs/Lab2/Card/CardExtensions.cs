namespace Lab2.card
{
    public static class CardExtensions
    {
        public static bool IsRed(this CardSuit suit)
        {
            return suit == CardSuit.Hearts || suit == CardSuit.Diamonds;
        }

        public static bool Is21Rank(this CardRank rank)
        {
            return rank != CardRank.Two 
                   && rank != CardRank.Three
                   && rank != CardRank.Four
                   && rank != CardRank.Five;
        }
    }
}