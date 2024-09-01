/*
  Name: Nagham Maali
  ID: 1212312
  Sec.: 2
*/

//libraries:
/*1*/#include <stdio.h>
/*2*/#include <stdlib.h>
/*3*/#include <string.h>
/*4*/#include <limits.h>

struct Node  //to hold town and population info
{
    char town[20] ;
    int population ;
    struct Node *Next ;
    struct Node *Previous ;
};

struct MainNode  //to hold city info
{
    char city[20] ;
    struct Node *town ;  //pointer that points at towns in the same city
    struct MainNode *MainNext ;
    struct MainNode *MainPrevious ;
};

//function Definition:
/*1*/void displayMainMenu() ;
/*2*/void Open_and_Load(struct MainNode **D) ;
/*3*/void print(struct MainNode *D) ;
/*4*/void RadixSort(struct MainNode *D) ;
/*5*/void townsort(struct MainNode *D) ;
/*6*/void insertcity(struct MainNode *D) ;
/*7*/int exist(struct MainNode *D , char *city) ;
/*8*/void inserttown(struct MainNode *D) ;
/*9*/void deleteTown(struct MainNode *D) ;
/*10*/void deleteCity(struct MainNode *D) ;
/*11*/int TotalP(struct MainNode *D) ;
/*12*/int MaxP(struct MainNode *D) ;
/*13*/int MinP(struct MainNode *D) ;
/*14*/void print_districtandpopulation(struct MainNode *D) ;
/*15*/void changeP(struct MainNode *D) ;
/*16*/void save(struct MainNode *D) ;
/*17*/int districtpop(struct MainNode *district) ;

int main()
{
    printf("Hello!\n");

    int x ;
    int condition = 1 ;

    struct MainNode *D = NULL ; //the main list

    int TotalPopulation ;
    int MaxPopulation ;
    int MinPopulation ;

    while(condition == 1)
    {
        displayMainMenu() ;
        scanf("%d" , &x) ;

        if(x == 1)
        {
            Open_and_Load(&D) ;
        }
        else if(x == 2)
        {
            print(D) ;
        }
        else if(x == 3)
        {
            RadixSort(D) ;
        }
        else if(x == 4)
        {
            townsort(D) ;
        }
        else if(x == 5)
        {
            print(D) ;
        }
        else if(x == 6)
        {
            insertcity(D) ;
            printf("\n") ;
            townsort(D) ;
        }
        else if(x == 7)
        {
            inserttown(D) ;
        }
        else if(x == 8)
        {
            deleteTown(D) ;
        }
        else if(x == 9)
        {
            deleteCity(D) ;
        }
        else if(x == 10)
        {
            TotalPopulation = TotalP(D) ;
            MaxPopulation = MaxP(D) ;
            MinPopulation = MinP(D) ;

            if(TotalPopulation != 0 && MaxPopulation != 0 && MinPopulation != 0)
            {
                printf("the total population of Palestine: %d\n" , TotalPopulation) ;
                printf("Max population: %d\n" , MaxPopulation) ;
                printf("Min population: %d\n" , MinPopulation) ;
            }
            else
            {
                printf("No data!!!\n") ;
            }
        }
        else if(x == 11)
        {
            print_districtandpopulation(D) ;
        }
        else if(x == 12)
        {
            changeP(D) ;
        }
        else if(x == 13)
        {
            save(D) ;
        }
        else if(x == 14)
        {
            printf("Bye!\n") ;
            break ;
        }
        else
        {
            printf("invalid option!!!\n") ;
            printf("try again :)\n") ;
        }
    }

    return 0 ;
}

void displayMainMenu()
{
    printf("please select an option(1-14):\n") ;
    printf("1. Load the input file (Palestinian districts and their town with population).\n") ;
    printf("2. Print the loaded information before sorting.\n") ;
    printf("3. Sort the districts alphabetically using Radix sort.\n") ;
    printf("4. Sort the towns for each district based on population in ascending order.\n") ;
    printf("5. Print the sorted information.\n") ;
    printf("6. Add a new district to the list of sorted districts (and sort the list)\n") ;
    printf("7. Add a new town to a certain district.\n") ;
    printf("8. Delete a town from a specific district.\n") ;
    printf("9. Delete a complete district.\n") ;
    printf("10. Calculate the population of Palestine, the max and min town population.\n") ;
    printf("11. Print the districts and their total population (without towns details).\n") ;
    printf("12. Change the population of a town.\n") ;
    printf("13. Save to output file.\n") ;
    printf("14. Exit.\n") ;
}

void Open_and_Load(struct MainNode **D)
{
    FILE *input_file ;
    char Line[50] ;
    char c[20] ;  //city
    char *city ; //pointer that points to the beginning of the string c
    char t[20] ;  //town
    char pop[20] ;  //population as character
    int p ;  //population as integer

    struct Node *towns ;
    struct MainNode *foundcity ;
    struct MainNode *currentcity ;
    struct MainNode *cities ;
    struct MainNode *temp ;  //last node

    input_file = fopen("districts.txt" , "r") ;  //open input file

    if(input_file == NULL)
    {
        printf("the file is empty!\n") ;
        return ;
    }

    printf("loading process started ... \n") ;

    while(fgets(Line , sizeof(Line) , input_file) != NULL)  //read each line from input file
    {
        //printf("%s\n" , Line) ; to check the reading process
        char *token = strtok(Line , "|") ;  //split the line into tokens using '|' as delimiter
        if(token == NULL)
        {
            printf("invalid input format!\n") ;
            fclose(input_file) ;
            return ;
        }

        strcpy(c , token) ;  //copy token "city name" into c
        token = strtok(NULL , "|") ;
        strcpy(t , token) ;  //copy token "town name" into t
        token = strtok(NULL , "|") ;
        strcpy(pop , token) ;  //copy token "population" into pop

        /*
          printf("city: %s \n" , c) ;
          printf("town: %s\n" , t) ;
          printf("population: %d\n" , p) ;
          to check the splitting process
        */

        city = c ;  //initialize city pointer to the beginning of c
        while(*city == ' ' || *city == '\t')  //as long as city points to space or tab character,
        {
            city++ ;  //move to the next character
        }

        p = atoi(pop) ;  //turn into integer

        foundcity = NULL ;
        currentcity = *D ;  //initialize currentcity to the head of the list

        while(currentcity != NULL)
        {
            if((strcmp(currentcity -> city , city)) == 0)  //check if city already exists
            {
                foundcity = currentcity ;  //set foundcity to the existing city node
                break ;
            }
            currentcity = currentcity -> MainNext ;  //move to the next city node
        }
        if(foundcity != NULL)  //if city is found,
        {
            towns = (struct Node *)malloc(sizeof(struct Node)) ;  //allocate memory for town node
            strcpy(towns -> town , t) ;  //copy town name into towns
            towns -> population = p ;  //set town population

            towns -> Next = foundcity -> town ;  //set the next pointer of towns to the existing town list of the city
            towns -> Previous = NULL ;  //set the previous pointer of towns to NULL

            if(foundcity -> town != NULL)  //if town list of the city is not empty,
            {
                foundcity -> town -> Previous = towns ;  //set the previous pointer of the first town node to towns
            }

            foundcity -> town = towns ;  //update the town list of the city
        }
        else  //if city isn't found,
        {
            cities = (struct MainNode *)malloc(sizeof(struct MainNode)) ;  //allocate memory for new city node
            strcpy(cities -> city , city) ;  //copy city name into cities
            cities -> town = (struct Node *)malloc(sizeof(struct Node)) ;  //allocate memory for town node
            strcpy(cities -> town -> town , t) ;  //copy town name into towns
            cities -> town -> population = p ;  //set town population
            cities -> town -> Next = NULL ;  //set next pointer of town node to NULL
            cities -> town -> Previous = NULL ;  //set previous pointer of town node to NULL
            cities -> MainPrevious = NULL ;  //set previous pointer of city node to NULL
            cities -> MainNext = NULL ;  //set next pointer of city node to NULL

            if(*D == NULL)  //if list is empty,
            {
                *D = cities ;  //set head of the list to cities
            }
            else  //if list isn't empty,
            {
                temp = *D ;  //initialize temp to head of the list
                while(temp -> MainNext != NULL)  //loop until last city node is reached
                {
                    temp = temp -> MainNext ;  //move temp to the next city node
                }
                temp -> MainNext = cities ;  //link new city node to the end of the list
                cities -> MainPrevious = temp ;  //set previous pointer of cities to the previous lat city node
            }
        }
    }

    fclose(input_file) ;  //close input file

    printf("\t\t\t done loading info.\n") ;
}

void print(struct MainNode *D)
{
    struct MainNode *temp ;  //temporary pointer to iterate through the list of cities
    struct Node *ptr ;  //temporary pointer to iterate through the list of towns within a city

    if(D == NULL)  //if the list is empty
    {
        printf("No data to print!\n") ;
        return ;
    }

    temp = D ;  //initialize temp to the head of the list

    while(temp != NULL)  //loop through the list of cities
    {
        printf("%s district: \n" , temp -> city) ;  //print city name
        ptr = temp -> town ;  //initialize ptr to the head of the town list of the current city
        while(ptr != NULL)  //loop through the list of towns
        {
            printf("%s , %d \n" , ptr -> town , ptr -> population) ;  //print the town name and population
            ptr = ptr -> Next ;  //move to the next town
        }
        printf("\n") ;  //empty line

        temp = temp -> MainNext ;  //move to the next city
    }
}

void RadixSort(struct MainNode *D)
{
    if(D == NULL)  //if the list is empty
    {
        printf("No data to sort!\n") ;
        return ;
    }

    int maxL = 20 ;  //maximum length of the city name

    for(int i = (maxL - 1) ; i >= 0 ; --i)  //iterate through each character position of city name starting from the end
    {
        /*struct MainNode *out = NULL ;  //pointer to the sorted list
        struct MainNode *C[256] = {NULL} ;  //array of pointers to buckets(one for each possible ASCII character)
        struct MainNode *p = *D ;  //pointer to iterate through the list of districts

        //distribute districts into buckets according to the current character position
        while(p)
        {
            int index = (unsigned char)p -> city[i] ;  //get the ASCII value of the character at the current position
            struct MainNode *temp = p -> MainNext ;  //store the next pointer of p
            p -> MainNext = C[index] ;  //insert p into the corresponding bucket
            if(C[index])  //if the bucket isn't empty,
            {
                C[index] -> MainPrevious = p ;  //adjust the previous pointer of the bucket's head
            }

            C[index] = p ;  //update the head of the bucket
            p = temp ;  //move to the next district
        }

        //collect districts from buckets and merge into the sorted list
        for(int j = 255 ; j>= 0 ; --j)
        {
            struct MainNode *p = C[j] ;  //pointer to iterate through the bucket
            while(p)  //loop through the bucket
            {
                struct MainNode *temp = p -> MainNext ;  //store the next pointer of p
                p -> MainNext = out ;  //insert p into the sorted list
                if(out)  //if the sorted list isn't empty,
                {
                    out -> MainPrevious = p ;  //adjust the previous pointer of the current head of the sorted list
                }

                out = p ;  //update the head of the sorted list
                p = temp ;  //move to the next district in the bucket
            }
        }

        *D = out ;  ////update the pointer to the sorted list
        struct MainNode *t = out ;  //pointer to iterate through the sorted list
        while(t && (t -> MainNext))  //find the last node of the sorted list
        {
            t = t -> MainNext ;  //move to the next node
        }

        if(t)  //if the sorted list is not empty,
        {
            t -> MainNext = NULL ;  //set the next pointer of the last node to NULL
        }*/
    }
}

void townsort(struct MainNode *D)
{
    struct MainNode *temp = D ;  //temporary pointer to iterate through the list of cities
    struct Node *ptr ;  //temporary pointer to iterate through the list of towns within a city
    struct Node *sortedlist ;  //pointer to the sorted list of towns
    struct Node *L ;  //pointer to iterate through the unsorted list of towns
    struct Node *c ;  //pointer to the current town being sorted
    struct Node *p ;  //pointer to the previous town in the sorted list

    if(temp == NULL)  //if the list is empty
    {
        printf("No data to sort!\n") ;
        return ;
    }

    printf("sorting towns process has started ... \n") ;

    while(temp != NULL)  //loop through the list of cities
    {
        ptr = temp -> town ;  //initialize ptr to the head of the town list of the current city
        if(ptr == NULL || ptr -> Next == NULL)  //if the list of towns is empty or has only one town,
        {
            temp = temp -> MainNext ;  //move to the next city
            continue ;
        }

        //Insertion sort:
        sortedlist = NULL ;  //initialize the sorted list of towns to NULL
        L = ptr ;  //initialize L to the head of the unsorted list of towns
        while(L != NULL)  //loop through the unsorted list of towns
        {
            c = L ;  //set c to the current town being sorted
            L = L -> Next ;  //move L to the next town
            if((sortedlist == NULL) || ((c -> population) < (sortedlist -> population)))  //if the sorted list is empty or the current town has smaller population than the first town in the sorted list
            {
                c -> Next = sortedlist ;  //insert the current town at the beginning
                c -> Previous = NULL ;  //set the previous pointer of the current town to NULL
                if(sortedlist != NULL)  //if the sorted list is not empty,
                {
                    sortedlist -> Previous = c ;  //set the previous pointer of the first town in the sorted list to the current town
                }
                sortedlist = c ;  //update the sorted list to include the current town
            }
            else  //of the current town has population larger than or equal to some town in the sorted list
            {
                p = sortedlist ;  //initialize p to the head of the sorted list
                while((p -> Next != NULL) && ((p -> Next -> population) < (c -> population)))  //find the position to insert the current town in the sorted list
                {
                    p = p -> Next ;  //move p to the next town in the sorted list
                }
                c -> Next = p -> Next ;  //link the current town to the next town in the sorted list
                if(p -> Next != NULL)  //if the current town is not the last town in the sorted list,
                {
                    p -> Next -> Previous = c ;  //set the previous pointer of the town after the current town to the current town
                }
                p -> Next = c ;  //link the previous town to the current town
                c -> Previous = p ;  //set the previous pointer of the current town to the previous town
            }
        }

        //update pointers:
        temp -> town  = sortedlist ;  //update the town list of the current city with the sorted list
        temp = temp -> MainNext ;  //move to the next city
    }

    printf("\t\t\t\t done sorting.\n") ;
}

void insertcity(struct MainNode *D)
{
    char city[20] ;  //variable to store the name of the new city
    int n = 0 ;  //variable to store the number of towns to be added to the new city
    char town[20] ;  //variable to store the name of each town
    int population ;  //variable to store the population of each town

    if(D == NULL)  //if the list is empty
    {
        printf("No list!can't add!!!\n") ;
        return ;
    }

    printf("enter the name of your new city...\n") ;
    scanf("%s" , city) ;

    if(exist(D , city) == 1)  //check if the city already exists in the list
    {
        printf("this city is already exists!\nif u wanna add more towns or delete the city , there r options for that ...\n") ;
        return ;
    }

    printf("how many towns in this city u wanna add?\n") ;
    scanf("%d" , &n) ;

    if(n == 0)
    {
        printf("No towns!!! there must be at least one town , maybe try again later!\n") ;
        return ;
    }

    struct MainNode *newCity ;  //pointer to the  new city node
    struct Node *newTown ;  //pointer to the new town node
    struct Node *temp ;  //temporary pointer to iterate through the town list of the new city
    struct MainNode *ptr ;  //pointer to iterate through the list of cities

    newCity = (struct MainNode *)malloc(sizeof(struct MainNode)) ;  //allocate memory for the new city node
    strcpy(newCity -> city , city) ;  //copy the name of the new city into the new city node
    newCity -> town = NULL ;  //initialize the town list of the new city to NULL
    newCity -> MainNext = NULL ;  //set the next pointer of the new city node to NULL
    newCity -> MainPrevious = NULL ;  //set the previous pointer of the new city node to NULL

    printf("enter your town(s) name(s) and population...\n") ;
    for(int i = 0 ; i < n ; i++)  //loop to add each town to the new city
    {
        printf("town:\n") ;
        scanf("%s" , town) ;
        printf("population:\n") ;
        scanf("%d" , &population) ;

        newTown = (struct Node *)malloc(sizeof(struct Node)) ;  //allocate memory for the new town node
        strcpy(newTown -> town , town) ;  //copy the name of the town into the new town node
        newTown -> population = population ;  //set the population of the town
        newTown -> Next = NULL ;  //set the next pointer of the new town node to NULL
        newTown -> Previous = NULL ;  //set the previous pointer of the new town node to NULL

        if(newCity -> town == NULL)  //if the town list of the new city is empty,
        {
            newCity -> town = newTown ;  //set the town list of the new city to the new town
        }
        else  //if the town list of the new city is not empty
        {
            temp = newCity -> town ;  //initialize temp to the head of the town list of the new city
            while(temp -> Next != NULL)  //loop to find the last town in the town list of the new city
            {
                temp = temp -> Next ;  //move temp to the next town
            }
            temp -> Next = newTown ;  //link the last town in the town list to the new town
            newTown -> Previous = temp ;  //set the previous pointer of the new town to the last town in the town list
        }
    }

    if(D == NULL)  //if the list is empty,
    {
        D = newCity ;  //set the head of the list of the cities to the new city
    }
    else  //if the list isn't empty,
    {
        ptr = D ;  //initialize ptr to the head of the list of cities
        while(ptr -> MainNext != NULL)  //loop to find the last city in the list of cities
        {
            ptr = ptr -> MainNext ;  //move ptr to the next city
        }
        ptr -> MainNext = newCity ;  //link the last city in the list to the new city
        newCity -> MainPrevious = ptr ;  //set the previous pointer of the new city to the last city in the list
    }

    printf("district and it's town(s) and population have been added successfully.\n") ;
}

int exist(struct MainNode *D , char *city)
{
    struct MainNode *c = D ;  //pointer to iterate through the list of cities

    while(c != NULL)  //loop through the list of cities
    {
        if(strcmp(c -> city , city) == 0)  //check if the city is already exists
        {
            return 1 ;  //return 1 if the city exists in the list
        }
        c = c -> MainNext ;  //move to the next city
    }
    return 0 ;  //return 0 if the city doesn't exist in the list

}

void inserttown(struct MainNode *D)
{
    char city[20] ;  //variable to store the name of the district to which the new town will be added
    char town[20] ;  //variable to store the name of the new town
    int population ;  //variable to store the population of the new town

    if(D == NULL)  //if the list is empty
    {
        printf("No list!can't add!!!\n") ;
        return ;
    }

    printf("which district u wanna add the new town to?\n") ;
    scanf("%s" , city) ;

    struct MainNode *district ;  //pointer to iterate through the list of districts
    struct Node *newt ;  //pointer to the new town node
    struct Node *temp ;  //temporary pointer to iterate through the town list of a district

    district = D ;  //initialize district to the head of the list of districts
    while(district != NULL)  //loop through the list of districts
    {
        if(strcmp(district -> city , city) == 0)  //if the city is already exists
        {
            printf("what is the name of the new town?\n") ;
            scanf("%s" , town) ;
            printf("and it's population?\n") ;
            scanf("%d" , &population) ;
            newt = (struct Node *)malloc(sizeof(struct Node)) ;  //allocate memory for the new town node
            strcpy(newt -> town , town) ;  //copy the name of the new town into the new town node
            newt -> population = population ;  //set the population of the new town
            newt -> Next = NULL ;  //set the next pointer of the new town node to NULL
            newt -> Previous = NULL ;  //set the previous pointer of the new town node to NULL
            if(district -> town == NULL)  //if the town list of the district is empty,
            {
                district -> town = newt ;  //set the town list of the district to the new town
            }
            else  //if the town list of the the district is not empty
            {
                temp = district -> town ;  //initialize temp to the head of the town list of the district
                while(temp -> Next != NULL)  //loop to find the last town in the town list of the district
                {
                    temp = temp -> Next ;  //move temp to the next town
                }

                temp -> Next = newt ;  //link the last town in the town list to the new town
                newt -> Previous = temp ;  //set the previous pointer of the new town to the last town in the town list
            }
            printf("town '%s' with population '%d' add to district '%s'.\n" , town , population , city) ;
            return ;
        }

        district = district -> MainNext ;  //move to the next district
    }
    printf("district '%s' is not found!\n" , city) ;
}

void deleteTown(struct MainNode *D)
{
    char city[20] ;  //variable to store the name of the district from which the town will be deleted
    char town[20] ;  //variable to store the name of the town to be deleted

    if(D == NULL)  //if the list is empty
    {
        printf("No list!can't add!!!\n") ;
        return ;
    }

    printf("which district u wanna add the new town to?\n") ;
    scanf("%s" , city) ;

    struct MainNode *district ;  //pointer to iterate through the list of districts
    struct Node *t ;  //pointer to iterate through the town list of a district

    district = D ;  //initialize district to the head of the list of districts
    while(district != NULL)  //loop through the list of districts
    {
        if(strcmp(district -> city , city) == 0)  //check if the city already exists
        {
            printf("what is the name of the new town?\n") ;
            scanf("%s" , town) ;

            t = district -> town ;  //initialize t to the head of the town list of the district
            while (t != NULL)  //loop through the town list of the district
            {
                if(strcmp(t -> town , town) == 0)  //check if the town exists
                {
                    if(t -> Previous != NULL)
                    {
                        t -> Previous -> Next = t -> Next ;  //link the previous town to the next town
                    }
                    if(t -> Next != NULL)
                    {
                        t -> Next -> Previous = t -> Previous ;  //link the next town to the previous town
                    }
                    free(t) ;  //deallocate memory for the current town
                    printf("town '%s' deleted from district '%s'.\n" , town , city) ;
                    return ;
                }
                t = t -> Next ;  //move to the next town
            }
            printf("town '%s' isn't found in district '%s'!\n" , town , city) ;
            return ;
        }

        district = district -> MainNext ;  //move to the next district
    }
    printf("district '%s' is not found!\n" , city) ;
}

void deleteCity(struct MainNode *D)
{
    char city[20] ;  //variable to store the name of the district to be deleted

    if(D == NULL)  //if the list is empty
    {
        printf("No list!!!\n") ;
        return ;
    }

    printf("which district u wanna delete?\n") ;
    scanf("%s" , city) ;

    struct MainNode *district = D ;  //pointer to iterate through the list of districts
    struct Node *t ;  //pointer to iterate through the town list of a district
    struct Node *temp ;  //temporary pointer to deallocate memory for towns

    while(district != NULL)  //loop through the list of districts
    {
        if(strcmp(district -> city , city) == 0)  //check if the city exists
        {
            t = district -> town ;  //initialize t to the head of the town list of the district
            while(t != NULL)  //loop through the town list of the district
            {
                temp = t ;  //store the current town in temp
                t = t -> Next ;  //move t to the next town
                free(temp) ;  //deallocate memory for the current town
            }
            if(district -> MainPrevious != NULL)
            {
                district -> MainPrevious -> MainNext = district -> MainNext ;  //link the previous district to the next district
            }
            if(district -> MainNext != NULL)
            {
                district -> MainNext -> MainPrevious = district -> MainPrevious ;  //link the next district to the previous district
            }
            if(D == district)  //if the deleted district is the head of the list
            {
                D = district -> MainNext ;  //update the head of the list to the next district
            }

            free(district) ;  //deallocate memory for the deleted district

            printf("district '%s' and all it's towns deleted.\n" , city) ;
            return ;
        }

        district = district -> MainNext ;  //move to the next district
    }

    printf("district '%s' isn't found!\n" , city) ;
}

int TotalP(struct MainNode *D)
{
    int tp = 0 ;  //variable to store the total population
    struct MainNode *district ;  //pointer to iterate through the list of districts
    struct Node * town ;  //pointer to iterate through the town list of a district

    if(D == NULL)  //if the list is empty
    {
        printf("No list!!!\n") ;
        return ;
    }

    district = D ;  //initialize district to the head of the list of districts
    while(district != NULL)  //loop through the list of districts
    {
        town = district -> town ;  //initialize town to the head of the town list of the district
        while(town != NULL)  //loop through the town list of the district
        {
            tp += town -> population ;  //add the population of the current town to the total population
            town = town -> Next ;  //move to the next town
        }
        district = district -> MainNext ;  //move to the next district
    }
    return tp ;  //return the total population
}

int MaxP(struct MainNode *D)
{
    int mp ;  //variable t store the maximum population
    struct MainNode *district ;  //pointer to iterate through the list of a district
    struct Node *town ;  //pointer to iterate through the town list of a district

    if(D == NULL)  //if the list is empty
    {
        printf("No list!!!\n") ;
        return ;
    }

    mp = INT_MIN ;  //initialize mp to the minimum possible integer value
    district = D ;  //initialize district to the head of the list of didstricts
    while(district != NULL)  //loop through the list of districts
    {
        town = district -> town ;  //initialize town to the head of the town list of the district
        while(town != NULL)  //loop through the town list of the district
        {
            if(town -> population > mp)  //if the population of the current town is greater than mp
            {
                mp = town -> population ;  //update mp with the population of the current town
            }

            town = town -> Next ;  //move to the next town
        }

        district = district -> MainNext ;  //move to the next district
    }

    return mp ;  //return the maximum population
}

int MinP(struct MainNode *D)
{
    int mp ;  //variable to store the minimum population
    struct MainNode *district ;  //pointer to iterate through the list of districts
    struct Node *town ;  //pointer to iterate through the town list of a district

    if(D == NULL)  //if the list is empty
    {
        printf("No list!!!\n") ;
        return ;
    }

    mp = INT_MAX ;  //initialize mp to the maximum possible integer value
    district = D ;  //initialize district to the head of the list of districts
    while(district != NULL)  //loop through the list of districts
    {
        town = district -> town ;  //initialize town to the head of the town list of the district
        while(town != NULL)  //loop through the town list of the district
        {
            if(town -> population < mp)  //if the population of the current town is less than mp
            {
                mp = town -> population ;  //update mp with the population of the current town
            }

            town = town -> Next ;  //move to the next town
        }

        district = district -> MainNext ;  //move to the next district
    }

    return mp ;  //return the minimum population
}

void print_districtandpopulation(struct MainNode *D)
{
    struct MainNode *district ;  //pointer to iterate through the list of districts
    struct Node *town ;  //pointer to iterate through the town list of a district
    int dp = 0 ;  //variable to store the total population of a district

    if(D == NULL)  //if the list is empty
    {
        printf("No Data to print!\n") ;
    }

    district = D ;  //initialize town to the head of the town list of the district
    while(district != NULL)  //loop through the town list of the district
    {
        dp = 0 ;  //reset dp to 0 for each district
        town = district -> town ;  //initialize town to the head of the town list of the district
        while(town != NULL)  //loop through the town list of the district
        {
            dp += town -> population ;  //add the population of the current town to dp
            town = town -> Next ;  //move to the next town
        }

        printf("%s district , population = %d\n" , district -> city , dp) ;
        district = district -> MainNext ;  //move to the next district
    }
}

void changeP(struct MainNode *D)
{
    char city[20] ;
    char town[20] ;
    int newP ;

    struct MainNode *district ;
    struct Node *t ;

    if(D == NULL)  //if the list is empty
    {
        printf("No data to modify!\n") ;
        return ;
    }

    printf("what is the name of the district?\n") ;
    scanf("%s" , city) ;

    district = D ;  //initialize district to the head of the list of districts
    while(district != NULL)  //loop through the list of districts
    {
        if(strcmp(district -> city , city) == 0)  //check if the district exists
        {
            printf("which town has a new population?\n") ;
            scanf("%s" , town) ;

            t = district -> town ;  //initialize t to the head of the town list of the district
            while(t != NULL)  //loop through the town list of the district
            {
                if(strcmp(t -> town , town) == 0)  //check if the town exists in the district
                {
                    printf("the new population...?\n") ;
                    scanf("%d" , &newP) ;

                    t -> population = newP ;  //update the population of the current town with the new population
                    printf("population of town '%s' in district '%s' updated to '%d'." , town , city , newP) ;
                    return ;
                }

                t = t -> Next ;  //move t to the next town
            }

            printf("town '%s' isn't found in district '%s'.\n" , town , city) ;
            return ;
        }

        district = district -> MainNext ;  //move to  the next district
    }

    printf("district '%s' isn't found!\n" , city) ;
}

void save(struct MainNode *D)
{
    FILE *output_file ;

    if(D == NULL)  //if the list is empty
    {
        printf("No data to save!\n") ;
        return ;
    }

    output_file = fopen("sorted_districts.txt" , "w") ;  //open output file

    struct MainNode *district ;  //pointer to iterate through the list of districts
    struct Node *town ;  //pointer to iterate through the town list of a district

    district = D ;  //initialize district to the head of the list of districts
    while(district != NULL)  //loop through the list of districts
    {
        fprintf(output_file , "%s District , population = %d\n" , district -> city , districtpop(district)) ;  //write info in the output file

        town = district -> town ;  //initialize town to the head of the town list of the district
        while(town != NULL)  //loop through the town list of the district
        {
            fprintf(output_file , "%s , %d\n" , town -> town , town -> population) ;  //write info in the output file
            town = town -> Next ;  //move to the next town
        }

        district = district -> MainNext ;  //move to the next district
    }

    fclose(output_file) ;  //close the output file
    printf("Data is saved.\n") ;
}

int districtpop(struct MainNode *district)
{
    int tp ;  //variable to store the total population of the district
    struct Node *t ;  //pointer to iterate through the town list of the district

    tp = 0 ;  //initialize tp to 0
    t = district -> town ;  //initialize t to the head of the town list of the district
    while(t != NULL)  //loop through the town list of the district
    {
        tp += t -> population ;  //add the population of the current town to to
        t = t -> Next ;  //move to the next town
    }

    return tp ;  //return the total population of the district
}
