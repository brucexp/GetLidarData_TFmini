#include <iostream>
#include "WzSerialPort.h"

/*
	���ߣ�xp
	���ڣ�2023-4-14
	��;��ʹ��C++��ȡ�״�����
	ʾ����
		�ο� getLidarData()
*/

using namespace std;

void sendDemo()
{
	WzSerialPort w;
	if (w.open("COM1", 9600, 0, 8, 1))
	{
		for (int i = 0; i < 10; i++)
		{
			w.send("helloworld", 10);
		}
		cout << "send demo finished...";
	}
	else
	{
		cout << "open serial port failed...";
	}
}

typedef struct {
	int distance;
	int strength;
	int temp;
	bool receiveComplete;
} TF;

TF Lidar = { 0, 0, 0, false };

void getLidarData(TF* lidar)
{
	static int i = 0;
	int j = 0;
	int checksum = 0;
	static char rx[9];
	WzSerialPort w;
	w.open("COM4", 115200, 0, 8, 1);
	while (true)
	{
		int checksum = 0;
		w.receive(rx, 9);
		/*
		if (rx[0] != 0x59)
		{
			i = 0;
			std::cout << "-----------------------��ȡ����ʧ��1---------------------"<<std::endl;
		}
		else if (i == 1 && rx[1] != 0x59) {
			i = 0;
			std::cout << "-----------------------��ȡ����ʧ��2---------------------" << std::endl;
		}
		else if (i == 8)
		{
			//std::cout << "------------------------3---------------------" << std::endl;
			for (j = 0; j < 8; j++)
			{
				//std::cout << "rx["<<j<<"]"<< (int)rx[j] << std::endl;
				checksum += rx[j];
			}
			//std::cout <<"checksum:"<< checksum << std::endl;
			if (rx[8] == (checksum % 256))
			{
				lidar->distance = rx[2] + rx[3] * 256;
				lidar->strength = rx[4] + rx[5] * 256;
				lidar->temp = (rx[6] + rx[7] * 256) / 8 - 256;
				lidar->receiveComplete = true;
				std::cout << "Distance:"<<lidar->distance<<"cm\t"<<"Strength:"<<lidar->strength<<"\t"<<"Temp:"<<lidar->temp<<std::endl;
			}
			i = 0;
		}
		else
		{
			i++;
		}
		*/
		if (rx[0] == 0x59 && (rx[1] == 0x59)) {
			for (j = 0; j < 8; j++)
			{
				//std::cout << "rx["<<j<<"]"<< (int)rx[j] << std::endl;
				checksum += rx[j];
			}
			//std::cout <<"checksum:"<< checksum << std::endl;
			if (rx[8] == (checksum % 256))
			{
				lidar->distance = rx[2] + rx[3] * 256;
				lidar->strength = rx[4] + rx[5] * 256;
				lidar->temp = (rx[6] + rx[7] * 256) / 8 - 256;
				lidar->receiveComplete = true;
				std::cout << "Distance:" << lidar->distance << "cm\t" << "Strength:" << lidar->strength << "\t" << "Temp:" << lidar->temp << std::endl;
			}
		
		}
		else {
			std::cout << "---------------------��������ʧ��4-------------" << std::endl;
			w.close();
			w.open("COM4", 115200, 0, 8, 1);
			std::cout << "---------------------���´򿪶˿�-------------" << std::endl;
		}


	}
}/*���Ƚ��״������9λ���ݰ�˳�����롮rx[]�������У�����������ľ��롢�ź�ǿ�ȡ��¶�*/


int main(int argumentCount, const char* argumentValues[])
{
	// ����COM1�Ѿ�������һ���������Ӻ���

	// ���� demo
	//sendDemo();

	// ���� demo
	getLidarData(&Lidar);

	return 0;
}
