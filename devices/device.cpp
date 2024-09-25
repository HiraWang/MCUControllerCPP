#include "device.h"

SerialPort::SerialPort(const wchar_t* port_name,
					   DWORD baud_rate,
					   BYTE byte_size,
					   BYTE stop_bits,
					   BYTE parity) :
					   port_name(port_name),
					   baud_rate(baud_rate),
					   byte_size(byte_size),
					   stop_bits(stop_bits),
					   parity(parity)
{

}

SerialPort::~SerialPort()
{

}