#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int ack() {
    return rand() % 2;  // Random 0 or 1
}

int main() {
    int n, ws, wt;
    int i, j;
    
    srand(time(0));

    printf("Packets to send: ");
    scanf("%d", &n);
    printf("Window size: ");
    scanf("%d", &ws);
    printf("Wait time: ");
    scanf("%d", &wt);

    int sent[n + 1]; // 1-based indexing
    for (i = 1; i <= n; i++) {
        sent[i] = 0; // 0 = not yet ACKed
    }

    i = 1;
    while (i <= n) {
        // Send packets in current window
        for (j = 0; j < ws && i + j <= n; j++) {
            int pkt = i + j;
            if (sent[pkt] == 0) {
                printf("Sending packet %d...\n", pkt);
                sleep(1);
            }
        }

        // Check ACKs
        for (j = 0; j < ws && i + j <= n; j++) {
            int pkt = i + j;
            if (sent[pkt] == 0) {
                if (ack()) {
                    printf("ACK received for packet %d\n", pkt);
                    sent[pkt] = 1;
                } else {
                    printf("ACK lost for packet %d! Will retry after %d sec\n", pkt, wt);
                }
            }
        }

        // Slide window forward past ACKed packets
        while (sent[i] == 1 && i <= n) {
            i++;
        }

        // Wait before resending any lost packets
        if (i <= n) {
            sleep(wt);
        }
    }

    printf("All packets sent successfully with Selective Repeat!\n");
    return 0;
}
