#include <stdio.h>

int search(int page, int frames[], int f)
{
    int i;
    for(i = 0; i < f; i++)
    {
        if(frames[i] == page)
            return 1;
    }
    return 0;
}

void printFrames(int frames[], int f)
{
    int i;

    printf("[");
    for(i = 0; i < f; i++)
    {
        if(frames[i] == -1)
            printf(" ");
        else
            printf("%d", frames[i]);

        if(i != f - 1)
            printf(" ");
    }
    printf("]\n");
}

void FIFO(int pages[], int n, int f)
{
    int frames[10];
    int i, pointer = 0, faults = 0;

    for(i = 0; i < f; i++)
        frames[i] = -1;

    printf("\n--- FIFO Page Replacement ---\n\n");

    for(i = 0; i < n; i++)
    {
        printf("Page %d -> ", pages[i]);

        if(!search(pages[i], frames, f))
        {
            frames[pointer] = pages[i];
            pointer = (pointer + 1) % f;
            faults++;
        }

        printFrames(frames, f);
    }

    printf("\nTotal Page Faults (FIFO): %d\n", faults);
}

void LRU(int pages[], int n, int f)
{
    int frames[10], recent[10];
    int i, j, least, pos, faults = 0, count = 0;

    for(i = 0; i < f; i++)
    {
        frames[i] = -1;
        recent[i] = 0;
    }

    printf("\n--- LRU Page Replacement ---\n\n");

    for(i = 0; i < n; i++)
    {
        printf("Page %d -> ", pages[i]);

        if(search(pages[i], frames, f))
        {
            for(j = 0; j < f; j++)
            {
                if(frames[j] == pages[i])
                {
                    recent[j] = ++count;
                    break;
                }
            }
        }
        else
        {
            faults++;

            for(j = 0; j < f; j++)
            {
                if(frames[j] == -1)
                {
                    frames[j] = pages[i];
                    recent[j] = ++count;
                    break;
                }
            }

            if(j == f)
            {
                least = recent[0];
                pos = 0;

                for(j = 1; j < f; j++)
                {
                    if(recent[j] < least)
                    {
                        least = recent[j];
                        pos = j;
                    }
                }

                frames[pos] = pages[i];
                recent[pos] = ++count;
            }
        }

        printFrames(frames, f);
    }

    printf("\nTotal Page Faults (LRU): %d\n", faults);
}

void Optimal(int pages[], int n, int f)
{
    int frames[10];
    int i, j, k, pos, farthest, faults = 0;

    for(i = 0; i < f; i++)
        frames[i] = -1;

    printf("\n--- Optimal Page Replacement ---\n\n");

    for(i = 0; i < n; i++)
    {
        printf("Page %d -> ", pages[i]);

        if(!search(pages[i], frames, f))
        {
            faults++;

            for(j = 0; j < f; j++)
            {
                if(frames[j] == -1)
                {
                    frames[j] = pages[i];
                    break;
                }
            }

            if(j == f)
            {
                farthest = -1;
                pos = -1;

                for(j = 0; j < f; j++)
                {
                    int found = 0;

                    for(k = i + 1; k < n; k++)
                    {
                        if(frames[j] == pages[k])
                        {
                            found = 1;

                            if(k > farthest)
                            {
                                farthest = k;
                                pos = j;
                            }

                            break;
                        }
                    }

                    if(!found)
                    {
                        pos = j;
                        break;
                    }
                }

                frames[pos] = pages[i];
            }
        }

        printFrames(frames, f);
    }

    printf("\nTotal Page Faults (Optimal): %d\n", faults);
}

int main()
{
    int n, f, i;
    int pages[50];

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    FIFO(pages, n, f);
    LRU(pages, n, f);
    Optimal(pages, n, f);

    return 0;
}
