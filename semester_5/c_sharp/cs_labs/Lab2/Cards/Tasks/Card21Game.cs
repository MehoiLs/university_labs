using System;
using System.Collections.Generic;
using System.Linq;

namespace Lab2.Cards.Tasks
{
    public static class Card21Game
    {
        private const int Max21WinSum = 21;    
        private const int MaxAceRank = 11;
        
        public static string Calculate21WinPossibility(List<Card> playersHand, List<Card> deck)
        {
            if (!Is21Hand(playersHand) || !Is21Hand(deck))
            {
                throw new ArgumentException("Invalid decks. See the rules of the '21' card game");
            }
            
            var currentSum = Count21Ranks(playersHand);
            if (currentSum > Max21WinSum)
            {
                return "0%";
            }

            double winCardsCount = deck
                .Count(card => (Get21CardRank(playersHand, card) + currentSum) == Max21WinSum);
            
            var winPercent = winCardsCount / deck.Count;
            return $"{winPercent:P1} ({winCardsCount}/{deck.Count})";
        }

        public static List<Card> GetFullDeck()
        {
            return Card
                .GetAllSuits()
                .SelectMany(suit =>
                {
                    return Card.GetAllRanks()
                        .Where(rank => rank.Is21Rank())
                        .Select(rank => new Card(suit, rank));
                })
                .ToList();
        }
        
        private static bool Is21Hand(List<Card> cards)
        {
            return cards.All(card => card.Rank.Is21Rank());
        }

        public static int Count21Ranks(List<Card> cards)
        {
            var acePredicate = new Func<Card, bool>(card => card.Rank == CardRank.Ace);

            var noAceSum = cards
                .Where(card => !acePredicate(card))
                .Sum(Get21CardRankNoAce);
            
            var acesCount = cards
                .Where(acePredicate)
                .Count();
            
            return noAceSum + Get21AceRanks(noAceSum, acesCount);
        }
        
        private static int Get21CardRank(List<Card> currentHand, Card card)
        {
            if (card.Rank != CardRank.Ace)
            {
                return Get21CardRankNoAce(card);
            }
            var currentHandCount = Count21Ranks(currentHand); 
            return Get21AceRanks(currentHandCount, 1);
        }

        private static int Get21CardRankNoAce(Card card)
        {
            switch (card.Rank)
            {
                case CardRank.Six:
                case CardRank.Seven:
                case CardRank.Eight:
                case CardRank.Nine:
                case CardRank.Ten:
                    return card.Rank.AsInt();
                
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

        private static int Get21AceRanks(int currentRanksCount, int acesCount)
        {
            if ((currentRanksCount + acesCount) <= MaxAceRank)
            {
                return acesCount - 1 + MaxAceRank;
            }
            return acesCount;
        }
    }
}