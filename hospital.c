#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct patient
{
    char name[50];
    int age;
    char disease[50];
    long int phone_no;
    char address[50];
};

void add(struct patient p[], int n)
{
    FILE *fp;
    fp = fopen("Patient.bin", "ab");
    if (fp == NULL)
    {
        printf("File cannot be opened.\n");
        return;
    }
    int i;
    printf("Enter the no of patients to add:");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Patient No: %d\n", i + 1);
        fflush(stdin);
        printf("Enter the name:");
        scanf("%s", p[i].name);
        fflush(stdin);
        printf("Enter the disease of patient:");
        scanf("%s", p[i].disease);
        fflush(stdin);
        printf("Enter the address of patient:");
        scanf("%s", p[i].address);
        printf("Enter the age and phone no:");
        scanf("%d %ld", &p[i].age, &p[i].phone_no);
        fwrite(&p[i], sizeof(struct patient), 1, fp);
    }
    fclose(fp);
}

void view()
{
    FILE *fp;
    int i=1;
    struct patient p;
    fp = fopen("Patient.bin", "rb");
    if (fp == NULL)
    {
        printf("File cannot be opened.\n");
        return;
    }

    while (fread(&p, sizeof(struct patient), 1, fp))
    {
    	printf("Patient No: %d\n",i);
        printf("Name: %s\n", p.name);
        printf("Disease: %s\n", p.disease);
        printf("Address: %s\n", p.address);
        printf("Age: %d\n", p.age);
        printf("Phone No: %ld\n", p.phone_no);
        i++;
    }

    fclose(fp);
}

void search()
{
    int s;
    char nam[50];
    FILE *fp;
    struct patient p;
    fp = fopen("Patient.bin", "rb");
    if (fp == NULL)
    {
        printf("File cannot be opened.\n");
        return;
    }
    printf("What do you want to search by:\n1.Patient No\t2.Name\n");
    scanf("%d", &s);
    if (s == 1)
    {
        int pn;
        printf("Enter the patient number:");
        scanf("%d", &pn);
        fseek(fp, (pn - 1) * sizeof(struct patient), SEEK_SET);
        if (fread(&p, sizeof(struct patient), 1, fp))
        {
            printf("Name of the patient is %s", p.name);
            printf("\nDisease is %s and address is %s", p.disease, p.address);
            printf("\nThe patient's age is %d and phone no is %ld", p.age, p.phone_no);
        }
        else
        {
            printf("Patient not found.\n");
        }
    }
    else if (s == 2)
    {
        printf("Enter the name of patient:");
        scanf("%s", nam);
        int found = 0;
        while (fread(&p, sizeof(struct patient), 1, fp))
        {
            if (strcmp(p.name, nam) == 0)
            {
                printf("Name of the patient is %s", p.name);
                printf("\nDisease is %s and address is %s", p.disease, p.address);
                printf("\nThe patient's age is %d and phone no is %ld", p.age, p.phone_no);
                found = 1;
                break;
            }
        }
        if (!found)
        {
            printf("Patient not found.\n");
        }
    }
    fclose(fp);
}

void del()
{
    FILE *fp, *temp;
    struct patient p;
    int pn;
    fp = fopen("Patient.bin", "rb");
    if (fp == NULL)
    {
        printf("File cannot be opened.");
        return;
    }
    temp = fopen("temp.bin", "wb");
    if (temp == NULL)
    {
        printf("Temporary file cannot be created.");
        return;
    }
    printf("Enter the patient number to be deleted:");
    scanf("%d", &pn);
    int f= 0;
    while (fread(&p, sizeof(struct patient), 1, fp))
    {
        if (pn!= f+1)
        {
            fwrite(&p, sizeof(struct patient), 1, temp);
        }
        else
        {
            f++;
        }
    }
    fclose(fp);
    fclose(temp);
    remove("Patient.bin");
    rename("temp.bin", "Patient.bin");
    if(f)
    {
        printf("Patient deleted successfully.\n");
    }
    else
    {
        printf("Patient not found.\n");
    }
}

int main()
{
    int ch, n = 0;
    struct patient p[100];
    FILE *fp;
    fp = fopen("Patient.bin", "rb");
    if (fp == NULL)
    {
        printf("File is not created.\n");
    }
    else
    {
        printf("File is successfully created.\n");
        fclose(fp);
    }
    printf("1. Add \n2. View \n3. Search\n4. Delete\n");
    printf("Enter the choice:");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        add(p,n);
        break;
    case 2:
        view();
        break;
    case 3:
        search();
        break;
    case 4:
        del();
        break;
    default:
        printf("Invalid input");
    }
    return 0;
}
