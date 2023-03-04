using System.Diagnostics;
using System.Runtime.CompilerServices;

internal class Program
{
    private static void Main(string[] args)
    {
        var data = Read();
        Console.WriteLine("{hello:aaa}");
        //Console.ReadKey();
        Process.Start("notepad");
    }

    private static string Read()
    {
        var stdin = Console.OpenStandardInput();
        if (stdin == System.IO.Stream.Null) return "";

        var length = 0;

        var lengthBytes = new byte[4];
        stdin.Read(lengthBytes, 0, 4);
        length = BitConverter.ToInt32(lengthBytes, 0);

        var buffer = new char[length];
        using (var reader = new StreamReader(stdin))
        {
            while (reader.Peek() >= 0)
            {
                reader.Read(buffer, 0, buffer.Length);
            }
        }

        return new string(buffer);
    }
}