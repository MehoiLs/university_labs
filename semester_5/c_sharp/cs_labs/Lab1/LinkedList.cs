using System;
using System.Net;

namespace Lab1
{
    public class LinkedList<T>
    {
        internal class Node
        {
            internal readonly T Data;
            internal Node Next;
            internal Node Prev;

            public Node(T data)
            {
                this.Data = data;
                this.Next = null;
                this.Prev = null;
            }
        }
        
        private const string EmptyListExceptionMessage = "List is empty";

        private Node head;
        private Node tail;

        private void InsertFirst(T data)
        {
            var newNode = new Node(data)
            {
                Next = head,
                Prev = null
            };
            
            if (head == null)
            {
                head = newNode;
                tail = newNode;
            }
            else
            {
                head.Prev = newNode;
                head = newNode;
            }
        }

        private void InsertLast(T data)
        {
            var newNode = new Node(data)
            {
                Next = null,
                Prev = tail
            };
            
            if (tail == null)
            {
                head = newNode;
            }
            else
            {
                tail.Next = newNode;
            }

            tail = newNode;
        }

        public void InsertFirst(params T[] items)
        {
            foreach (var item in items)
            {
                InsertFirst(item);
            }
        }
        
        public void InsertLast(params T[] items)
        {
            foreach (var item in items)
            {
                InsertLast(item);
            }
        }

        public T RemoveFirst()
        {
            if (head == null)
            {
                throw new InvalidOperationException(EmptyListExceptionMessage);
            }

            var removedNode = head;
            head = head.Next;

            if (head == null)
            {
                tail = null;
            }
            else
            {
                head.Prev = null;
            }
            
            return removedNode.Data;
        }

        public T RemoveLast()
        {
            if (tail == null)
            {
                throw new InvalidOperationException(EmptyListExceptionMessage);
            }

            var removedNode = tail;
            tail = tail.Prev;

            if (tail == null)
            {
                head = null;
            }
            else
            {
                tail.Next = null;
            }

            return removedNode.Data;
        }

        public T GetFirst()
        {
            return head.Data;
        }
        
        public T GetLast()
        {
            return tail.Data;
        }

        public bool IsEmpty()
        {
            return head == null && tail == null;
        }

        public void Clean()
        {
            while (!IsEmpty())
            {
                RemoveFirst();
            }
        }

        public override string ToString()
        {
            var str = "{ ";
            
            var iter = head;
            while (iter != null)
            {
                str += iter.Data + "; ";
                iter = iter.Next;
            }

            str += "}";
            return str;
        }
    }
}