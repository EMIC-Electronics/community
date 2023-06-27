# Printer Driver
## Description
This API allows printing data in ticket format. The API contains only one method responsible for sending the data to the printer.

## Details
- `void pPrinter(char* format, ...)`: This method is responsible for sending the provided string as a parameter to the printer in order to generate a new ticket.

# Changelog
## Version 1.0.0 - Initial Release:
### Description
For this initial version, we started from what was available in the previous version of the EMIC system (repository `Interpreted`), then we adapted the code to be compatible with the new version and the use of current resources, while maintaining consistency with other communication systems such as USB or the EMIC Bus.

### Changes
- The use of the interpreter and its resources (ptr_param, n_parama, etc.) has been removed.
- The method pPrinter now utilizes Stream structures to process data for sending.
- The data is transmitted directly from the pPrinter method rather than the poll function.