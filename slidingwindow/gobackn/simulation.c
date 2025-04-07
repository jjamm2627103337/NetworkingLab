#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int ack() {
    return rand() % 10;  // Random 0 or 1
}

int main() {
    int n, ws, wt;
    srand(time(0));

    printf("Packets to send: ");
    scanf("%d", &n);
    printf("Window size: ");
    scanf("%d", &ws);
    printf("Wait time (on failure): ");
    scanf("%d", &wt);

    int i = 1;

    while (i <= n) {
        int allAcked = 1;
        int end = (i + ws - 1 <= n) ? i + ws - 1 : n;

        printf("Sending packets %d to %d...\n", i, end);
        sleep(1);

        for (int j = i; j <= end; j++) {
            if (ack()) {
                printf("ACK received for packet %d\n", j);
            } else {
                printf("ACK lost for packet %d! Will resend from this packet.\n", j);
                i = j; // Go back to this packet
                allAcked = 0;
                break;
            }
        }

        if (allAcked) {
            i = end + 1; // Slide window
        } else {
            printf("Resending window after %d seconds...\n\n", wt);
            sleep(wt);
        }

        printf("\n");
    }

    printf("All packets sent successfully!\n");
    return 0;
}
