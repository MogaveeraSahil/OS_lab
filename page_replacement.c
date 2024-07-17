#include <stdio.h>
// Function to check if the page is present in the frames
int isPagePresent(int frames[], int n, int page) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == page) {
            return 1;
        }
    }
    return 0;
}
// Function to print the frames
void printFrames(int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] != -1) {
            printf("%d ", frames[i]);
        } else {
            printf("- ");
        }
    }
    printf("\n");
}
// Function to implement FIFO page replacement
void fifoPageReplacement(int pages[], int numPages, int numFrames) {
    int frames[numFrames];
    int front = 0, pageFaults = 0;
    // Initialize frames
    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1;
    }
    printf("FIFO Replacement\n");
    printf("Reference String\tFrames\n");
    for (int i = 0; i < numPages; i++) {
        printf("%d\t\t", pages[i]);
        if (!isPagePresent(frames, numFrames, pages[i])) {
            frames[front] = pages[i];
            front = (front + 1) % numFrames;
            pageFaults++;
        }
        printFrames(frames, numFrames);
    }
    printf("\nTotal Page Faults: %d\n\n", pageFaults);
}
// Function to find the page to replace using the Optimal page replacement
// algorithm
int findOptimalReplacementIndex(int pages[], int numPages, int frames[],
                                int numFrames, int currentIndex) {
    int farthest = currentIndex;
    int index = -1;
    for (int i = 0; i < numFrames; i++) {
        int j;
        for (j = currentIndex; j < numPages; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        // If the page is not found in future, return this index
        if (j == numPages) {
            return i;
        }
    }
    // If all pages are found in future, return the one with farthest future use
    return (index == -1) ? 0 : index;
}
// Function to implement Optimal page replacement
void optPageReplacement(int pages[], int numPages, int numFrames) {
    int frames[numFrames];
    int pageFaults = 0;
    // Initialize frames
    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1;
    }
    printf("Optimal Replacement\n");
    printf("Reference String\tFrames\n");
    for (int i = 0; i < numPages; i++) {
        printf("%d\t\t", pages[i]);
        if (!isPagePresent(frames, numFrames, pages[i])) {
            if (isPagePresent(frames, numFrames, -1)) {
                for (int j = 0; j < numFrames; j++) {
                    if (frames[j] == -1) {
                        frames[j] = pages[i];
                        break;
                    }
                }
            } else {
                int index = findOptimalReplacementIndex(pages, numPages, frames,
                                                        numFrames, i + 1);
                frames[index] = pages[i];
            }
            pageFaults++;
        }
        printFrames(frames, numFrames);
    }
    printf("\nTotal Page Faults: %d\n\n", pageFaults);
}
// Function to implement LRU page replacement
void lruPageReplacement(int pages[], int numPages, int numFrames) {
    int frames[numFrames];
    int pageFaults = 0;
    int timestamps[numFrames];
    // Initialize frames and timestamps
    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1;
        timestamps[i] = -1;
    }
    printf("LRU Replacement\n");
    printf("Reference String\tFrames\n");
    for (int i = 0; i < numPages; i++) {
        printf("%d\t\t", pages[i]);
        if (!isPagePresent(frames, numFrames, pages[i])) {
            int lruIndex = 0;
            for (int j = 1; j < numFrames; j++) {
                if (timestamps[j] < timestamps[lruIndex]) {
                    lruIndex = j;
                }
            }
            frames[lruIndex] = pages[i];
            timestamps[lruIndex] = i;
            pageFaults++;
        } else {
            for (int j = 0; j < numFrames; j++) {
                if (frames[j] == pages[i]) {
                    timestamps[j] = i;
                    break;
                }
            }
        }
        printFrames(frames, numFrames);
    }
    printf("\nTotal Page Faults: %d\n\n", pageFaults);
}
int main() {
    int numFrames, numPages;
    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);
    printf("Enter the number of pages: ");
    scanf("%d", &numPages);
    int pages[numPages];
    printf("Enter the reference string: ");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }
    fifoPageReplacement(pages, numPages, numFrames);
    optPageReplacement(pages, numPages, numFrames);
    lruPageReplacement(pages, numPages, numFrames);
    return 0;
}