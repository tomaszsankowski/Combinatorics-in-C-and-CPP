#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

struct City {
    int id;
    char name[20];
    int population;
    double latitude;
    double longitude;
};

#define N 4

struct City shortest[N];
int length = 0;

struct City closest_to_avarage[N/2];
int population = 0;
int cur_population = 0;
int delta = INT_MAX;

int calc_distance(int x1, int y1, int x2, int y2)
{
    return(abs((x1-x2)*(x1-x2)+(y1-y2)*(y1*y2)));
}

void swap(struct City* city1, struct City* city2)
{
    struct City tmp = *city1;
    *city1 = *city2;
    *city2 = tmp;
}

void permute(struct City cities[], int start, int end)
{
    if(start==end)
    {
        int tmp_length = 0;
        for(int i=0;i<end;i++)
        {
            tmp_length+=calc_distance(cities[i].latitude,cities[i].longitude, cities[i+1].latitude, cities[i+1].longitude);
        }
        if(tmp_length>length)
        {
            length = tmp_length;
            for(int i=0;i<=end;i++)
            {
                shortest[i] = cities[i];
            }
        }
        for(int i=0;i<=end;i++)
        {
            printf("%s ", cities[i].name);
        }
        printf("\n");
    }
    else
    {
        for(int i = start; i <= end; i++)
        {
            swap(&cities[start], &cities[i]);
            permute(cities, start+1, end);
            swap(&cities[start], &cities[i]);
        }
    }
}

void generateSubset(struct City cities[], struct City subset[], int n, int k, int id, int subsetid)
{
    if(subsetid == k)
    {
        int tmp_population = 0;
        for(int i=0;i<k;i++)
        {
            tmp_population+=subset[i].population;
        }
        if(abs(tmp_population-population)<delta)
        {
            delta = abs(tmp_population-population);
            cur_population = tmp_population;
            for(int i=0;i<k;i++)
            {
                closest_to_avarage[i] = subset[i];
            }
        }
        for(int i=0;i<k;i++)
        {
            printf("%s ",subset[i].name);
        }
        printf("\n");
        return;
    }

    if(id == n)
    {
        return;
    }

    subset[subsetid] = cities[id];
    generateSubset(cities, subset, n, k, id + 1, subsetid + 1);

    generateSubset(cities, subset, n, k, id + 1, subsetid);
}

int main() {
    struct City cities[15];
    FILE *file = fopen("miasta.in", "r");

    if (file == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 15; i++) {
        if (fscanf(file, "%d %s %d %lf %lf",
                   &cities[i].id,
                   cities[i].name,
                   &cities[i].population,
                   &cities[i].latitude,
                   &cities[i].longitude) != 5) {
            break;
        }
    }

    fclose(file);

    permute(cities, 0, N-1);

    printf("\n\nShortest path:\n");
    for(int i=0;i<N;i++)
    {
        printf("%s ",shortest[i].name);
    }
    printf("\n\nShortest path length: %d\n\n",length);

    int k = N/2;
    struct City subset[k];

    for(int i=0;i<N;i++)
    {
        population+=cities[i].population;
    }
    population/=2;
    generateSubset(cities, subset, N, k, 0, 0);

    printf("\n\nClosest to avarage cities permutation:\n");
    for(int i=0;i<k;i++)
    {
        printf("%s ",closest_to_avarage[i].name);
    }
    printf("\n\nPopulation of permutation: %d\n\n",cur_population);
    /*
    printf("Id\tTown\tPopulation\tLatitude\tLongitude\n");
    for (int i = 0; i < 15; i++) {
        printf("%d\t%s\t%d\t%.4lf\t%.4lf\n",
               cities[i].id,
               cities[i].name,
               cities[i].population,
               cities[i].latitude,
               cities[i].longitude);
    }
    */

    return 0;
}
