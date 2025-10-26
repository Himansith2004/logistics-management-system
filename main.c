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
int deleteCityName(char cityName[Max_city][Max_character], int *count,int distanceCity[Max_city][Max_city]);
int addCityDur(char cityName[Max_city][Max_character],int distanceCity[Max_city][Max_city], int *count);
void takingDistance(char cityName[Max_city][Max_character],int distanceCity[Max_city][Max_city],int count);
void displayDistanceTable(char cityName[Max_city][Max_character], int distanceCity[Max_city][Max_city], int count);
int editCityDistance(char cityName[Max_city][Max_character], int distanceCity[Max_city][Max_city], int count);
void calcDeliveryCost(char cityName[Max_city][Max_character], int distanceCity[Max_city][Max_city], int count,float deliveries[][6],int *deliveryCount);
void viewAllDeliveries(char cityName[Max_city][Max_character],float deliveries[Max_deliveries][6], int deliveryCount);
void findingLowCostWay(char cityName[Max_city][Max_character], int distanceCity[Max_city][Max_city], int count);
void saveRoutes(char cityName[][Max_character], int distanceCity[][Max_city], int count);
int loadRoutes(char cityName[][Max_character], int distanceCity[][Max_city]);
void saveDeliveries(float deliveries[][6], int deliveryCount);
int loadDeliveries(float deliveries[][6]);

int main()
{
    char cityName[Max_city][Max_character];
    int distanceCity[Max_city][Max_city];
    float deliveries[Max_deliveries][Delivery_fields];
    int deliveryCount = 0;
    int cityCount = 0;

    printf("====== Welcome to the LOGISTICS MANAGEMENT SYSTEM ======\n\n");

    // 🔹 Load existing data if available
    cityCount = loadRoutes(cityName, distanceCity);
    deliveryCount = loadDeliveries(deliveries);

    // 🔹 If no data exists, let user input fresh cities
    if (cityCount == 0)
    {
        cityCount = takingCityName(cityName);
        takingDistance(cityName, distanceCity, cityCount);
        displayDistanceTable(cityName, distanceCity, cityCount);
    }

    int choice;
    do
    {
        printf("\n========== MAIN MENU ==========\n");
        printf("1. Display Cities\n");
        printf("2. Rename City\n");
        printf("3. Add new city\n");
        printf("4. Delete City\n");
        printf("5. Edit City Distance\n");
        printf("6. Book a Ride\n");
        printf("7. Reports\n");
        printf("8. Find Least-Cost Route Between Two Cities\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            displayCities(cityName, cityCount);
            displayDistanceTable(cityName, distanceCity, cityCount);
            break;
        case 2:
            renameCity(cityName, cityCount);
            break;
        case 3:
            addCityDur(cityName,distanceCity, &cityCount);
            break;

        case 4:
            deleteCityName(cityName, &cityCount,distanceCity);
            break;
        case 5:
            editCityDistance(cityName, distanceCity, cityCount);
            break;
        case 6:
            calcDeliveryCost(cityName, distanceCity, cityCount, deliveries, &deliveryCount);
            break;
        case 7:
            viewAllDeliveries(cityName, deliveries, deliveryCount);
            break;
        case 8:
            findingLowCostWay(cityName, distanceCity, cityCount);
            break;
        case 0:
            printf("\nSaving all data before exiting...\n");
            saveRoutes(cityName, distanceCity, cityCount);
            saveDeliveries(deliveries, deliveryCount);
            printf("All data saved successfully. Goodbye!\n");
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
    char choice[]="done";

    for(int i=0; i<Max_city; i++)
    {
        printf("Enter the %d city(Enter \"done\" if you want to finish): ",i+1);
        fgets(cityName[i],Max_character,stdin);
        cityName[i][strcspn(cityName[i], "\n")] = '\0';

        if(strcmp(cityName[i],choice)==0)
        {
            printf("All the cities have been entered.");
            break;
        }
        count++;
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

int deleteCityName(char cityName[Max_city][Max_character], int *count,int distanceCity[Max_city][Max_city])
{
    int keyNum;
    printf("Enter the number of the city you want to Delete : ");
    scanf("%d", &keyNum);
    getchar();
    if (keyNum <= 0 || keyNum > *count)
    {
        printf("Invalid number! Please try again.\n");
        return deleteCityName(cityName,count,distanceCity);
    }
    int index = keyNum - 1;

    int i=index;
    for(i; i<*count-1; i++)
    {

        strcpy(cityName[i],cityName[i+1]);
    }

    for (int i = index; i < *count - 1; i++)
    {
        for (int j = 0; j < *count; j++)
        {
            distanceCity[i][j] = distanceCity[i + 1][j];
        }
    }

     for (int i = 0; i < *count - 1; i++)
    {
        for (int j = index; j < *count - 1; j++)
        {
            distanceCity[i][j] = distanceCity[i][j + 1];
        }
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

int addCityDur(char cityName[Max_city][Max_character],int distanceCity[Max_city][Max_city], int *count)
{
    if (*count >= Max_city)
    {
        printf("Cannot add more cities. Maximum limit reached.\n");
        return *count;
    }
    getchar();
  printf("Enter the new city name: ");
    fgets(cityName[*count], Max_character, stdin);
    cityName[*count][strcspn(cityName[*count], "\n")] = '\0';


    printf("\n_Enter distance from the new city (%s) to other cities_\n", cityName[*count]);
    for (int j = 0; j < *count; j++)
    {
        printf("Enter distance between %s and %s (in km): ", cityName[*count], cityName[j]);
        scanf("%d", &distanceCity[*count][j]);
        distanceCity[j][*count] = distanceCity[*count][j];
    }
    distanceCity[*count][*count] = 0;
    (*count)++;
    printf("\nCity '%s' added successfully!\n", cityName[*count - 1]);
    displayCities(cityName, *count);
    displayDistanceTable(cityName, distanceCity, *count);
    saveRoutes(cityName, distanceCity, *count);
    printf("\nRoutes updated and saved successfully!\n");
    return 0;
}

void displayDistanceTable(char cityName[Max_city][Max_character], int distanceCity[Max_city][Max_city], int count)
{
    printf("\n\n===== Distance Table (in km) =====\n\n");
    printf("%-15s", "");
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
        deliveries[*deliveryCount][0] = src - 1;
        deliveries[*deliveryCount][1] = dest - 1;
        deliveries[*deliveryCount][2] = distance;
        deliveries[*deliveryCount][3] = estTime;
        deliveries[*deliveryCount][4] = customerCharge;
        deliveries[*deliveryCount][5] = profit;
        (*deliveryCount)++;

        printf("\nDelivery record saved successfully! Total deliveries: %d\n", *deliveryCount);
    }
    else
    {
        printf("\nMaximum of %d deliveries reached.\n", Max_deliveries);
    }

}

void viewAllDeliveries(char cityName[Max_city][Max_character],float deliveries[Max_deliveries][6], int deliveryCount)
{
    float totDistance=0.0,avgTime=0.0,totRevenue=0.0,totProfit=0.0;
    float longRoute=deliveries[0][2],shortRoute=deliveries[0][2];
    int longIndex = 0, shortIndex = 0;

    if (deliveryCount == 0)
    {
        printf("\nNo deliveries recorded yet.\n");
        return;
    }
    printf("\n================= DELIVERY RECORDS =================\n");
    for (int i = 0; i<deliveryCount; i++)
    {
        int src = (int)deliveries[i][0];
        int dest = (int)deliveries[i][1];
        float distance = deliveries[i][2];
        float time = deliveries[i][3];
        float revenue = deliveries[i][4];
        float profit = deliveries[i][5];

        printf("%d. %s to %s | Distance: %.2f km | Time: %.2f h | Revenue: %.2f LKR | Profit: %.2f LKR\n",i + 1, cityName[src], cityName[dest], distance, time, revenue, profit);
    }

    for(int i=0;i<deliveryCount;i++)
    {
        totDistance+=deliveries[i][2];
    }
     for(int i=0;i<deliveryCount;i++)
    {
        avgTime+=deliveries[i][3];
    }
     for(int i=0;i<deliveryCount;i++)
    {
        totRevenue+=deliveries[i][4];
    }
     for(int i=0;i<deliveryCount;i++)
    {
        totProfit+=deliveries[i][5];
    }
     for(int i=0;i<deliveryCount;i++)
    {
        float distance = deliveries[i][2];
        if (distance > longRoute)
        {
            longRoute = distance;
            longIndex = i;
        }
        if (distance < shortRoute)
        {
            shortRoute = distance;
            shortIndex = i;
        }
    }
    printf("\n The Total Distance-%.2f",totDistance);
    printf("\n The Average time to complete delivery-%.2f",avgTime/deliveryCount);
    printf("\n The total revenue=%.2f The total profit=%.2f",totRevenue,totProfit);
    printf("\nThe Longest Route: %s to %s ",cityName[(int)deliveries[longIndex][0]],cityName[(int)deliveries[longIndex][1]],longRoute);
    printf("\nThe Shortest Route: %s to %s ",cityName[(int)deliveries[shortIndex][0]],cityName[(int)deliveries[shortIndex][1]],shortRoute);


    printf("\n====================================================\n");
}

void findingLowCostWay(char cityName[Max_city][Max_character], int distanceCity[Max_city][Max_city], int count)
{
    int sourceCity,destinationCity;
    displayCities(cityName, count);
    printf("\nEnter the number of the source city: ");
    scanf("%d", &sourceCity);
    printf("Enter the number of the destination city: ");
    scanf("%d", &destinationCity);

    if(sourceCity<=0||destinationCity<=0||sourceCity>count||destinationCity>count||sourceCity==destinationCity)
    {
        printf("\nInvalid selection! Please choose different valid city numbers.\n");
        return;
    }
    sourceCity=sourceCity-1;
    destinationCity=destinationCity-1;

    int dist[Max_city], visited[Max_city], prev[Max_city];
    for (int i = 0; i < count; i++)
    {
        dist[i] = 999999;
        visited[i] = 0;
        prev[i] = -1;
    }
    dist[sourceCity] = 0;
    for (int i = 0; i < count - 1; i++)
    {
        int minium = 999999, u = -1;
        for (int j = 0; j < count; j++)
        {
            if (!visited[j] && dist[j] < minium)
            {
                minium = dist[j];
                u = j;
            }
        }

        if (u == -1)
            break;
        visited[u] = 1;
        for (int v = 0; v < count; v++)
        {
            if (!visited[v] && distanceCity[u][v] > 0 && dist[u] + distanceCity[u][v] < dist[v])
            {
                dist[v] = dist[u] + distanceCity[u][v];
                prev[v] = u;
            }
        }
    }
    if (dist[destinationCity] == 999999)
    {
        printf("\nNo route found between %s and %s.\n", cityName[sourceCity], cityName[destinationCity]);
        return;
    }
    printf("\n~~~~~~~ LEAST COST (DISTANCE) ROUTE ~~~~~~~\n");
    printf("From: %s\n", cityName[sourceCity]);
    printf("To: %s\n", cityName[destinationCity]);
    printf("Minimum Distance: %d km\n", dist[destinationCity]);
    int path[Max_city];
    int pathLen = 0;
    for (int v = destinationCity; v != -1; v = prev[v])
        path[pathLen++] = v;
    printf("Minium distance Route: ");
    for (int i = pathLen - 1; i >= 0; i--)
    {
        printf("%s", cityName[path[i]]);
        if (i != 0)
        {
             printf(" -> ");
        }
    }
    printf("\n=~=~=~=~=~=~=~==~=~=~=~=~=~=~==~=~=~=~=~=~=~=\n");



}


void saveRoutes(char cityName[Max_city][Max_character], int distanceCity[Max_city][Max_city], int count)
{
    FILE *f = fopen("routes.txt", "w");
    if (!f)
    {
        printf("Error: Could not save routes file!\n");
        return;
    }

    fprintf(f, "==== CITY AND ROUTE DATA ====\n");
    fprintf(f, "Number of Cities: %d\n\n", count);

    fprintf(f, "--- City List ---\n");
    for (int i = 0; i < count; i++)
    {
        fprintf(f, "%d. %s\n", i + 1, cityName[i]);
    }

    fprintf(f, "\n--- Distance Matrix (in km) ---\n");
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            fprintf(f, "%5d ", distanceCity[i][j]);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    printf("Routes saved in a readable format (routes.txt)\n");
}


int loadRoutes(char cityName[Max_city][Max_character], int distanceCity[Max_city][Max_city])
{
    FILE *f = fopen("routes.txt", "r");
    if (!f)
    {
        printf("No existing routes file found. Starting fresh.\n");
        return 0;
    }

    int count = 0;
    char line[200];

    // Skip first line
    fgets(line, sizeof(line), f);
    fscanf(f, "Number of Cities: %d\n", &count);

    // Skip blank and header lines
    fgets(line, sizeof(line), f); // blank line
    fgets(line, sizeof(line), f); // "--- City List ---"

    for (int i = 0; i < count; i++)
    {
        fgets(cityName[i], Max_character, f);
        cityName[i][strcspn(cityName[i], "\n")] = '\0';
        // Remove "1. " prefix if needed
        char *dot = strchr(cityName[i], '.');
        if (dot)
            memmove(cityName[i], dot + 2, strlen(dot + 2) + 1);
    }

    // Skip to distance matrix section
    fgets(line, sizeof(line), f); // blank
    fgets(line, sizeof(line), f); // "--- Distance Matrix ---"

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            fscanf(f, "%d", &distanceCity[i][j]);
        }
    }

    fclose(f);
    printf("Routes loaded successfully from routes.txt\n");
    return count;
}


void saveDeliveries(float deliveries[Max_deliveries][6], int deliveryCount)
{
    FILE *f = fopen("deliveries.txt", "w");
    if (!f)
    {
        printf("Error: Could not save deliveries file!\n");
        return;
    }

    fprintf(f, "==== DELIVERY HISTORY ====\n");
    fprintf(f, "Total Deliveries: %d\n\n", deliveryCount);

    fprintf(f, "%-5s %-10s %-10s %-10s %-10s %-12s %-12s\n",
            "No", "SrcIdx", "DstIdx", "Dist", "Time(h)", "Revenue(LKR)", "Profit(LKR)");
    fprintf(f, "-------------------------------------------------------------------\n");

    for (int i = 0; i < deliveryCount; i++)
    {
        fprintf(f, "%-5d %-10.0f %-10.0f %-10.2f %-10.2f %-12.2f %-12.2f\n",
                i + 1,
                deliveries[i][0],
                deliveries[i][1],
                deliveries[i][2],
                deliveries[i][3],
                deliveries[i][4],
                deliveries[i][5]);
    }

    fclose(f);
    printf("Deliveries saved in a readable format (deliveries.txt)\n");
}

int loadDeliveries(float deliveries[Max_deliveries][6])
{
    FILE *f = fopen("deliveries.txt", "r");
    if (!f)
    {
        printf("No existing deliveries file found. Starting fresh.\n");
        return 0;
    }

    int deliveryCount;
    fscanf(f, "%d\n", &deliveryCount);

    for (int i = 0; i < deliveryCount; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            fscanf(f, "%f", &deliveries[i][j]);
        }
    }

    fclose(f);
    printf("Deliveries loaded successfully from deliveries.txt\n");
    return deliveryCount;
}





