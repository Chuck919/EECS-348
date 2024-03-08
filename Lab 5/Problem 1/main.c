#include <stdio.h>
#include <stdlib.h>

#define MONTHS 12

// Function to find the minimum value and its index in an array
void findMin(float arr[], int n, float *min, int *minIndex) {
    *min = arr[0];
    *minIndex = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < *min) {
            *min = arr[i];
            *minIndex = i;
        }
    }
}

// Function to find the maximum value and its index in an array
void findMax(float arr[], int n, float *max, int *maxIndex) {
    *max = arr[0];
    *maxIndex = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] > *max) {
            *max = arr[i];
            *maxIndex = i;
        }
    }
}

// Function to calculate the average of an array of floats
float calculateAverage(float arr[], int n) {
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum / n;
}

// Function to generate the six-month moving averages
void generateMovingAverages(float sales[], float movingAverages[], int n) {
    for (int i = 0; i <= n - 6; i++) {
        float sum = 0;
        for (int j = i; j < i + 6; j++) {
            sum += sales[j];
        }
        movingAverages[i] = sum / 6;
    }
}

// Function to sort the sales and months arrays in descending order of sales
void sortSales(float sales[], char *months[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (sales[j] < sales[j + 1]) {
                // Swap sales
                float tempSales = sales[j];
                sales[j] = sales[j + 1];
                sales[j + 1] = tempSales;

                // Swap months
                char *tempMonth = months[j];
                months[j] = months[j + 1];
                months[j + 1] = tempMonth;
            }
        }
    }
}

// Function to print the sales report
void printSalesReport(float sales[], char *months[], char *title) {
    printf("%s\n\n", title);
    printf("Month\t\tSales\n");
    for (int i = 0; i < MONTHS; i++) {
        printf("%-10s\t$%.2f\n", months[i], sales[i]);
    }
    printf("\n");
}

// Function to print the sales summary
void printSalesSummary(float sales[], char *months[]) {
    float minSales, maxSales, avgSales;
    int minIndex, maxIndex;
    
    findMin(sales, MONTHS, &minSales, &minIndex);
    findMax(sales, MONTHS, &maxSales, &maxIndex);
    avgSales = calculateAverage(sales, MONTHS);
    
    printf("Sales summary:\n");
    printf("Minimum sales: $%.2f (%s)\n", minSales, months[minIndex]);
    printf("Maximum sales: $%.2f (%s)\n", maxSales, months[maxIndex]);
    printf("Average sales: $%.2f\n\n", avgSales);
}

// Function to print the six-month moving average report
void printMovingAverage(float movingAverages[], char *months[]) {
    printf("Six-Month Moving Average Report:\n");
    for (int i = 0; i <= MONTHS - 6; i++) {
        printf("%-10s - %-10s\t$%.2f\n", months[i], months[i + 5], movingAverages[i]);
    }
    printf("\n");
}

int main() {
    FILE *fp;
    char *fileName = "input";
    float sales[MONTHS];
    float movingAverages[MONTHS - 5];
    char *months[] = {"January", "February", "March", "April", "May", "June", 
                      "July", "August", "September", "October", "November", "December"};
    
    // Open the file for reading
    fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    
    // Read sales data from the file
    for (int i = 0; i < MONTHS; i++) {
        if (fscanf(fp, "%f", &sales[i]) != 1) {
            printf("Error reading sales data.\n");
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    
    // Generate the six-month moving averages
    generateMovingAverages(sales, movingAverages, MONTHS);
    
    // Generate and print the reports
    printSalesReport(sales, months, "Monthly sales report:");
    printSalesSummary(sales, months);
    printMovingAverage(movingAverages, months);
    
    // Sort sales data in descending order and print the sales report
    sortSales(sales, months, MONTHS);
    printSalesReport(sales, months, "Sales Report (Highest to Lowest):");
    
    return 0;
}