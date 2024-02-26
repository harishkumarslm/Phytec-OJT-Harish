#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

// Function to parse GPGGA sentence and extract latitude and longitude
void parseGPGGA(char *sentence, double *latitude, double *longitude) {
    char *token = strtok(sentence, ",");
    int count = 1;

    while (token != NULL) {
        if (count == 2) {
            *latitude = atof(token);
        } else if (count == 4) {
            *longitude = atof(token);
        }

        token = strtok(NULL, ",");
        count++;
    }
}

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
    int bytesRead;

    while (1) {
        bytesRead = read(fd, buffer, sizeof(buffer));
        buffer[bytesRead] = '\0';

        // Check if the received data contains GPGGA sentence
        if (strstr(buffer, "$GPGGA")) {
            double latitude, longitude;
            parseGPGGA(buffer, &latitude, &longitude);

            printf("Latitude: %f, Longitude: %f\n", latitude, longitude);
        }
    }

    close(fd);

    return 0;
}

