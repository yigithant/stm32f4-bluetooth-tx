#include "stm32f4xx.h"                  // Device header

#include <stdio.h>

char metin[30]="frsfd";//gönderilecek metin 	
void initBluetooth(void);//bluetooth configleri ayarlandigi fonksiyon
void sendBluetoothChar(char item);//bilginin gönderilecegi fonksiyon

int secim=0;
int main(){
	
	
	initBluetooth();//bluetooth config burda çagriliyor ve yapiliyor
	while(1)
	{

	
		for(uint16_t i=0;i<18;i++)
		{
		sendBluetoothChar(metin[i]);//bilgi burda teker teker gönderiliyor
		}
		
	
	}

}



void initBluetooth(void)
{
	GPIO_InitTypeDef GPIOStruct;
	USART_InitTypeDef UsartStruct;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	

	GPIOStruct.GPIO_Mode=GPIO_Mode_AF;
	GPIOStruct.GPIO_Pin=GPIO_Pin_5;
	GPIOStruct.GPIO_OType=GPIO_OType_PP;
	GPIOStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIOStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIOStruct);
	
	
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
	
	
	UsartStruct.USART_BaudRate=9600;
	UsartStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	UsartStruct.USART_Mode=USART_Mode_Tx;
	UsartStruct.USART_Parity=USART_Parity_No;
	UsartStruct.USART_StopBits=USART_StopBits_1;
	UsartStruct.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART2,&UsartStruct);
	

	
	/*NVIC_InitTypeDef NVICStruct;
	NVICStruct.NVIC_IRQChannel=USART2_IRQn;
	NVICStruct.NVIC_IRQChannelCmd=ENABLE;
	NVICStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVICStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVICStruct);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	*/
	USART_Cmd(USART2,ENABLE);
}



void sendBluetoothChar(char item)
{
	
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET){}
	USART_SendData(USART2, (uint16_t)item);
}





	
