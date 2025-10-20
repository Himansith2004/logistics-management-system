#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max_city 50
#define Max_character 40

int takingCityName(char cityName[Max_city][Max_character]);
void displayCities(char cityName[Max_city][Max_character], int count);
int renameCity(char cityName[Max_city][Max_character], int count);
int deleteCityName(char cityName[Max_city][Max_character], int *count);
void takingDistance(char cityName[Max_city][Max_character],int distanceCity[Max_city][Max_city],int count);
void displayDistanceTable(char cityName[Max_city][Max_character], int distanceCity[Max_city][Max_city], int count);

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
}

int takingCityName(char cityName[Max_city][Max_character])
{
    int count=0;
    char choice;

    for(int i=0;i<Max_city;i++)
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
    printf("Enter the number of the city you want to rename (1–%d): ", count);
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
    printf("Enter the number of the city you want to Delete (1–%d): ", count);
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
    for(i;i<*count-1;i++)
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
    for(int i=0;i<count;i++)
    {
        for(int j=0;j<count;j++)
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
    printf("%15s", "");
    for (int i = 0; i < count; i++)
    {
        printf("%15s", cityName[i]);
    }
    printf("\n");
    for (int i = 0; i < count; i++)
    {
        printf("%15s", cityName[i]);
        for (int j = 0; j < count; j++)
        {
            printf("%15d", distanceCity[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
