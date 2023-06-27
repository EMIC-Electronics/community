# Bluetooth (without BLE)
## Description
This API contains all the functions to control a Bluetooth chip using AT commands through the UART port.

The interface has one method used to send data via Bluetooth and one event that is triggered when our module receives data through Bluetooth.

## Details
- `void pBlth(char* format, ...)`: This method is responsible for sending the provided string as a parameter via Bluetooth.
- `extern void eBlth(char* tag, const streamIn* getBlth)`: This event is triggered when new data arrives via Bluetooth. The message includes a header *tag* with a maximum limit of 20 characters, while *getBlth* is a structure that contains all the characters of the message and information on how to access it.

# Changelog
## Version 1.0.0 - Initial Release:
### Description
For this initial version, we started from what was available in the previous version of the EMIC system (repository `Interpreted`), then we adapted the code to be compatible with the new version and the use of current resources, while maintaining consistency with other communication systems such as USB or the EMIC Bus.

### Changes
- The use of the interpreter and its resources (ptr_param, n_parama, etc.) has been removed.
- The mechanism to send hexadecimal values has been removed. This data format is now compatible with the use of StreamIn and StreamOut structures.
- The method gBlth, which was used to read messages from Bluetooth, has been deleted.
- The method pBlth now utilizes Stream structures to process data for sending.
- The event eBlth now returns the received message via Bluetooth as a parameter. 