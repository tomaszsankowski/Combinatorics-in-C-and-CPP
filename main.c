#include <stdio.h>
#include <math.h>

struct City {
    int id;
    char name[20];
    int population;
    double x, y;
};

struct City cities[15];
struct City cities2[15];
double smallest_plain = 76676.0f;
float shortest_dist = 524365476.0f;
int counter = 0;

float odleglosc(const int x1, const int y1, const int x2, const int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void P(int miasta[], int permutacja[], const int N, const int K, const int perm_id, const int perm_size) {
    if (perm_id == K) {
        float tmp = 0;
        for (int i = 0; i < K - 1; i++) {
            tmp += odleglosc(cities[permutacja[i]].x, cities[permutacja[i]].y, cities[permutacja[i + 1]].x, cities[permutacja[i + 1]].y);
        }
        if (tmp < shortest_dist) {
            shortest_dist = tmp;
        }
        counter++;
        printf("%d\t", counter);
        for (int i = 0; i < K; i++) {
            printf("%s ", cities[permutacja[i]].name);
        }
        printf("\n");
        return;
    }

    for (int i = 0; i < N; i++) {
        const int n = miasta[i];
        int found = 0;
        for (int j = 0; j < perm_size; j++) {
            if (permutacja[j] == n) {
                found = 1;
            }
        }
        if (found == 0 && perm_size < K) {
            permutacja[perm_id] = miasta[i];
            P(miasta, permutacja, N, K, perm_id + 1, perm_size + 1);
        }
    }
}

void W(int miasta[], int wariacja[], const int N, const int K, const int id, const int war_id) {
    if (war_id == K) {
        double minx = cities[wariacja[0]].x, maxx = cities[wariacja[0]].x, miny = cities[wariacja[0]].y, maxy = cities[wariacja[0]].y;
        for (int i = 1; i < K; i++) {
            if (cities[wariacja[i]].x > maxx)
                maxx = cities[wariacja[i]].x;
            if (cities[wariacja[i]].x < minx)
                minx = cities[wariacja[i]].x;
            if (cities[wariacja[i]].y > maxy)
                maxy = cities[wariacja[i]].y;
            if (cities[wariacja[i]].y < miny)
                miny = cities[wariacja[i]].y;
        }
        const double pole = (maxx - minx) * (maxy - miny);
        if (pole < smallest_plain) {
            smallest_plain = pole;
            for (int i = 0; i < K; i++) {
                cities2[i] = cities[wariacja[i]];
            }
        }
        counter++;
        printf("%d\t", counter);
        for (int i = 0; i < K; i++) {
            printf("%s ", cities[wariacja[i]].name);
        }
        printf("\n");
        return;
    }

    if (id == N) {
        return;
    }
    wariacja[war_id] = miasta[id];
    W(miasta, wariacja, N, K, id + 1, war_id + 1);
    W(miasta, wariacja, N, K, id + 1, war_id);
}

int main() {
    FILE* f = fopen("miasta.in", "r");
    if (f == NULL) {
        perror("Error opening file");
        return -1;
    }
    for (int i = 0; i < 15; i++) {
        if (fscanf(f, "%d %s %d %lf %lf", &cities[i].id, cities[i].name, &cities[i].population, &cities[i].x, &cities[i].y) != 5) {
            break;
        }
    }
    fclose(f);
    for (int i = 0; i < 15; i++) {
        printf("%s\n", cities[i].name);
    }

    const int N = 5;
    const int K = 3;

    int miasta[N];
    for (int i = 0; i < N; i++) {
        miasta[i] = i + 1;
    }
    int permutacja[K];

    P(miasta, permutacja, N, K, 0, 0);

    printf("Shortest dist: %lf\n", shortest_dist);

    counter = 0;
    int wariacja[K];
    W(miasta, wariacja, N, K, 0, 0);

    printf("Smallest plain: %lf\nIn cities:\n", smallest_plain);
    for (int i = 0; i < K; i++)
    {
        printf("%s ", cities2[i].name);
    }
    return 0;
}
