/**
* @file serial_rx.hpp
*
* @brief This file contains the implementation for receiving 
*    serial data from an external device (e.g., Raspberry Pi)
*
* @author Michael Earley @MEarley
*
* @date 2026-03-20
*
*/

#ifndef SERIAL_RX_HPP
#define SERIAL_RX_HPP

#include "config.hpp"
#include <queue>

#define BAUD_RATE 250000 // Baud rate for serial communication
#define SERIAL_BUFFER_SIZE 64 // Size of the buffer for incoming serial data
#define MAX_SERIAL_MSG_QUEUE_SIZE 7 // Maximum number of messages to store in the queue

namespace SerialRx
{
    struct SerialMsg_t
    {
        uint8_t data[SERIAL_BUFFER_SIZE]; // Buffer to hold incoming data
        size_t length;    // Length of the received data
    };

// Queue to hold received messages
    inline std::queue<SerialMsg_t> serialMsgQueue; 
    
    bool isAvailable(void);
    void SerialRx_TaskInit(void);
}

#endif // SERIAL_RX_HPP