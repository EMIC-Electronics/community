# GPS 
## Description
This API contains the interface to read and configure the GPS module.

## Details
The information getting from the GPS is represented in five variables:
- `Latitude`: Represents the current latitude of the GPS.
- `Longitude`: Represents the current longitude of the GPS.
- `Altitude`: Represents the current altitude of the GPS.
- `n_sat`: Contains the number of satellites that the GPS detect.
- `Valid_data`: Indicates if the last data given by the GPS is valid.

# Changelog

## Version 1.0.0 - Initial Release:
### Description
For this initial version, we started from what was available in the previous version of the EMIC system (repository `Interpreted`), then we adapted the code to be compatible with the new version and the use of current resources.

### Changes
- The use of the interpreter and its resources (ptr_param, n_parama, etc.) has been removed.
  