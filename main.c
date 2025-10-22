#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max_city 50
#define Max_character 40
#define Fuel_cost 310

int takingCityName(char cityName[Max_city][Max_character]);
void displayCities(char cityName[Max_city][Max_character], int count);
int renameCity(char cityName[Max_city][Max_character], int count);
int deleteCityName(char cityName[Max_city][Max_character], int *count);
void takingDistance(char cityName[Max_city][Max_character],int distanceCity[Max_city][Max_city],int count);
void displayDistanceTable(char cityName[Max_city][Max_character], int distanceCity[Max_city][Max_city], int count);
int editCityDistance(char cityName[Max_city][Max_character], int distanceCity[Max_city][Max_city], int count);
void calcDeliveryCost(char cityName[Max_city][Max_character], int distanceCity[Max_city][Max_city], int count);

int main()
{
    char cityName[Max_city][Max_character];
    int cityCount=takingCityName(cityName);
    int distanceCity[Max_city][Max_city];
    displayCities(cityName,cityCount);
    renameCity(cityName, cityCount);
    deleteCityName(cityName,&cityCount);
    takingDistance(cityName,distanceCity,cityCount);
    displayDistanceTable(cityName,distanceCity,cityCount);
    editCityDistance(cityName,distanceCity,cityCount);
    calcDeliveryCost(cityName,distanceCity,cityCount);


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
        renameCity(cityName, count); // recall safely
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
        deleteCityName(cityName,count);
        // recall safely
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
        printf("❌ Invalid city numbers! Please enter different valid city indices.\n");
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

void calcDeliveryCost(char cityName[Max_city][Max_character], int distanceCity[Max_city][Max_city], int count)
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

}









