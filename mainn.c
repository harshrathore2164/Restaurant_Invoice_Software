#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

struct items
{
    char item[20];
    float price;
    int qty;
};

struct orders
{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};

// function to generate bills
void generateBillHeader(char name[50], char date[30])
{
    printf("\n\n");
    printf("\t     MKC Restaurant");
    printf("\n\t     ----------------------");
    printf("\nDate:%s", date);
    printf("\nInvoice To: %s", name);
    printf("\n");
    printf("----------------------------------------\n");
    printf("Items\t\t");
    printf("Quantity\t\t");
    printf("Total\t\t");
    printf("\n---------------------------------------");
    printf("\n\n");
}

void generateBillBody(char item[30], int qty, float price)
{

    printf("%s\t\t", item);
    printf("%d\t\t", qty);
    printf("%.2f\t\t", qty * price);
    printf("\n");
}

void generateBillFooter(float total)
{
    printf("\n");
    float dis = 0.1 * total;
    float netTotal = total - dis;
    float cgst = 0.09 * netTotal, grandTotal = netTotal + 2 * cgst;
    printf("-----------------------------------------------\n");
    printf("SubTotal\t\t\t%.2f", total);
    printf("\nDiscount @10%s\t\t\t%.2f", "%", dis);
    printf("\n\t\t\t\t-------");
    printf("\nNetTotal\t\t\t%.2f", netTotal);
    printf("\nCGST @9%s\t\t\t%.2f", "%", cgst);
    printf("\nSGST @9%s\t\t\t%.2f", "%", cgst);
    printf("\n--------------------------------------------");
    printf("\nGrand Total\t\t\t%.2f", grandTotal);
    printf("\n--------------------------------------------\n");
}

int snakewatergun(char you, char comp)
{

    // for draw
    if (you == comp)
    {
        return 0;
    }
    // for other outcomes

    if (you == 's' && comp == 'w')
    {
        return 1;
    }

    else if (you == 'w' && comp == 's')
    {
        return -1;
    }

    if (you == 's' && comp == 'g')
    {
        return -1;
    }

    else if (you == 'g' && comp == 's')
    {
        return 1;
    }

    if (you == 'w' && comp == 'g')
    {
        return 1;
    }

    else if (you == 'g' && comp == 'w')
    {
        return -1;
    }

    if (you == 'g' && comp == 'w')
    {
        return -1;
    }

    else if (you == 'w' && comp == 'g')
    {
        return 1;
    }
    return 0;
}

int main()
{
    int opt, n;
    float total = 0;
    struct orders ord, order;
    char saveBill = 'y', name[50], contFlag = 'y';
    FILE *fp;
    int number;
    char you, comp;
    srand(time(0));
    number = rand() % 100 + 1;

    while (contFlag == 'y')
    {
        int invoiceFound = 0;
        float total = 0;
        printf("\t=============MKC RESTAURANT=============");
        printf("\n\n Please select your preferred operation");
        printf("\n\n1. Generate Inovice");
        printf("\n2. Show all Inovices");
        printf("\n3. Search  Invoices");
        printf("\n4. Play A Game");
        printf("\n5. Exit");
        printf("\n\nYour Choice:\t");
        scanf("%d", &opt);
        printf("\nYou have chosen: %d", opt);
        fgetc(stdin);
        switch (opt)
        {
        case 1:
            system("clear");
            printf("\nPlease enter the name of the customer:\t");
            fgets(ord.customer, 50, stdin);
            ord.customer[strlen(ord.customer) - 1] = 0;
            strcpy(ord.date, __DATE__);
            printf("\nPlease enter the number of items:\t");
            scanf("%d", &n);
            ord.numOfItems = n;
            for (int i = 0; i < n; i++)
            {
                fgetc(stdin);
                printf("\n\n");
                printf("Please enter the item %d name:\t", i + 1);
                fgets(ord.itm[i].item, 20, stdin);
                ord.itm[i].item[strlen(ord.itm[i].item) - 1] = 0;
                printf("\nPlease enter the quantity:\t");
                scanf("%d", &ord.itm[i].qty);
                printf("\nPlease neter the unit price:\t");
                scanf("%f", &ord.itm[i].price);
                total += ord.itm[i].qty * ord.itm[i].price;
            }
            generateBillHeader(ord.customer, ord.date);
            for (int i = 0; i < ord.numOfItems; i++)
            {
                generateBillBody(ord.itm[i].item, ord.itm[i].qty, ord.itm[i].price);
            }
            generateBillFooter(total);
            printf("\nDo you want to save the invoice?[y/n]:\t");
            scanf("%s", &saveBill);

            if (saveBill == 'y')
            {
                fp = fopen("RestaurantBill.txt", "a+");
                fwrite(&ord, sizeof(struct orders), 1, fp);
                if (&fwrite != 0)
                    printf("\nSuccessfully saved\n");
                else
                    printf("\nError saving\n");
                fclose(fp);
            }
            break;
        case 2:
            system("clear");
            fp = fopen("RestaurantBill.txt", "r");
            printf("\n *****Your Previous Invoices*****\n");
            while (fread(&order, sizeof(struct orders), 1, fp))
            {
                float tot = 0;
                generateBillHeader(order.customer, order.date);
                for (int i = 0; i < order.numOfItems; i++)
                {
                    generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                    tot += order.itm[i].qty * order.itm[i].price;
                }
                generateBillFooter(tot);
            }
            fclose(fp);
            break;

        case 3:
            printf("\nEnter the name of the customer:\t");
            fgets(name, 50, stdin);
            name[strlen(name) - 1] = 0;
            system("clear");
            fp = fopen("RestaurantBill.txt", "r");
            printf("\t*****Invoice of %s*****", name);
            while (fread(&order, sizeof(struct orders), 1, fp))
            {
                float tot = 0;
                if (!strcmp(order.customer, name))
                {
                    generateBillHeader(order.customer, order.date);
                    for (int i = 0; i < order.numOfItems; i++)
                    {
                        generateBillBody(order.itm[i].item, order.itm[i].qty, order.itm[i].price);
                        tot += order.itm[i].qty * order.itm[i].price;
                    }
                    generateBillFooter(tot);
                    invoiceFound = 1;
                }
            }
            if (!invoiceFound)
            {
                printf("Sorry the invoice for %s does not exist", name);
            }
            fclose(fp);
            break;

        case 4:

            if (number < 33)
            {
                comp = 's';
            }

            else if (number > 33 && number < 66)
            {
                comp = 'w';
            }

            else
            {
                comp = 'g';
            }

            printf("\nChoose 's' for snake , 'w' for water or 'g' for gun:\n");
            scanf("%c", &you);

            int result = snakewatergun(you, comp);
            printf("You chose %c and computer chose %c\n", you, comp);

            if (result == 0)
            {
                printf("Game is draw!!");
            }

            else if (result == 1)
            {
                printf("You Won!!\n");
            }

            else
            {
                printf("You Lost!!\n");
            }
            break;

        case 5:
            printf("\n\t\t Bye Bye :)\n\n");
            exit(0);
            break;

        default:
            printf("Sorry Invalid Option");
            break;
        }
        printf("\nDo you want to perform another operation?[y/n]:\t");
        scanf("%s", &contFlag);
    }

    return 0;
}