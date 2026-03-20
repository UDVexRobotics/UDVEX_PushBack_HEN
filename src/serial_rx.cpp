/**
 * @file serial_rx.cpp
 *
 * @brief This file contains the implementation for receiving
 *    serial data from an external device (e.g., Raspberry Pi)
 *
 * @author Michael Earley @MEarley
 *
 * @date 2026-03-20
 *
 */

#include "serial_rx.hpp"
#include <cstddef>
#include <iostream>

namespace // Anonymous namespace for internal linkage
{

bool rxIsAvailable = false;

/**
* @brief Task function for receiving serial data
*/
void SerialRx_Task(void *arg) {
  static_cast<void>(arg); // Unused parameter

  constexpr int kSerialPort = SERIAL_PORT;
  constexpr int kBaudRate = BAUD_RATE;
  constexpr size_t kBufferSize = SERIAL_BUFFER_SIZE;
  constexpr size_t kMaxQueueSize = MAX_SERIAL_MSG_QUEUE_SIZE;

  std::cout << "T=Rx" << std::endl;

  // Initialize Serial Communication
  pros::Serial serial(SERIAL_PORT, BAUD_RATE);

  // Flush the serial buffer to prevent old data from being read
  serial.flush();

  // Find a way to determine if rx is available. For now, we will assume it is always available after initialization
  rxIsAvailable = true;

  while (rxIsAvailable) {

    // Check if data is available to read
    size_t availableBytes = serial.get_read_avail();
    if (availableBytes > 0) {
      // Limit the number of bytes to read to the buffer size
      if (availableBytes > kBufferSize) {
        availableBytes = kBufferSize;
      }
      
      // Create a message struct and store data
      SerialRx::SerialMsg_t msg;
      msg.length = availableBytes;
      serial.read(msg.data, availableBytes);

      // Push the received message to the queue for processing later
      SerialRx::serialMsgQueue.push(msg);
      
      if(SerialRx::serialMsgQueue.size() < kMaxQueueSize)
      {
        SerialRx::serialMsgQueue.push(msg);
      }
      else {
      std::cout << "ERROR: RX FULL" << std::endl;
      }
      
    }
    pros::delay(20);
  }

  std::cout << "ERROR: Rx is not available" << std::endl;
  // If we exit the loop, it means serial communication is no longer available
  while (true) {
    pros::delay(10000);
  }
}
} // namespace

namespace SerialRx {

/**
* @brief Initializes the Serial RX Task
*/
void SerialRx_TaskInit(void) {
  pros::Task serialRxTask(SerialRx_Task, nullptr, TASK_PRIORITY_DEFAULT + 1,
                          TASK_STACK_DEPTH_DEFAULT, "Serial RX Task");
  return;
}

/**
* @brief Checks if serial data is available to be read
* @note Currently assumed available
*/
bool isAvailable(void) { return rxIsAvailable; }

} // namespace SerialRx