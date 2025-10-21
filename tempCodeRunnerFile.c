#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    FILE *fin,*fout;

    fin = fopen("in.txt", "r");
    if (fin == NULL){
        printf("Nu se poate deschide fisierul de intare.");
        return 1;
    }
    fout = fopen ("out.txt", "a");
    if (fout == NULL){
        printf("Nu se poate deschide fisierul de iesire.");
        return 1;
    }

    char x; //pentru citirea caracterelor.
    int i = 1; //contor
    char aux; //buffer
    char *v = NULL;
    int j = 0, k = 0;
    int n = 2;
    char buffer[10];

    char *tmp = (char *)realloc(v, sizeof(char) * n );
    if (tmp == NULL){
        printf("Zona de memroie nu a putut fi alocata!");
        return 1;
        free(v);
    }
    v = tmp;

    fscanf(fin,"%c",&x);
    aux = x;

    while(fscanf(fin,"%c",&x) == 1){
        if(j > sizeof(int) * n - 1){
            n = n * 2;
            tmp = (char *)realloc(v,sizeof(int) * n);
            if(tmp == NULL){
                printf("Nu s-a putut extinde memoria, sarakule!");
                free(v);
                return 1;
            }
            v = tmp;
        }
        if(x != aux){
            v[j++] = aux;
            aux = x;
            if(i > 9){
                sprintf(buffer,"%d", i);
                i=0;
                while(buffer[i] != '\0'){
                    strcpy(v[j++],buffer[i]);
                    i++;
                }
            }
            else
                v[j++] = i + '0';
            i=1;
        }
        else{
            i++;
        }
    }
    v[j++] = aux;
    v[j++] = i + '0';
    v[j] = '\0';
    fprintf(fout,"%s", v);



    free(tmp);
    free(v);
    fclose(fin);
    fclose(fout);
    return 0;
}