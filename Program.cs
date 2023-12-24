using System;
using System.IO;
using System.Xml;
using System.Xml.Serialization;


namespace ConsoleTextEditor
{
    class Program
    {
        static void Main(string[] args)
        {
            // Выбор файла по имени перед началом программы
            Console.WriteLine("Введите имя файла:");
            Console.WriteLine("Нажмите F1 для сохранения файла");
            Console.WriteLine("Нажмите ESC для сохранения файла");
            string fileName = Console.ReadLine();

            // Проверка наличия файла
            if (!File.Exists(fileName))
            {
                Console.WriteLine("Файл не найден.");
                return;
            }

            // Выгрузка информации из файла
            string extension = Path.GetExtension(fileName)?.ToLower();
            string fileContent;

            if (extension == ".txt")
            {
                fileContent = File.ReadAllText(fileName);
            }

            else if (extension == ".xml")
            {
                using (var reader = XmlReader.Create(fileName))
                {
                    reader.ReadToFollowing("Data");
                    fileContent = reader.ReadInnerXml();
                }
            }
            else
            {
                Console.WriteLine("Неподдерживаемый формат файла.");
                return;
            }

            Console.WriteLine("Содержимое файла:");
            Console.WriteLine(fileContent);

            // Ожидание нажатия клавиши F1 (112 - код клавиши F1 в ASCII)
            while (true)
            {
                var keyInfo = Console.ReadKey();
                if (keyInfo.Key == ConsoleKey.F1)
                {
                    // Выбор формата сохранения файла
                    Console.WriteLine("\nВыберите формат сохранения файла: (txt/xml)");
                    string saveFormat = Console.ReadLine().ToLower();
                    if (saveFormat != "txt" && saveFormat != "xml")
                    {
                        Console.WriteLine("Недопустимый формат сохранения файла.");
                        continue;
                    }
                    // Запрос нового имени файла
                    Console.WriteLine("Введите новое имя файла:");
                    string newFileName = Console.ReadLine();
                    string newFilePath = Path.Combine(Path.GetDirectoryName(newFileName), newFileName);

                    // Сохранение файла
                    SaveFile(newFilePath, fileContent, saveFormat);
                    break;
                }
                else if (keyInfo.Key == ConsoleKey.Escape)
                {
                    // Завершение программы
                    return;
                }
            }
        }

        static void SaveFile(string fileName, string fileContent, string saveFormat)
        {
            string extension = Path.GetExtension(fileName)?.ToLower();

            if (saveFormat == "txt")
            {
                // Сохранение файла в формате txt
                File.WriteAllText(fileName, fileContent);
            }

            else if (saveFormat == "xml")
            {
                // Сохранение файла в формате xml
                using (var writer = XmlWriter.Create(fileName))
                {
                    writer.WriteStartElement("Data");
                    writer.WriteRaw(fileContent);
                    writer.WriteEndElement();
                }
            }
            else
            {
                Console.WriteLine("Неподдерживаемый формат файла для сохранения.");
            }

            Console.WriteLine("Файл успешно сохранен.");
        }
    }
}