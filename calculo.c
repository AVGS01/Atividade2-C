#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float X;
    float Y;
} Ponto;

float calcularAreaTriangulo(Ponto A, Ponto B, Ponto C) {
    float det = ((A.X * B.Y) + (B.X * C.Y) + (C.X * A.Y)) - ((A.Y * B.X) + (B.Y * C.X) + (C.Y * A.X));
    return fabs(det) / 2.0;
}

void calcularAreaPoligono(char* arquivo) {
    FILE* f;
    int numVertices;
    Ponto* vertices;
    float areaTotal = 0.0;

    f = fopen(arquivo, "r");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    if (fscanf(f, "%d", &numVertices) != 1 || numVertices < 3) {
        printf("O arquivo não contém o número correto de vértices!\n");
        fclose(f);
        exit(1);
    }
    
    vertices = (Ponto*)malloc(numVertices * sizeof(Ponto));
    if (vertices == NULL) {
        printf("Erro ao alocar memória!\n");
        fclose(f);
        exit(1);
    }

    for (int i = 0; i < numVertices; i++) {
        if (fscanf(f, "%f %f", &vertices[i].X, &vertices[i].Y) != 2) {
            printf("Erro ao ler as coordenadas do vértice!\n");
            fclose(f);
            free(vertices);
            exit(1);
        }
    }

    fclose(f);

    if (numVertices == 3) {
        areaTotal = calcularAreaTriangulo(vertices[0], vertices[1], vertices[2]);
    } else {
        for (int i = 2; i < numVertices; i++) {
            areaTotal += calcularAreaTriangulo(vertices[0], vertices[i - 1], vertices[i]);
        }
    }

    printf("A área do polígono é: %.2f\n", areaTotal);

    free(vertices);
}

int main() {
    calcularAreaPoligono("../poligono.txt");
    return 0;
}
