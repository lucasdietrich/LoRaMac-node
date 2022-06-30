/*!
 * \file      LmHandlerMsgDisplay.h
 *
 * \brief     Common set of functions to display default messages from
 *            LoRaMacHandler.
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \code
 *                ______                              _
 *               / _____)             _              | |
 *              ( (____  _____ ____ _| |_ _____  ____| |__
 *               \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 *               _____) ) ____| | | || |_| ____( (___| | | |
 *              (______/|_____)_|_|_| \__)_____)\____)_| |_|
 *              (C)2013-2019 Semtech
 *
 * \endcode
 *
 * \author    Miguel Luis ( Semtech )
 */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "utilities.h"
#include "timer.h"

#include "logging.h"
#define LOG_LEVEL LOG_LEVEL_DBG

#include "LmHandlerMsgDisplay.h"

/*!
 * MAC status strings
 */
const char* MacStatusStrings[] =
{
    "OK",                            // LORAMAC_STATUS_OK
    "Busy",                          // LORAMAC_STATUS_BUSY
    "Service unknown",               // LORAMAC_STATUS_SERVICE_UNKNOWN
    "Parameter invalid",             // LORAMAC_STATUS_PARAMETER_INVALID
    "Frequency invalid",             // LORAMAC_STATUS_FREQUENCY_INVALID
    "Datarate invalid",              // LORAMAC_STATUS_DATARATE_INVALID
    "Frequency or datarate invalid", // LORAMAC_STATUS_FREQ_AND_DR_INVALID
    "No network joined",             // LORAMAC_STATUS_NO_NETWORK_JOINED
    "Length error",                  // LORAMAC_STATUS_LENGTH_ERROR
    "Region not supported",          // LORAMAC_STATUS_REGION_NOT_SUPPORTED
    "Skipped APP data",              // LORAMAC_STATUS_SKIPPED_APP_DATA
    "Duty-cycle restricted",         // LORAMAC_STATUS_DUTYCYCLE_RESTRICTED
    "No channel found",              // LORAMAC_STATUS_NO_CHANNEL_FOUND
    "No free channel found",         // LORAMAC_STATUS_NO_FREE_CHANNEL_FOUND
    "Busy beacon reserved time",     // LORAMAC_STATUS_BUSY_BEACON_RESERVED_TIME
    "Busy ping-slot window time",    // LORAMAC_STATUS_BUSY_PING_SLOT_WINDOW_TIME
    "Busy uplink collision",         // LORAMAC_STATUS_BUSY_UPLINK_COLLISION
    "Crypto error",                  // LORAMAC_STATUS_CRYPTO_ERROR
    "FCnt handler error",            // LORAMAC_STATUS_FCNT_HANDLER_ERROR
    "MAC command error",             // LORAMAC_STATUS_MAC_COMMAD_ERROR
    "ClassB error",                  // LORAMAC_STATUS_CLASS_B_ERROR
    "Confirm queue error",           // LORAMAC_STATUS_CONFIRM_QUEUE_ERROR
    "Multicast group undefined",     // LORAMAC_STATUS_MC_GROUP_UNDEFINED
    "Unknown error",                 // LORAMAC_STATUS_ERROR
};

/*!
 * MAC event info status strings.
 */
const char* EventInfoStatusStrings[] =
{ 
    "OK",                            // LORAMAC_EVENT_INFO_STATUS_OK
    "Error",                         // LORAMAC_EVENT_INFO_STATUS_ERROR
    "Tx timeout",                    // LORAMAC_EVENT_INFO_STATUS_TX_TIMEOUT
    "Rx 1 timeout",                  // LORAMAC_EVENT_INFO_STATUS_RX1_TIMEOUT
    "Rx 2 timeout",                  // LORAMAC_EVENT_INFO_STATUS_RX2_TIMEOUT
    "Rx1 error",                     // LORAMAC_EVENT_INFO_STATUS_RX1_ERROR
    "Rx2 error",                     // LORAMAC_EVENT_INFO_STATUS_RX2_ERROR
    "Join failed",                   // LORAMAC_EVENT_INFO_STATUS_JOIN_FAIL
    "Downlink repeated",             // LORAMAC_EVENT_INFO_STATUS_DOWNLINK_REPEATED
    "Tx DR payload size error",      // LORAMAC_EVENT_INFO_STATUS_TX_DR_PAYLOAD_SIZE_ERROR
    "Address fail",                  // LORAMAC_EVENT_INFO_STATUS_ADDRESS_FAIL
    "MIC fail",                      // LORAMAC_EVENT_INFO_STATUS_MIC_FAIL
    "Multicast fail",                // LORAMAC_EVENT_INFO_STATUS_MULTICAST_FAIL
    "Beacon locked",                 // LORAMAC_EVENT_INFO_STATUS_BEACON_LOCKED
    "Beacon lost",                   // LORAMAC_EVENT_INFO_STATUS_BEACON_LOST
    "Beacon not found"               // LORAMAC_EVENT_INFO_STATUS_BEACON_NOT_FOUND
};

void DisplayNvmDataChange( LmHandlerNvmContextStates_t state, uint16_t size )
{
    if ( state == LORAMAC_HANDLER_NVM_STORE )
    {
        LOG_INF( "-- [ NVM CTXS STORED ] size=%i", size);
    }
    else
    {
        LOG_INF( "-- [ NVM CTXS RESTORED ] size=%i", size);
    }
}

void DisplayNetworkParametersUpdate( CommissioningParams_t *commissioningParams )
{
    LOG_INF_BEG( "DevEui : " );
    LOG_HEXDUMP_INF( commissioningParams->DevEui, 8 );

    LOG_INF_BEG( "JoinEui : " );
    LOG_HEXDUMP_INF( commissioningParams->JoinEui, 8 );

    LOG_INF_BEG( "Pin : " );
    LOG_HEXDUMP_INF( commissioningParams->SePin, 4 );
}

void DisplayMacMcpsRequestUpdate( LoRaMacStatus_t status, McpsReq_t *mcpsReq, TimerTime_t nextTxIn )
{
    switch( mcpsReq->Type )
    {
        case MCPS_CONFIRMED:
        {
            LOG_INF_BEG( "-- [ MCPS-Request - MCPS_CONFIRMED]");
            break;
        }
        case MCPS_UNCONFIRMED:
        {
            LOG_INF_BEG( "-- [ MCPS-Request - MCPS_UNCONFIRMED]");
            break;
        }
        case MCPS_PROPRIETARY:
        {
            LOG_INF_BEG( "-- [ MCPS-Request - MCPS_PROPRIETARY]");
            break;
        }
        default:
        {
            LOG_INF_BEG( "-- [ MCPS-Request - MCPS_ERROR]" );
            break;
        }
    }

    LOG_INF_RAW("  status=%s Next Tx in= %lu ms\n", MacStatusStrings[status], nextTxIn);
}

void DisplayMacMlmeRequestUpdate( LoRaMacStatus_t status, MlmeReq_t *mlmeReq, TimerTime_t nextTxIn )
{
    switch( mlmeReq->Type )
    {
        case MLME_JOIN:
        {
            LOG_INF_BEG( "-- [ MCPS-Request - MLME_JOIN]" );
            break;
        }
        case MLME_LINK_CHECK:
        {
            LOG_INF_BEG( "-- [ MCPS-Request - MLME_JOIN]" );
            break;
        }
        case MLME_DEVICE_TIME:
        {
            LOG_INF_BEG( "-- [ MCPS-Request - MLME_DEVICE_TIME]" );
            break;
        }
        case MLME_TXCW:
        {
            LOG_INF_BEG( "-- [ MCPS-Request - MLME_TXCW]" );
            break;
        }
        default:
        {
            LOG_INF_BEG( "-- [ MCPS-Request - MLME_UNKNOWN]" );
            break;
        }
    }

    LOG_INF_RAW("  status=%s Next Tx in= %lu ms\n", MacStatusStrings[status], nextTxIn);
}

void DisplayJoinRequestUpdate( LmHandlerJoinParams_t *params )
{
    if( params->CommissioningParams->IsOtaaActivation == true )
    {
        if ( params->Status == LORAMAC_HANDLER_SUCCESS )
        {
            LOG_INF( "-- [ JOINED ]  OTAA DevAddr=%08lX DR_%d",
                     params->CommissioningParams->DevAddr, params->Datarate );
        }
    }
#if ( OVER_THE_AIR_ACTIVATION == 0 )
    else
    {
        LOG_INF( "-- [ JOINED ] ABP DevAddr=%08lX",
                 params->CommissioningParams->DevAddr );
    }
#endif
}

void DisplayTxUpdate( LmHandlerTxParams_t *params )
{
    MibRequestConfirm_t mibGet;

    if( params->IsMcpsConfirm == 0 )
    {
        LOG_INF( "-- [ MLME-Confirm ]  status=%s", EventInfoStatusStrings[params->Status] );
        return;
    }

    LOG_INF( "-- [ MCPS-Confirm ]  status=%s",
             EventInfoStatusStrings[ params->Status ] );
    LOG_INF( "-- [ UPLINK FRAME ]  counter=%lu class=%c port=%u",
             params->UplinkCounter, "ABC"[ LmHandlerGetCurrentClass() ],
             params->AppData.Port );

    if ( params->AppData.BufferSize != 0 )
    {
        if ( params->MsgType == LORAMAC_HANDLER_CONFIRMED_MSG )
        {
            LOG_INF_BEG( "\tTX DATA CONFIRMED - %s : ", ( params->AckReceived != 0 ) ? "ACK" : "NACK" );
        }
        else
        {
            LOG_INF_BEG( "\tTX DATA UNCONFIRMED : " );
        }
        LOG_HEXDUMP_INF( params->AppData.Buffer, params->AppData.BufferSize );
    }

    mibGet.Type  = MIB_CHANNELS;
    uint32_t frequency = 0;
    if( LoRaMacMibGetRequestConfirm( &mibGet ) == LORAMAC_STATUS_OK )
    {
        frequency = mibGet.Param.ChannelList[params->Channel].Frequency;
    }

    uint16_t chan = 0;

    mibGet.Type  = MIB_CHANNELS_MASK;
    if( LoRaMacMibGetRequestConfirm( &mibGet ) == LORAMAC_STATUS_OK )
    {
        switch( LmHandlerGetActiveRegion( ) )
        {
            case LORAMAC_REGION_AS923:
            case LORAMAC_REGION_CN779:
            case LORAMAC_REGION_EU868:
            case LORAMAC_REGION_IN865:
            case LORAMAC_REGION_KR920:
            case LORAMAC_REGION_EU433:
            case LORAMAC_REGION_RU864:
            {
                chan = mibGet.Param.ChannelsMask[0];
                break;
            }
            case LORAMAC_REGION_AU915:
            case LORAMAC_REGION_CN470:
            case LORAMAC_REGION_US915:
            {
                LOG_WRN("Unsupported region");
                break;
            }
            default:
            {
                LOG_ERR( "Unknown region" );
                break;
            }
        }
    }

    LOG_INF( "\tDR_%u frequency=%lu power=%d channel mask=%u",
             params->Datarate, frequency, params->TxPower, chan );
}

void DisplayRxUpdate( LmHandlerAppData_t *appData, LmHandlerRxParams_t *params )
{
    const char *slotStrings[] = { "1", "2", "C", "C Multicast", "B Ping-Slot", "B Multicast Ping-Slot" };

    if( params->IsMcpsIndication == 0 )
    {
        LOG_INF( "-- [ MLME-Indication ]  status=%s",
                     EventInfoStatusStrings[ params->Status ] );
        return;
    }

    LOG_INF( "-- [ MCPS-Indication ]  status=%s",
             EventInfoStatusStrings[ params->Status ] );

    LOG_INF( "-- [ DOWNLINK FRAME ]  counter=%lu window=%s port=%d",
             params->DownlinkCounter, slotStrings[ params->RxSlot ],
             appData->Port );

    if( appData->BufferSize != 0 )
    {
        LOG_INF_BEG( "\tRX DATA : " );
        LOG_HEXDUMP_INF( appData->Buffer, appData->BufferSize );
    }

    LOG_INF( "\tDR_%d rssi=%d snr=%d",
             params->Datarate, params->Rssi, params->Snr );
}

void DisplayBeaconUpdate( LoRaMacHandlerBeaconParams_t *params )
{
    switch( params->State )
    {
        default:
        case LORAMAC_HANDLER_BEACON_ACQUIRING:
        {
            LOG_INF("-- [ BEACON ACQUIRING ]");
            break;
        }
        case LORAMAC_HANDLER_BEACON_LOST:
        {
            LOG_INF("-- [ BEACON LOST ]");
            break;
        }
        case LORAMAC_HANDLER_BEACON_RX:
        {
            LOG_INF_BEG( "-- [ BEACON ] time sec=%lu GW DESC=%u INFO=",
                     params->Info.Time.Seconds, params->Info.GwSpecific.InfoDesc );
            LOG_HEXDUMP_INF( params->Info.GwSpecific.Info, 6 );

            LOG_INF("\tfreq=%lu DR_%u rssi=%d snr=%d",
                     params->Info.Frequency, params->Info.Datarate,
                     params->Info.Rssi, params->Info.Snr );
            break;
        }
        case LORAMAC_HANDLER_BEACON_NRX:
        {
            LOG_WRN( "-- [ BEACON BEACON NOT RECEIVED ]" );
            break;
        }
    }
}

void DisplayClassUpdate( DeviceClass_t deviceClass )
{
    LOG_INF( "-- [ Switch to class %c done ]", "ABC"[ deviceClass ] );
}