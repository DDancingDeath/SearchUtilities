using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LuceneDotNet
{
    class Program
    {
        static void Main(string[] args)
        {
            Controller c = new Controller();

            while(true)
            {

                Console.WriteLine("Select the operation.\n" +
                                    "1. Index\n" +  
                                    "2. Search\n" +
                                    "3. Exit\n");


                string option = Console.ReadLine();

                switch(Convert.ToInt32(option))
                {
                    case 1:
                        Console.WriteLine("Enter Directory to index");
                        string dir = Console.ReadLine();
                        c.DoLuceneIndex(dir);
                        Console.WriteLine("Done.\n");
                        break;
                    case 2:
                        Console.WriteLine("Enter string to search");
                        string str = Console.ReadLine();
                        c.DoLuceneSearch(str);
                        Console.WriteLine("Done.\n");
                        break;

                    default:
                        return;
                }

            }
            
        }
    }
}
