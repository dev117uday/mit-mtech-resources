#include <stdio.h>

#define NUM_SEGMENTS 5
#define SEGMENT_SIZE 1024

// Segment Table Entry
typedef struct
{
    int base;
    int limit;
} SegmentEntry;

// Segment Table
SegmentEntry segmentTable[NUM_SEGMENTS];

void initializeSegmentTable()
{
    // Set base and limit for each segment
    segmentTable[0].base = 1400;
    segmentTable[0].limit = 1000;

    segmentTable[3].base = 3200;
    segmentTable[3].limit = 1100;

    segmentTable[2].base = 4300;
    segmentTable[2].limit = 400;

    segmentTable[4].base = 4700;
    segmentTable[4].limit = 1000;

    segmentTable[1].base = 6300;
    segmentTable[1].limit = 6700;
}

int convertLogicalToPhysical(int segment, int offset)
{
    if (segment < 0 || segment >= NUM_SEGMENTS)
    {
        printf("Invalid segment number.\n");
        return -1;
    }

    if (offset < 0 || offset >= segmentTable[segment].base + segmentTable[segment].limit)
    {
        printf("Invalid offset for the segment.\n");
        return -1;
    }

    return segmentTable[segment].base + offset;
}

int main()
{
    initializeSegmentTable();

    // Compute physical addresses for specific byte offsets
    int address1 = convertLogicalToPhysical(2, 53);
    int address2 = convertLogicalToPhysical(3, 852);
    int address3 = convertLogicalToPhysical(0, 1222);

    // Print the computed physical addresses
    printf("Physical address for (i) 53 byte of segment 2: %d\n", address1);
    printf("Physical address for (ii) 85 byte of segment 3: %d\n", address2);
    printf("Physical address for (iii) 1222 byte of segment 0: %d\n", address3);

    return 0;
}
