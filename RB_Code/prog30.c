#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

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

    char buffer[12];
    int bytesRead = read(fd, buffer, sizeof(buffer));
    buffer[bytesRead] = '\0';

    printf("RFID Tag UID: %s\n", buffer);

    // Assuming PC13 is connected to the LED
    int led_fd = open("/sys/class/gpio/gpio13/value", O_WRONLY);
    if (led_fd == -1) {
        perror("Error opening LED control file");
        close(fd);
        return -1;
    }

    if (strcmp(buffer, "TAG1") == 0) {
        write(led_fd, "1", 1);
        sleep(2);  // Wait for 2 seconds
        write(led_fd, "0", 1);
    } else if (strcmp(buffer, "TAG2") == 0) {
        // Control PC17
        // ...
    } else if (strcmp(buffer, "TAG3") == 0) {
        // Control PC19
        // ...
    }

    close(fd);
    close(led_fd);

    return 0;
}

