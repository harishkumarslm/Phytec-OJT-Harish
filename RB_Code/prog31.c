#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

int main() {
    int fd;
    struct termios options;

    fd = open("/dev/ttyS3", O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1) {
        perror("Error opening the port");
        return -1;
    }

    tcgetattr(fd, &options);
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);

    options.c_cflag |= (CLOCAL | CREAD);
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

    tcsetattr(fd, TCSANOW, &options);

    char buffer[256];
    int bytesRead = read(fd, buffer, sizeof(buffer));
    buffer[bytesRead] = '\0';

    printf("GPS Data: %s\n", buffer);

    close(fd);

    return 0;
}

