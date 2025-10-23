#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max_city 50
#define Max_character 40
#define Fuel_cost 310
#define Max_deliveries 50
#define Delivery_fields 6

int takingCityName(char cityName[Max_city][Max_character]);
void displayCities(char cityName[Max_city][Max_character], int count);
int renameCity(char cityName[Max_city][Max_character], int count);
int deleteCityName(char cityName[Max_city][Max_character], int *count);
void takingDistance(char cityName[Max_city][Max_character],int distanceCity[Max_city][Max_city],int count);
void displayDistanceTable(char cityName[Max_city][Max_character], int distanceCity[Max_city][Max_city], int count);
int editCityDistance(char cityName[Max_city][Max_character], int distanceCity[Max_city][Max_city], int count);
void calcDeliveryCost(char cityName[Max_city][Max_character], int distanceCity[Max_city][Max_city], int count,float deliveries[][6],int *deliveryCount);
void viewAllDeliveries(char cityName[Max_city][Max_character],float deliveries[Max_deliveries][6], int deliveryCount);

int main()
{
    char cityName[Max_city][Max_character];
    int distanceCity[Max_city][Max_city];
    float deliveries[Max_deliveries][Delivery_fields];
    int deliveryCount = 0;

    int cityCount = takingCityName(cityName);
    takingDistance(cityName, distanceCity, cityCount);
    displayDistanceTable(cityName, distanceCity, cityCount);

    int choice;
    do {
        printf("\n========== MAIN MENU ==========\n");
        printf("1. Display Cities\n");
        printf("2. Rename City\n");
        printf("3. Delete City\n");
        printf("4. Edit City Distance\n");
        printf("5. Calculate Delivery Cost\n");
        printf("6. View All Deliveries\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice)
        {
            case 1:
                displayCities(cityName, cityCount);
                displayDistanceTable(cityName, distanceCity, cityCount);
                break;

            case 2:
                renameCity(cityName, cityCount);
                displayCities(cityName, cityCount);
                displayDistanceTable(cityName, distanceCity, cityCount);
                break;

            case 3:
                deleteCityName(cityName, &cityCount);
                displayCities(cityName, cityCount);
                displayDistanceTable(cityName, distanceCity, cityCount);
                break;

            case 4:
                editCityDistance(cityName, distanceCity, cityCount);
                displayDistanceTable(cityName, distanceCity, cityCount);
                break;

            case 5:
                calcDeliveryCost(cityName, distanceCity, cityCount,deliveries, &deliveryCount);
                break;

            case 6:
                viewAllDeliveries(cityName, deliveries, deliveryCount);
                break;

            case 0:
                printf("\nExiting program...\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}



int takingCityName(char cityName[Max_city][Max_character])
{
    int count=0;
    char choice;

    for(int i=0; i<Max_city; i++)
    {
        printf("Enter the %d city: ",i+1);
        fgets(cityName[i],Max_character,stdin);
        cityName[i][strcspn(cityName[i], "\n")] = '\0';
        count++;
        printf("Enter \"y\" if you want to and another city otherwise \"n\": ");
        scanf(" %c",&choice);
        if(choice == 'n')
        {
            printf("All the cities have been entered.");
            break;
        }
        else if((choice !='y')&&(choice !='n'))
        {
            printf("THE ENTERED NUMBER is not correct!!");
            break;
        }
        getchar();
    }
    return count;
}

void displayCities(char cityName[Max_city][Max_character], int count)
{
    printf("\nList of Cities:\n");
    for (int i = 0; i < count; i++)
    {
        printf("%d. %s\n", i + 1, cityName[i]);
    }
}

int renameCity(char cityName[Max_city][Max_character], int count)
{
    int keyNum;
    printf("Enter the number of the city you want to rename : ");
    scanf("%d", &keyNum);
    getchar();
    if (keyNum <= 0 || keyNum > count)
    {
        printf("Invalid number! Please try again.\n");
        return renameCity(cityName, count);
    }
    int keyN = keyNum - 1;
    printf("Enter the new name of the city: ");
    fgets(cityName[keyN], Max_character, stdin);
    cityName[keyN][strcspn(cityName[keyN], "\n")] = '\0';
    printf("City renamed successfully!\n");
    displayCities(cityName, count);

    return 0;
}

int deleteCityName(char cityName[Max_city][Max_character], int *count)
{
    int keyNum;
    printf("Enter the number of the city you want to Delete : ");
    scanf("%d", &keyNum);
    getchar();
    if (keyNum <= 0 || keyNum > count)
    {
        printf("Invalid number! Please try again.\n");
        return deleteCityName(cityName,count);
    }
    int keyN = keyNum - 1;

    int i=keyN;
    for(i; i<*count-1; i++)
    {

        strcpy(cityName[i],cityName[i+1]);
    }
    (*count)--;
    printf("City deleted successfully!\n");
    displayCities(cityName,*count);

}

void takingDistance(char cityName[Max_city][Max_character],int distanceCity[Max_city][Max_city],int count)
{
    printf("\n--- Enter Distances Between Cities ---\n");
    for(int i=0; i<count; i++)
    {
        for(int j=0; j<count; j++)
        {
            if (i == j)
            {
                distanceCity[i][j] = 0;
                break;
            }
            printf("Enter distance between %s and %s (in km): ", cityName[i], cityName[j]);
            scanf("%d", &distanceCity[i][j]);
            distanceCity[j][i] = distanceCity[i][j];
        }
    }
    printf("\nAll distances recorded successfully!\n");
}

void displayDistanceTable(char cityName[Max_city][Max_character], int distanceCity[Max_city][Max_city], int count)
{
    printf("\n\n===== Distance Table (in km) =====\n\n");
    printf("%-5s", "");
    for (int i = 0; i < count; i++)
    {
        printf("%-15s", cityName[i]);
    }
    printf("\n");
    for (int i = 0; i < (count + 1) * 15; i++)
        printf("-");
    printf("\n");
    for (int i = 0; i < count; i++)
    {
        printf("%-15s", cityName[i]);
        for (int j = 0; j < count; j++)
        {
            printf("%-15d", distanceCity[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int editCityDistance(char cityName[Max_city][Max_character], int distanceCity[Max_city][Max_city], int count)
{
    int i, j, newDistance;

    printf("\nEnter the numbers of two cities to edit the distance between them:\n");
    printf("Enter the number of the first city : ");
    scanf("%d", &i);
    printf("Enter the number of the second city: ");
    scanf("%d", &j);

    if (i <= 0 || j <= 0 || i > count || j > count || i == j)
    {
        printf("Invalid city numbers! Please enter different valid city indices.\n");
        return 0;
    }
    printf("Enter the new distance between %s and %s (in km): ",cityName[i - 1], cityName[j - 1]);
    scanf("%d", &newDistance);
    distanceCity[i - 1][j - 1] = newDistance;
    distanceCity[j - 1][i - 1] = newDistance;

    printf(" Distance between %s and %s updated successfully!\n",cityName[i - 1], cityName[j - 1]);
    displayDistanceTable(cityName, distanceCity, count);

    return 0;
}

void calcDeliveryCost(char cityName[Max_city][Max_character], int distanceCity[Max_city][Max_city], int count,float deliveries[][6],int *deliveryCount)
{
    char *vehicleType[] = {"Van", "Truck", "Lorry"};
    int capacity[] = {1000, 5000, 10000};
    float rate[] = {30, 40, 80};
    float speed[] = {60, 50, 45};
    float efficiency[] = {12, 6, 4};

    displayCities(cityName, count);
    int src, dest, vType;
    float weight;
    printf("\nEnter source city number: ");
    scanf("%d", &src);
    printf("Enter destination city number: ");
    scanf("%d", &dest);
    printf("Enter delivery weight (kg): ");
    scanf("%f", &weight);
    printf("Select vehicle type (1=Van, 2=Truck, 3=Lorry): ");
    scanf("%d", &vType);
    if (src <= 0 || dest <= 0 || src > count || dest > count || src == dest)
    {
        printf("\nInvalid city selection! Source and destination must be different.\n");
        return;
    }

    if (vType < 1 || vType > 3)
    {
        printf("\nInvalid vehicle type selection!\n");
        return;
    }

    if (weight > capacity[vType - 1])
    {
        printf("\nWeight exceeds the capacity of the selected vehicle (%d kg max)!\n", capacity[vType - 1]);
        return;
    }

    float distance = distanceCity[src - 1][dest - 1];
    float rateOfCost = rate[vType - 1];
    float speedOfVehicle = speed[vType - 1];
    float fuelEffi = efficiency[vType - 1];
    float fuelPrice=Fuel_cost;
    float baseCost = distance*rateOfCost*(1+(weight/capacity[vType - 1]));
    float fuelUsed = distance/fuelEffi;
    float fuelCost = fuelUsed*fuelPrice;
    float operationalCost = baseCost+fuelCost;
    float profit = operationalCost*0.25;
    float customerCharge = operationalCost + profit;
    float estTime = distance/speedOfVehicle;

    printf("\n======================================================\n");
    printf("DELIVERY COST ESTIMATION\n");
    printf("------------------------------------------------------\n");
    printf("From: %s\n", cityName[src - 1]);
    printf("To: %s\n", cityName[dest - 1]);
    printf("Minimum Distance: %.2f km\n", distance);
    printf("Vehicle: %s\n", vehicleType[vType - 1]);
    printf("Weight: %.2f kg\n", weight);
    printf("------------------------------------------------------\n");
    printf("Base Cost: %.0f x %.0f x (1 + %.0f/%.0f) = %.2f LKR\n",distance, rateOfCost, weight, (float)capacity[vType - 1], baseCost);
    printf("Fuel Used: %.2f L\n", fuelUsed);
    printf("Fuel Cost: %.2f LKR\n", fuelCost);
    printf("Operational Cost: %.2f LKR\n", operationalCost);
    printf("Profit: %.2f LKR\n", profit);
    printf("Customer Charge: %.2f LKR\n", customerCharge);
    printf("Estimated Time: %.2f hours\n", estTime);
    printf("======================================================\n");

    if (*deliveryCount < Max_deliveries)
{
    deliveries[*deliveryCount][0] = src - 1;        // source city index
    deliveries[*deliveryCount][1] = dest - 1;       // destination city index
    deliveries[*deliveryCount][2] = distance;       // distance
    deliveries[*deliveryCount][3] = estTime;        // delivery time
    deliveries[*deliveryCount][4] = customerCharge; // total charge (revenue)
    deliveries[*deliveryCount][5] = profit;         // profit
    (*deliveryCount)++;

    printf("\nDelivery record saved successfully! Total deliveries: %d\n", *deliveryCount);
}
else
{
    printf("\n⚠Maximum of %d deliveries reached.\n", Max_deliveries);
}

}

void viewAllDeliveries(char cityName[Max_city][Max_character],float deliveries[Max_deliveries][6], int deliveryCount)
{
    if (deliveryCount == 0) {
        printf("\nNo deliveries recorded yet.\n");
        return;
    }
    printf("\n================= DELIVERY RECORDS =================\n");
    for (int i = 0; i < deliveryCount; i++) {
        int src = (int)deliveries[i][0];
        int dest = (int)deliveries[i][1];
        float distance = deliveries[i][2];
        float time = deliveries[i][3];
        float revenue = deliveries[i][4];
        float profit = deliveries[i][5];

        printf("%d. %s to %s | Distance: %.2f km | Time: %.2f h | Revenue: %.2f LKR | Profit: %.2f LKR\n",i + 1, cityName[src], cityName[dest], distance, time, revenue, profit);
    }
    printf("====================================================\n");
}









