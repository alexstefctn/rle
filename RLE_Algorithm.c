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
    char *v = NULL; char* v2 = NULL; //pointeri catre zona de memorie care pastreaza sirul de caractere
    char aux; //buffer
    int i = 0, j = 0; //contor v si v2
    int p = 1; //contor pentru numarul de litere la comprimare
    int c = 0; //retine si transforma in int numarul de repetitii al unei litere - folosit pt decomprimare
    int k = 0; //contor pentru c
    int n = 2; //marire dimensiune pentru v
    int m = 2; //marire dimensiune pentru v2
    char buffer[10]; //pentru repetitii de litere mai mari decat 9
    short int verificat = 0; //verifc daca a trecut pe ramura de calulare a frecventei

    char *tmp = (char *)realloc(v, sizeof(char) * n );
    if (tmp == NULL){
        printf("Zona de memroie nu a putut fi alocata pentru sirul din in.txt!");
        return 1;
        free(v);
    }
    v = tmp;

    fscanf(fin,"%c",&x);
    aux = x;

    while(fscanf(fin,"%c",&x) == 1){
        if(i > n - 1){
            n = n * 2;
            tmp = (char *)realloc(v,sizeof(char) * n);
            if(tmp == NULL){
                printf("Nu s-a putut extinde memoria, sarakule!");
                free(v);
                return 1;
            }
            v = tmp;
        }
        if(x != aux){
            v[i++] = aux;
            aux = x;
            sprintf(buffer,"%d", p);
            for(int b = 0; buffer[b] != '\0'; b++)
                v[i++] = buffer[b];
            p=1;
        }
        else{
            p++;
        }
    }
    v[i++] = aux;
    v[i++] = p + '0';
    v[i] = '\0';
    fprintf(fout,"Acesta este codul comprimat: %s \n", v);

//Decompresie: A30B3C7D1A1B1C1D1
i = 0;
j = 0; //resetarea contorilor pentru vectori.
n = 0; //resetarea dimensiunii pentru noul vector v2
tmp = (char *)realloc(v2, sizeof(char) * 100 );
    if (tmp == NULL){
        printf("Zona de memroie nu a putut fi alocata pentru sirul decompresat!");
        free(v2);
        return 1;
    }
    v2 = tmp;
//0123
//A30B3C7D1A1B1C1D1
    for(i = 0; v[i] != '\0'; i++){
        if(v[i] >= '0' && v[i] <= '9'){
            c = c*10 + (v[i]-'0');
            verificat = 1; //este folosit doar ca siguranta la inceput, sa nu intre in loop pentru cand nu are numarul de repetitii.
        }
        else{
            if(verificat == 1)
                for(k = 0; k < c; k++)
                    v2[j++] = aux;
            aux = v[i];
            verificat = 0;
            c = 0;
        }
    }
    for(k = 0; k < c; k++)
        v2[j++] = aux;
    v2[j] = '\0';

    fprintf(fout,"Acesta este decomprimat: %s \n", v2);

    free(v);
    free(v2);
    fclose(fin);
    fclose(fout);
    return 0;
}