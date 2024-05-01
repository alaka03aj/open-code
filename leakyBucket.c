// Simulation of Leaky Bucket in C

#include <stdio.h>

void main(){
    int bucketSize, rate, input, bucketInput = 0, i = 0;
    printf("Enter the number of inputs: ");
    scanf("%d", &i);
    printf("Enter the bucket size: ");
    scanf("%d", &bucketSize);
    printf("Enter the rate of transmission: ");
    scanf("%d", &rate);

    while (i!=0){
        printf("\nIncoming packet size: ");
        scanf("%d", &input);
        if (input <= (bucketSize - bucketInput)){
            bucketInput += input;
            printf("\nBucket buffer after adding: %d", bucketInput);
        }
        else{
            printf("\nPacket loss: %d", input - (bucketSize - bucketInput));
            bucketInput = bucketSize;
        }
        bucketInput -= rate;
        printf("\nBucket status after transmission: %d of %d", bucketInput, bucketSize);
        i--;
    }
}
