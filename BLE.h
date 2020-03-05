/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

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
void broadcastBLE(void)
{
    Cy_BLE_Start(genericEventHandler);
    
    while (Cy_BLE_GetState() != CY_BLE_STATE_ON)
    {
        Cy_BLE_ProcessEvents();
    }
    Cy_BLE_RegisterAppHostCallback(bleInterruptNotify);

    for(;;)
    {
        /* Place your application code here. */
        
        cy_stc_ble_gatt_handle_value_pair_t serviceHandle;
        cy_stc_ble_gatt_value_t serviceData;
        
        serviceData.val = (uint8*)data;
        serviceData.len = 1;
        
        serviceHandle.attrHandle = CY_BLE_DEVICE_INTERFACE_DEVICE_OUTBOUND_CHAR_HANDLE;
        serviceHandle.value = serviceData;
        
        Cy_BLE_GATTS_WriteAttributeValueLocal(&serviceHandle);
        
        data[0] = 0xEA;
        CyDelay(1000);
    }
}

/* [] END OF FILE */
