using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.IO;

namespace SerialPortTest2
{
    class Program
    {
        const int STRING_LENGTH = 40;

        static void Main(string[] args)
        {
            int loopCount = 0;
            bool blnIncrement = true;

            SerialPort mySerialPort = new SerialPort("COM4", 9600);
            mySerialPort.Open();

            Console.ReadLine();

            while (true)
            {
                for (int i = 0; i < STRING_LENGTH; i++)
                {
                    if (i >= loopCount && i < loopCount + 3) mySerialPort.Write(new byte[] { 255 }, 0, 1);
                    else mySerialPort.Write(new byte[] { 0 }, 0, 1);
                }

                if (blnIncrement) loopCount++;
                else loopCount--;

                if (loopCount > STRING_LENGTH - 3 && blnIncrement) blnIncrement = false;
                else if (loopCount < 0 && !blnIncrement) blnIncrement = true;

                System.Threading.Thread.Sleep(100);
            }
        }
    }
}
