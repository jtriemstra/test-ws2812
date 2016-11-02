using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.IO;


namespace SerialPortTest
{
    class Program
    {
        static void Main(string[] args)
        {
            SerialPort mySerialPort = new SerialPort( "COM4", 9600);
            mySerialPort.Open();

            while (true)
            { 
                String s = Console.ReadLine();
                if (s.Equals("h")){
                    mySerialPort.Write(new byte[] { 1 }, 0, 1);
                }
                else if (s.Equals("l"))
                {
                    mySerialPort.Write(new byte[] { 0 }, 0, 1);
                }
            }
        }
    }
}
