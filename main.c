#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max_city 50
#define Max_character 40

int takingCityName(char cityName[Max_city][Max_character]);
void displayCities(char cityName[Max_city][Max_character], int count);
int renameCity(char cityName[Max_city][Max_character], int count);

int main()
{
    char cityName[Max_city][Max_character];
    int cityCount=takingCityName(cityName);
   displayCities(cityName,cityCount);
   renameCity(cityName, cityCount);
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
