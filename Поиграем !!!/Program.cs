
class Program
{
    static void Main(string[] args)
    {
        Console.WriteLine("Выберите программу:");
        Console.WriteLine("1. Угадай число");
        Console.WriteLine("2. Таблица умножения");
        Console.WriteLine("3. Вывод делителей числа");
        Console.WriteLine("4. Выход");

        int choice = Convert.ToInt32(Console.ReadLine());

        switch (choice)
        {
            case 1:
                GuessNumber();
                break;
            case 2:
                MultiplicationTable();
                break;
            case 3:
                PrintDivisors();
                break;
            case 4:
                PrintExcape();
                break;

            default:
                Console.WriteLine("Неверный выбор.");
                break;
        }

        Console.ReadLine();
    }
    static void GuessNumber()
    {
        Random random = new Random();
        int randomNumber = random.Next(0, 101);
        int userNumber;

        Console.WriteLine("Игра 'Угадай число'");
        Console.WriteLine("Введите число от 0 до 100:");

        do
        {
            string input = Console.ReadLine();
            if (!int.TryParse(input, out userNumber))
            {
                Console.WriteLine("Введите корректное число!");
                continue;
            }

            if (userNumber > randomNumber)
            {
                Console.WriteLine("Загаданное число меньше, чем введенное");
            }
            else if (userNumber < randomNumber)
            {
                Console.WriteLine("Загаданное число больше, чем введенное");
            }
            else
            {
                Console.WriteLine("Вы угадали число! Поздравляем!");
                return;
            }
        } while (true);
    }


    
    static void MultiplicationTable()
    {
        int size = 10; 

      
        int[,] multiplicationTable = new int[size, size];

        
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                multiplicationTable[i, j] = (i + 1) * (j + 1);
            }
        }

        
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                Console.Write("{0,4}", multiplicationTable[i, j]); 
            }
            Console.WriteLine();
            
        }
     
    }

    static void PrintDivisors()
    {
        Console.WriteLine("Введите число:");

        int number;
        bool isNumber = int.TryParse(Console.ReadLine(), out number);

        if (!isNumber)
        {
            Console.WriteLine("Число введено неправильно.");
            return;
        }

        Console.WriteLine("Делители числа {number}:");

        for (int i = 1; i <= number; i++)
        {
            if (number % i == 0)
            {
                Console.WriteLine(i);

            }

        }
    
}
    static void PrintExcape()
    { Console.WriteLine("Пока");
        Environment.Exit(0);

    }
}


       
   


