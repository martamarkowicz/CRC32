# CRC32
Program adds CRC32 to the file and checks the integrity of data.
In order to determine the CRC32, 32 zeroed bits are added to the data string, and then we divide the entire file by the generating polynomial, which in this case will be 33 bits (the divisor is n+1 bits). The remainder of the division is our CRC32. Then we append the determined CRC value to the file. To check the integrity of the data in the file with the added CRC, we use the division function again and if the remainder of the division is 0, the data integrity has not been compromised.
