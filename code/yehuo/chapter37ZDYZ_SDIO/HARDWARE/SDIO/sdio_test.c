#include "sdio_test.h"

#include "bsp_eval_sdio_sd.h"
#include "led.h"
#include "usart.h"

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus; 

#define BLOCK_SIZE 				512	// Bloack Size in Bytes
#define NUMBER_OF_BLOCKS 	100 // For Multi Bolcks operation (read/write)
#define NULTI_BUFFER_SIZE (BLOCK_SIZE * NUMBER_OF_BLOCKS)

volatile TestStatus EraseStatus = FAILED, TransferStatus1 = FAILED, TransferStatus2 = FAILED;

SD_Error Status = SD_OK;

uint8_t Buffer_Block_Tx[BLOCK_SIZE], Buffer_Block_Rx[BLOCK_SIZE];
uint8_t Buffer_MultiBlock_Tx[NULTI_BUFFER_SIZE], Buffer_MultiBlock_Rx[NULTI_BUFFER_SIZE];

void Fill_Buffer(uint8_t *pBuffer, uint32_t BufferLength, uint32_t offset);
void SD_EraseTest(void);
void SD_SingleBlockTest(void);
void SD_MultiBlockTest(void);
TestStatus eBufferCmp(uint8_t* pBuffer, uint32_t BufferLength);
TestStatus BufferCmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength);

void SD_Test(void)
{
	LED0 = 0;
	/*------------ SD Init -------------*/
	if((Status = SD_Init()) != SD_OK){
		LED1 = 0;
		printf("SD卡测试失败,请确保SD卡已正确插接入开发板，或换一张SD卡测试\r\n");
		return;
	} 
	
	printf("SD卡初始化成功！ \r\n");
	
	//LED0 = 0;
	
	// 擦除测试
	SD_EraseTest();
	//LED0 = 0;
	
	// single block 读写测试
	SD_SingleBlockTest();
	
	// mutil block 读写测试
	SD_MultiBlockTest();

	
    // Write operation as described in Section C
	/*
    Status = SD_WriteBlock(buffer, address, 512);
    Status = SD_WaitWriteOperation();
    while(SD_GetStatus() != SD_TRANSFER_OK);

    Status = SD_WriteMultiBlocks(buffer, address, 512, NUMBEROFBLOCKS);
    Status = SD_WaitWriteOperation();
    while(SD_GetStatus() != SD_TRANSFER_OK);

    // Read operation as described in Section B
    Status = SD_ReadBlock(buffer, address, 512);
    Status = SD_WaitReadOperation();
    while(SD_GetStatus() != SD_TRANSFER_OK);

    Status = SD_ReadMultiBlocks(buffer, address, 512, NUMBEROFBLOCKS);
    Status = SD_WaitReadOperation();
    while(SD_GetStatus() != SD_TRANSFER_OK);
		*/
}

/**
* @brief Test the SD card erase operation 
* @param None
* @param None
*/
void SD_EraseTest(void)
{
	if(Status == SD_OK){
		Status = SD_Erase(0x00, (BLOCK_SIZE * NUMBER_OF_BLOCKS));
	}
	
	if(Status != SD_OK){
		printf("SD erase failed!\r\n");
		return;
	}

	// Read operation
	Status = SD_ReadMultiBlocks(Buffer_Block_Rx, 0x00, 512, NUMBER_OF_BLOCKS);
	Status = SD_WaitReadOperation();
	while(SD_GetStatus() != SD_TRANSFER_OK);
	
	if(Status != SD_OK){
		printf("SD erase failed, SD read error!\r\n");
		return;
	}
	
	EraseStatus = eBufferCmp(Buffer_Block_Rx, NUMBER_OF_BLOCKS);
	if(EraseStatus == PASSED){
		// green Led on
		printf("SD card EraseTest success!\r\n");
	} else {
		// blue led on
		printf("SD card EraseTest failed!\r\n");
		printf("温馨提示：部分SD卡不支持擦除测试，若SD卡能通过下面的single读写测试，即表示SD卡能正常使用。\r\n");
	}
	
}

/**
* @brief  Tests the SD card Single Block operations
* @param  None
* @retval None
*/
void SD_SingleBlockTest(void)
{
	// Fill the buffer to send
	Fill_Buffer(Buffer_Block_Tx, BLOCK_SIZE, 0x320f);
	
	Status = SD_WriteBlock(Buffer_Block_Tx, 0x00, BLOCK_SIZE);
	Status = SD_WaitWriteOperation();
	while(SD_GetStatus() != SD_TRANSFER_OK);
	if(Status != SD_OK){
		printf("SD_SingleBlockTest: single block write error!\r\n");
		return ;
	}
	
	Status = SD_ReadBlock(Buffer_Block_Rx, 0x00, BLOCK_SIZE);
	Status = SD_WaitReadOperation();
	while(SD_GetStatus() != SD_TRANSFER_OK);
	if(Status != SD_OK){
		printf("SD_SingleBlockTest: single block read error!\r\n");
		return ;
	}
	
	TransferStatus1 = BufferCmp(Buffer_Block_Tx, Buffer_Block_Rx, BLOCK_SIZE);
	if(TransferStatus1 == FAILED){
		printf("SD_SingleBlockTest: test error, tx buffer value no equal rx buffer!\r\n");
		return;
	}
	
	printf("SD_SingleBlockTest: test success!");
	return;
}

/**
* @brief  Tests the SD card Multiple Block operations
* @param  None
* @retval None
*/
void SD_MultiBlockTest(void)
{
	// Fill the buffer to send
	Fill_Buffer(Buffer_MultiBlock_Tx, NULTI_BUFFER_SIZE, 0x320f);
	
	Status = SD_WriteMultiBlocks(Buffer_MultiBlock_Tx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);
	Status = SD_WaitWriteOperation();
	while(SD_GetStatus() != SD_TRANSFER_OK);
	if(Status != SD_OK){
		printf("SD_MultiBlockTest: write error!\r\n");
		return ;
	}
	
	Status = SD_ReadMultiBlocks(Buffer_MultiBlock_Rx, 0x00, BLOCK_SIZE, NUMBER_OF_BLOCKS);
	Status = SD_WaitReadOperation();
	while(SD_GetStatus() != SD_TRANSFER_OK);
	if(Status != SD_OK){
		printf("SD_MultiBlockTest: read error!\r\n");
		return ;
	}
	
	TransferStatus1 = BufferCmp(Buffer_MultiBlock_Tx, Buffer_MultiBlock_Rx, NULTI_BUFFER_SIZE);
	if(TransferStatus1 == FAILED){
		printf("SD_MultiBlockTest: test error, tx buffer value no equal rx buffer!\r\n");
		return;
	}
	
	printf("SD_MultiBlockTest: test success!");
	return;
}

/**
* @brief  Fill buffer with user predefined data 
* @param  pBuffer: pointer on the buffer to fill
* @param  BufferLength: size of the buffer to fill
* @param  offset:first value to fill on the buffer
* @retval 
*/
void Fill_Buffer(uint8_t *pBuffer, uint32_t BufferLength, uint32_t offset)
{
	uint32_t index = 0;
	
	if(pBuffer == NULL)
		return;

	for(index=0; index<BufferLength; ++index){
		pBuffer[index] = index + offset; 
	}
}	

/**
* @brief compare two buffer
*/
TestStatus BufferCmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint32_t BufferLength)
{
	while(BufferLength--){
		if(*pBuffer1++ != *pBuffer2++){
			return FAILED;
		}
	}
	return PASSED;
}


/**
* @brief Check if a buffer has all its values are equal to zero
*/
TestStatus eBufferCmp(uint8_t* pBuffer, uint32_t BufferLength)
{
	while(BufferLength--){
		if((*pBuffer != 0x00) && (*pBuffer != 0xFF)){
			return FAILED;
		}
		pBuffer ++;
	}
	
	return PASSED;
}
