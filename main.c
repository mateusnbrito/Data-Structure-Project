#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct price{
    float btc;
    float ada;
    float eth;
} Price;

typedef struct crypto{
    char name[4];
    char op[1];
    float qty;
    float price;
    struct crypto *next;
} Crypto;

void printDoneTransactions(char name[4], float qty, float price){
    printf("NOVA TRANSAÇÃO: %.2f %s vendidos a R$ %.2f\n", qty, name, price);
}

Crypto* removeOp(Crypto *head){
    Crypto *current = head;
    Crypto *delete = (Crypto*) malloc(sizeof(Crypto));

    while(current->next != NULL){
        if((current->next)->qty == 0){
            if((current->next)->next != NULL){
                delete = current->next;

                current->next = (current->next)->next;

                free(delete);
            }
        }

        current = current->next;
    }

    if(current->qty == 0){
        free(current);
    }
}

void getCurrentPrice(Price *price){
    printf("------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    printf("                                                                   Cotação Atual\n\n------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    printf("                                              BTC: R$ %.2f  |  ADA: R$ %.2f  |  ETH: R$ %.2f\n\n", price->btc, price->ada, price->eth);
}

Crypto* transact(Crypto *offer, Crypto *head, Price *price){
    Crypto *current = head;

    while(current->next != NULL){
        if(strcmp(offer->name, current->name) == 0){
            if(!strcmp(offer->op, current->op) == 0){
                if(offer->price == current->price){
                    if(offer->qty == current->qty){
                        float aux;

                        if(strcmp(offer->name, "BTC") == 0 && offer->qty > 0 && current->qty > 0){
                            price->btc = offer->price;

                            aux = offer->qty;

                            offer->qty = offer->qty - current->qty;
                            current->qty = current->qty - aux;

                            printDoneTransactions(offer->name, aux, price->btc);
                        }
                        if(strcmp(offer->name, "ADA") == 0 && offer->qty > 0 && current->qty > 0){
                            price->ada = offer->price;

                            aux = offer->qty;

                            offer->qty = offer->qty - current->qty;
                            current->qty = current->qty - aux;

                            printDoneTransactions(offer->name, aux, price->ada);
                        }
                        if(strcmp(offer->name, "ETH") == 0 && offer->qty > 0 && current->qty > 0){
                            price->eth = offer->price;

                            aux = offer->qty;

                            offer->qty = offer->qty - current->qty;
                            current->qty = current->qty - aux;

                            printDoneTransactions(offer->name, aux, price->eth);
                        }
                    }

                    if(offer->qty > current->qty){
                        float aux;

                        if(strcmp(offer->name, "BTC") == 0 && offer->qty > 0 && current->qty > 0){
                            price->btc = offer->price;

                            aux = offer->qty;

                            offer->qty = offer->qty - current->qty;
                            current->qty -= current->qty;

                            printDoneTransactions(offer->name, aux-offer->qty, price->btc);
                        }

                        if(strcmp(offer->name, "ADA") == 0 && offer->qty > 0 && current->qty > 0){
                            price->ada = offer->price;

                            aux = offer->qty;

                            offer->qty = offer->qty - current->qty;
                            current->qty -= current->qty;

                            printDoneTransactions(offer->name, aux-offer->qty, price->ada);
                        }

                        if(strcmp(offer->name, "ETH") == 0 && offer->qty > 0 && current->qty > 0){
                            price->eth = offer->price;

                            aux = offer->qty;

                            offer->qty = offer->qty - current->qty;
                            current->qty -= current->qty;

                            printDoneTransactions(offer->name, aux-offer->qty, price->eth);
                        }
                    }

                    if(offer->qty < current->qty){
                        float aux;

                        if(strcmp(offer->name, "BTC") == 0 && offer->qty > 0 && current->qty > 0){
                            price->btc = offer->price;

                            aux = offer->qty;

                            offer->qty = current->qty - offer->qty;
                            current->qty -= current->qty;

                            printDoneTransactions(offer->name, offer->qty-current->qty, price->btc);
                        }
                        if(strcmp(offer->name, "ADA") == 0 && offer->qty > 0 && current->qty > 0){
                            price->ada = offer->price;

                            aux = offer->qty;

                            offer->qty = current->qty - offer->qty;
                            current->qty -= current->qty;

                            printDoneTransactions(offer->name, offer->qty-current->qty, price->ada);
                        }
                        if(strcmp(offer->name, "ETH") == 0 && offer->qty > 0 && current->qty > 0){
                            price->eth = offer->price;

                            aux = offer->qty;

                            offer->qty = current->qty - offer->qty;
                            current->qty -= current->qty;

                            printDoneTransactions(offer->name, offer->qty-current->qty, price->eth);
                        }
                    }
                }
            }
        }

        current = current->next;

        removeOp(head);
    }
}

Crypto* fillOpsList(Crypto op, Crypto *head, Price *price){
    Crypto *current = head;

    while(current->next != NULL){
        current = current->next;
    }

    Crypto *newOp = (Crypto*) malloc(sizeof(Crypto));

    current->next = newOp;

    strcpy(newOp->name, op.name);
    strcpy(newOp->op, op.op);
    newOp->qty = op.qty;
    newOp->price = op.price;
    newOp->next = NULL;

    transact(newOp, head, price);

    return head;
}

Crypto* newOp(Crypto *head, Price *price){
    int menuOp0, menuOp1;
    Crypto newOp;

    printf("                                                          Nova Operação\n\n------------------------------------------------------------------------------------------------------------------------------------------------\n\n");

    while(menuOp0 != 1 && menuOp0 != 2 && menuOp0 != 3){
        printf("ESCOLHA A CRIPTOMOEDA\n\nOpções:\n\nBTC | Digite 1\nADA | Digite 2\nETH | Digite 3\n\nSua opção: ");
        fflush(stdin);
        scanf("%d", &menuOp0);
        printf("\n------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    }

    switch(menuOp0){
        case 1: {
            strcpy(newOp.name, "BTC");
            break;
        };
        case 2: {
            strcpy(newOp.name, "ADA");
            break;
        };
        case 3: {
            strcpy(newOp.name, "ETH");
            break;
        }
    }

    while(menuOp1 != 1 && menuOp1 != 2){
        printf("ESCOLHA A OPERAÇÃO\n\nOpções:\n\nCompra | Digite 1\nVenda  | Digite 2\n\nSua opção: ");
        fflush(stdin);
        scanf("%d", &menuOp1);
        printf("\n------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    }

    switch(menuOp1){
        case 1: {
            strcpy(newOp.op, "B");
            break;
        };
        case 2: {
            strcpy(newOp.op, "S");
            break;
        };
    }

    int inputCheck = 0;

    while(inputCheck == 0){
        printf("INSIRA A QUANTIDADE\n\nSua opção: ");
        fflush(stdin);
        inputCheck = scanf("%f", &newOp.qty);
        printf("\n------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    }

    inputCheck = 0;

    while(inputCheck == 0){
        printf("INSIRA O PREÇO\n\nSua opção: ");
        fflush(stdin);
        inputCheck = scanf("%f", &newOp.price);
        printf("\n------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    }

    menuOp0 = 0;
    menuOp1 = 0;

    return fillOpsList(newOp, head, price);
}

Crypto* printOpsList(Crypto *head){
    Crypto *auxCrypto = head;

    int listSize = 0;

    printf("------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    printf("                                                          Ofertas de Criptomoedas\n\n------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("                    VENDA                                                                                          COMPRA                    \n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------\n\n");
    printf("Cripto | Qtd  | Preço                                                                                              Cripto | Qtd  | Preço\n\n");

    while(auxCrypto != NULL){
        listSize++;

        auxCrypto = auxCrypto->next;
    }

    auxCrypto = head;

    Crypto sellOffers[listSize];
    Crypto buyOffers[listSize];
    int sellCont = 0;
    int buyCont = 0;
    int cont = 0;

    for(int i=0; auxCrypto != NULL; i++){
        if(*auxCrypto->op == 'S'){
            sellOffers[sellCont] = *auxCrypto;
            sellCont++;
        }

        if(*auxCrypto->op == 'B'){
            buyOffers[buyCont] = *auxCrypto;
            buyCont++;
        }

        auxCrypto = auxCrypto->next;
    }

    auxCrypto = head;

    while(cont <= listSize/2){
        if(cont < sellCont){
            printf("%s    | %.2f | R$ %.2f", sellOffers[cont].name, sellOffers[cont].qty, sellOffers[cont].price);
        }

        if(buyCont-cont <= 0){
            printf("\n");
        }

        if(cont < buyCont){
            printf("                                                                                        %s    | %.2f | R$ %.2f\n", buyOffers[cont].name, buyOffers[cont].qty, buyOffers[cont].price);
        }

        cont++;
    }
}

Crypto* readDatabase(FILE *database, Crypto *head, Price *price){
    char line[150];

    database = fopen("database.txt", "r+");

    while(fgets(line, 512, database)){
        Crypto newOp;

        for(int i=0; i<=strlen(line); i++){
            if(line[i] == '-'){
                strncpy(newOp.name, line, i);
                *newOp.op =  line[i+1];
            }

            if(line[i] == '='){
                int cont = i+1;

                while(line[cont] != ','){
                    cont++;
                }

                int start = i+1;
                int end = cont;
                char *text = line;
                char auxTextQty[strlen(line)][10];
                char auxTextPrice[strlen(line)][10];

                strncpy(auxTextQty[i], &text[start], end-start);

                newOp.qty = atof(auxTextQty[i]);

                start = end+1;
                end = (strlen(line))-2;

                strncpy(auxTextPrice[i], &text[start], (end-start)+1);

                newOp.price = atof(auxTextPrice[i]);
            }
        }

        head = fillOpsList(newOp, head, price);
    }

    fclose(database);

    return head;
}

Crypto* initializeList(Crypto *head){
    head = (Crypto*) malloc(sizeof(Crypto));

    return head;
}

void main(){
    Crypto *head = NULL;
    Price *price = (Price*) malloc(sizeof(Price));

    FILE *database;

    head = initializeList(head);

    head = readDatabase(database, head, price);

    getCurrentPrice(price);

    printOpsList(head);

    while(1){
        fflush(stdin);
        head = newOp(head, price);

        getCurrentPrice(price);
        printOpsList(head);
    }
}