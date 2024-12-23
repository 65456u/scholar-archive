# Simple DNS Relay Server

## Compilation

To compile the DNS Relay Server, follow these steps:

```shell
# Create the build directory
mkdir build
# Enter the build directory
cd build
# Generate the makefile
cmake ..
# Use the makefile to compile
make
```

The resulting compiled binary executable file is named `dns_server` (or `dns_server.exe` in Windows).

## Running the Server

### Command Line Arguments

The program accepts command line arguments in the following format:

```
dns_server [-d] [-dd] [-s DNS_SERVER_ADDRESS] [-f FILENAME]
```

- `-d`: An optional argument indicating that the debug level should be set to 1.
- `-dd`: An optional argument indicating that the debug level should be set to 2.
- `-s DNS_SERVER_ADDRESS`: An optional argument used to specify the IP address of the DNS server.
- `-f FILENAME`: An optional argument used to specify the filename that contains static DNS entries.

### Administrator Privilege

The DNS Relay Server needs to bind to port 53, which is the standard port for DNS. Binding to this port requires administrator privilege. Therefore, when running the server, make sure you have the necessary administrative privileges to successfully bind to port 53.

For example, in Ubuntu, you can use the following command with `sudo`:

```shell
sudo ./dns_server
```

In Windows, you need to open the command prompt with administrative privileges. To do this, right-click on the Command Prompt icon and select "Run as administrator". Then, navigate to the location of the server executable and run it from the elevated command prompt.

## Acknowledgements

This program utilizes the `uthash` library, a lightweight hash table implementation in C. `uthash` is developed by Troy D. Hanson and is available at: [https://github.com/troydhanson/uthash](https://github.com/troydhanson/uthash).

We would like to express our gratitude to Troy D. Hanson for creating and sharing this useful library, which significantly contributed to the functionality of our Simple DNS Relay Server.
