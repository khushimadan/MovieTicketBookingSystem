#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

void payment_module(int no_tickets,int ticket_price,int total_snackprice,char movie_name[50],char multiplex[10],char movie_date[10],char seats[100],char hall[10],char movie_time[10],char language[10],char region[10]){
    void generate_Mticket(int no_tickets,char Transaction_ID[],float total_amount,char movie_name[50],char multiplex[10],char movie_date[10],char seats[100],char hall[10],char movie_time[10],char language[10],char region[10])
	{
        printf("***M-TICKET***\n");
        printf("%s\n",movie_name);
        printf("%s\n",language);
        printf("%s : %s\n",movie_date,movie_time);
        printf("%s : %s\n",multiplex,region);
        printf("%d Ticket(s)\n",no_tickets);
        printf("AUDI %s\n",hall);
        printf("PREMIMUM- %s\n",seats);
        printf("Booking ID: %s\n",Transaction_ID);
        printf("Total Amount: %.2f\n",total_amount);
        printf("Thank you for booking your tickets with us!");
    }
    void generate_bill(char Transaction_ID[],float total_amount, float tax,int no_tickets,float amount){
        printf("****PAYMENT SUCCESSFUL!****\n");
        printf("Transaction ID = %s\n",Transaction_ID);
        printf("%d Tickets = Rs.%.2f\n",no_tickets,amount);
        printf("Integrated GST (IGST) @18% = Rs.%.2f\n",tax);
        printf("Amount Paid = Rs.%.2f\n",total_amount);
    }
    int length(int num){
    int len=0;
    while(num!=0){
        num=num/10;
        len++;
    }
    return len;
    }
    float check_code(char code[],float amount){
            if (strcmp(code,"DIWALI10")==0){
                float discount=0.1*amount;
                amount-=discount;
            }
            else if (strcmp(code,"DIWALI20")==0){
                float discount=0.2*amount;
                amount-=discount;
            }
            else if (strcmp(code,"DIWALI30")==0){
                float discount=0.3*amount;
                amount-=discount;
            }
            else{
                printf("Enter Valid Code:");
                scanf("%s",code);
                check_code(code,amount);
            }
            return amount;
    }
    int check_details(long long int card_no,int CVV,int exp_month,int exp_year,char name[]){
        int valid=1;
        int len_cardno=0;
        long long int cardno_copy=card_no;
        while(cardno_copy!=0){
            cardno_copy=cardno_copy/10;
            len_cardno++;
        }
        if (len_cardno!=16){
            valid+=1;
        }
        int len_CVV=length(CVV);
        if (len_CVV!=3){
            valid+=1;
        }
        if (exp_month>12 || exp_month<=0){
            valid+=1;
        }
        int len_expyear=length(exp_year);
        if (len_expyear!=2){
            valid+=1;
        }
        if (exp_year<23){
            valid+=1;
        }
        if (name==NULL){
            valid+=1;
        }
        return valid;
    }
    float amount,total_amount,tax;
    char code[100];
    int CVV,exp_month,exp_year;
    long long int card_no;
    char name[50];
    amount=(no_tickets*ticket_price)+total_snackprice;
    tax=(0.18)*amount;
    total_amount=amount+tax;
    printf("Amount Payable = Rs.%.2f\n",total_amount);
    printf("**DISCOUNTS/VOUCHERS**\n");
    if (amount>=1000 && amount<2000){
        printf("Use DIWALI10 to get 10 percent off!\n");
        printf("Enter Code:");
        scanf("%s",code);
        amount=check_code(code,amount);
    }
    else if (amount>=2000 && amount<3000){
        printf("Use DIWALI20 to get 20 percent off!\n");
        printf("Enter Code:");
        scanf("%s",code);
        amount=check_code(code,amount);
    }
    else if (amount>=3000){
        printf("Use DIWALI30 to get 30 percent off!\n");
        printf("Enter Code:");
        scanf("%s",code);
        amount=check_code(code,amount);
    }
    else{
        printf("No discounts applicable!");
    }
    tax=(0.18)*amount;
    total_amount=amount+tax;
    printf("Amount Payable after discount = Rs.%.2f\n",total_amount);
    printf("Choose a payment method:\n");
    printf("Enter 1 to pay via Credit Card\n");
    printf("Enter 2 to pay via Debit Card\n");
    printf("Enter your choice:");
    int choice;
    scanf("%d",&choice);
    switch (choice){
            case 1:
            printf("Enter Credit Card number:");
            scanf("%lld",&card_no);
            printf("Enter Name on the card:");
            scanf(" %[^\n]",name);
            printf("Enter CVV:");
            scanf("%d",&CVV);
            printf("Enter Expiry (MM/YY):");
            scanf("%d/%d",&exp_month,&exp_year);
            break;
        
            case 2:
            printf("Enter Debit Card number:");
            scanf("%lld",&card_no);
            printf("Enter Name on the card:");
            scanf(" %[^\n]",name);
            printf("Enter CVV:");
            scanf("%d",&CVV);
            printf("Enter Expiry (MM/YY):");
            scanf("%d/%d",&exp_month,&exp_year);
            break;
        
            default: printf("Invalid Option!");
            return;
    }
    printf("\n");
    int valid=check_details(card_no,CVV,exp_month,exp_year,name);
    if (valid!=1){
        printf("Invalid Details!\n");
        printf("Payment Unsuccessful!");
        return;
    }
    srand(time(NULL));
    char generateRandomchar(){
        int randomnum=rand()%62;
        if (randomnum<10){
            return '0' + randomnum;
        }
        else if (randomnum<36){
            return 'a'+ (randomnum-10);
        }
        else{
            return 'A'+ (randomnum-36);
        }
    }
    char Transaction_ID[13];
    int i;
    for (i=0;i<12;i++){
        Transaction_ID[i]=generateRandomchar();
    }
    Transaction_ID[12]='\0';
    generate_bill(Transaction_ID,total_amount,tax,no_tickets,amount);
    printf("To Generate an M-Ticket enter 1 else 0:");
    int choice2;
    scanf("%d",&choice2);
    if (choice2==1){
    generate_Mticket(no_tickets,Transaction_ID,total_amount,movie_name,multiplex,movie_date,seats,hall,movie_time,language,region);
    return;
    }
    else{
        printf("Thank you for booking your ticket with us!");
        return;
    }
}
//actual main after receiving details from customer module 1 and 2
/*
int main(){
    payment_module(no_tickets,ticket_price,total_snackprice,movie_name,multiplex,movie_date, seats, hall,movie_time,language, region);
    return 0;
}
*/ 

//using test case 1 for execution before compiling with other modules
int main(){
    payment_module(2,500,600,"Jawan","PVR","12/11/2023","H-12,H-13","A","12 pm","Hindi","Delhi");
    return 0;
}

