//C Libraty headers
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Linux headers
#include <unistd.h> //write(), read(), close()
#include <fcntl.h> // Contains file controls like O_RDWR
#include <termios.h> // Contains POSIX terminal control definitions
#include <errno.h> // Error integer and strerror() function

volatile int fd, lenT, lenR;
char textReceive[255], textTransmit[255];
bool flagSerial;

int open_serial(){
    fd = open("/dev/ttyUSB0", O_RDWR);
    // check for errors
    if (fd < 0){
        printf("Error %i from open: %s\n", errno, strerror(errno));
    }
    
    /* Set up Serial port */
    struct termios tty;
    if(tcgetattr(fd, &tty) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    }

    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);

    tty.c_cc[VTIME] = 10;
    tty.c_cc[VMIN] = 0;

    cfsetspeed(&tty, B115200);
    // Save tty settings, also checking for error
    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        return -1;
    }
    printf("Open Port: OK !!!!!\n");
    return 0;
    
}

int transmitData(){
    /* Write to serial port */
    printf("*****************AT Command*****************\n");
    printf("Transmit:\n");
    memset(textTransmit, 0, sizeof(textTransmit));
    scanf("%s",textTransmit);
    lenT = sprintf(textTransmit, "%s\r", textTransmit);
    write(fd, textTransmit, lenT);

    return 0;
}

int receiveData(){
    /* Receive from serial port */
    memset(textReceive, 0 , sizeof(textReceive));
    read(fd, textReceive, sizeof(textReceive));
    lenR = strlen(textReceive);
    if (lenR < 0){
        printf("Error reading: %s\n", strerror(errno));
        return -1;
    }
    else if (lenR > 0)
    {
       printf("Received:\n%s\n", textReceive);
        return 0;
    }
}


int main(){
    open_serial();
    while (1)
    {
        if(transmitData() == 0){
            receiveData();
        }
    }
    return 0;
}