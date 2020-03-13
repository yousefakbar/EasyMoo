/******************************************************************************
* File Name: BLE.h
*
* Version: Beta
*
* Description: This file contains the firmware for setting up communication
* between the PSoC and the AS73211 True Color Sensor using the I2C protocol.
*
* Related Document: TrueColor_LightSensor.pdf
* Hardware Dependency:  CY8CKIT-063-BLE PSoC 6 BLE Pioneer kit
*                       AS73211 True Color Sensor
*
* Author(s):
*	Yousef H. Akbar & and Cow Team
*	Dept. Electrical and Computer Engineering
*	University of California, Davis
******************************************************************************/
#include "stdio.h"
#include "project.h"

uint16_t xChannel, yChannel, zChannel, temperature;	// Light Sensor Vars
uint16_t accX, accY, accZ;				// Accelerometer
uint16_t gyroX, gyroY, gyroZ;				// Gyroscope
int tempFlag;
int accInactive;
int lightFlag;
static uint8 data[1] = {0};

void genericEventHandler(uint32_t event, void *eventParameter)
{
    switch(event)
    {
        case CY_BLE_EVT_STACK_ON:
        case CY_BLE_EVT_GAP_DEVICE_DISCONNECTED:
        {
            Cy_BLE_GAPP_StartAdvertisement(CY_BLE_ADVERTISING_FAST, CY_BLE_PERIPHERAL_CONFIGURATION_0_INDEX);
            break;
        }
        case CY_BLE_EVT_GATT_CONNECT_IND:
        {
            break;
        }
        case CY_BLE_EVT_GATTS_WRITE_CMD_REQ:
        {
            cy_stc_ble_gatts_write_cmd_req_param_t *writeReqParameter = (cy_stc_ble_gatts_write_cmd_req_param_t *) eventParameter;
            
            if (CY_BLE_DEVICE_INTERFACE_DEVICE_INBOUND_CHAR_HANDLE == writeReqParameter->handleValPair.attrHandle)
            {
                data[0] = writeReqParameter->handleValPair.value.val[0];
                Cy_BLE_GATTS_WriteRsp(writeReqParameter->connHandle);
            }
            break;
        }
    }
}
void bleInterruptNotify()
{
    Cy_BLE_ProcessEvents();
}
void broadcastBLE(int happy_score)
{
    Cy_BLE_Start(genericEventHandler);
    uint8_t BLE_data[] = { 0x00, 0x00, 'G', gyroX, gyroY, gyroZ, 'L', xChannel, yChannel, zChannel, 'A', accX, accY, accZ, 'T', temperature, 'C', lightFlag, tempFlag, accInactive, 'H', happy_score, 0x00, 0x00 };
    
    while (Cy_BLE_GetState() != CY_BLE_STATE_ON)
    {
        Cy_BLE_ProcessEvents();
    }
    Cy_BLE_RegisterAppHostCallback(bleInterruptNotify);

    for(int i = 0; i < 24; i++)
    {
        printf("Broadcasting BLE Data!\r\n");
        
        cy_stc_ble_gatt_handle_value_pair_t serviceHandle;
        cy_stc_ble_gatt_value_t serviceData;
        
        serviceData.val = (uint8*)data;
        serviceData.len = 1;
        
        serviceHandle.attrHandle = CY_BLE_DEVICE_INTERFACE_DEVICE_OUTBOUND_CHAR_HANDLE;
        serviceHandle.value = serviceData;
        
        Cy_BLE_GATTS_WriteAttributeValueLocal(&serviceHandle);
        
        data[0] = BLE_data[i];
        CyDelay(1000);

    }
    Cy_BLE_Stop();
}

