#include<iostream>
#include<fstream>

using namespace std;

int division(fstream &input_string) {
    unsigned int buffer = 0;
    unsigned char byte;
    unsigned int polynomial = 0x04C11DB7;
    while (true) {
        byte = input_string.get();
        if (!input_string.good()) break;
        int i = 0;
        while (i < 8) {
            if ((buffer & 0x80000000) == 0x00000000) {
                buffer <<= 1;
                buffer |= ((byte & 0x80) >> 7);
                byte <<= 1;
            } else if ((buffer & 0x80000000) == 0x80000000) {
                buffer <<= 1;
                buffer |= ((byte & 0x80) >> 7);
                buffer = buffer ^ polynomial;
                byte <<= 1;
            }
            i++;
        }
    }
    for (int j = 0; j < 32; j++) {
        if ((buffer & 0x80000000) == 0x00000000) {
            buffer <<= 1;
        } else if ((buffer & 0x80000000) == 0x80000000) {
            buffer <<= 1;
            buffer = buffer ^ polynomial;
        }
    }
    return buffer;
}

//function that writes crc to a file
void saveCRC(unsigned int CRC32, fstream &file) {
    //We write to the file as 4 bytes
    unsigned char byte;
    unsigned int crc;
    crc = CRC32;
    for(int i = 0; i < 4; i++) {
        byte = ((crc&0xFF000000)>>24);
        file << byte;
        crc <<= 8; }
    file << endl;
    return;
}

int main()
{
    fstream file;
    char file_name[32];
    printf("Enter the name of the file with the extension: ");
    scanf("%s", file_name);
    file.open(file_name);
    int crc=division(file);
    printf("CRC: %#x\n", crc);
    saveCRC(crc, file);
    printf("Validation of the file\n");
    int remainder=division(file);
    printf("Calculated remainder: %#x\n", remainder);
    if(remainder==0) printf("Data integrity has not been compromised\n");
    else
        printf("Data integrity has been compromised\n");

    file.close();
}
