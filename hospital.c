#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct patient
{
    char name[50];
    int age;
    char disease[50];
    long int phone_no;
    char address[50];
};

void add(struct patient p[],int n)
{
	FILE*fp;
	fp=fopen("Patient.bin","ab");
	if(fp==NULL)
	{
		printf("File cannot be opened.\n");
		return;
	}
	int i;
	printf("Enter the no of patients to add:");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("Patient No: %d\n",i+1);
		fflush(stdin);
		printf("Enter the name:");
		scanf("%s",p[i].name);
		fflush(stdin);
		printf("Enter the disease of patient:");
		scanf("%s",p[i].disease);
		fflush(stdin);
		printf("Enter the address of patient:");
		scanf("%s",p[i].address);
		printf("Enter the age and phone no:");
		scanf("%d%ld",&p[i].age,&p[i].phone_no);
		fwrite(&p[i], sizeof(struct patient), 1, fp);
	}
	fclose(fp);
}

void view(struct patient p[], int n)
{
    FILE *fp;
    fp = fopen("Patient.bin", "rb");
    if (fp == NULL) 
	{
        printf("File cannot be opened.\n");
        return;
    }
    
    while (fread(&p[n], sizeof(struct patient), 1, fp)) 
	{
        printf("Name: %s\n", p[n].name);
        printf("Disease: %s\n", p[n].disease);
        printf("Address: %s\n", p[n].address);
        printf("Age: %d\n", p[n].age);
        printf("Phone No: %ld\n\n", p[n].phone_no);
    }
    
    fclose(fp);	
}
void search(struct patient p[],int n)
{
	int i,s,pn;
	char nam[50];
	FILE *fp;
	fp=fopen("Patient.bin","rb");
	if(fp == NULL) {
        printf("File cannot be opened.\n");
        return;
    }
	printf("What do you want to search by:\n1.Patient No\t2.Name\n");
	scanf("%d",&s);
	if(s==1)
	{
		printf("Enter the patient number:");
		scanf("%d",&pn);
		fscanf(fp,"%s%s%s%d%ld",p[pn-1].name,p[pn-1].disease,p[pn-1].address,&p[pn-1].age,&p[pn-1].phone_no);
		printf("Name of the patient is %s",p[pn-1].name);
		printf("\nDisease is %s and address is %s",p[pn-1].disease,p[pn-1].address);
		printf("\n The patient's age is %d and phone no is %ld",p[pn-1].age,p[pn-1].phone_no);
		
	}
	else if(s==2)
	{
		printf("Enter the name of patient:");
		scanf("%s",nam);
		for(i=0;i<n;i++)
		{
			if(strcmp(p[i].name,nam)==0)
			{
				fscanf(fp,"%s%s%s%d%ld",p[i].name,p[i].disease,p[i].address,p[i].age,p[i].phone_no);
				printf("Name of the patient is %s",p[i].name);
				printf("\nDisease is %s and address is %s",p[s-1].disease,p[i].address);
				printf("\n The patient's age is %d and phone no is %ld",p[i].age,p[i].phone_no);
			}
		}
	}
	fclose(fp);
}
void del(struct patient p[],int n)
{
	FILE *fp,*temp;
	fp=fopen("Patient.bin","rb+");
	if(fp==NULL)
	{
		printf("File cannot be opened.");
		return;
	}
	temp=fopen("temp.bin","wb");
	if(temp==NULL)
	{
		printf("Temporary file cannot be created.");
		return;
	}
	int pn;
	printf("Enter the patient number to be deleted:");
	scanf("%d",&pn);
	while(fread(&p[n],sizeof(struct patient),1,fp))
	{
		if(n+1!=pn)
			fwrite(&p[n],sizeof(struct patient),1,temp);
			n++;
	}
	fclose(fp);
	fclose(temp);
	remove("Patient.bin");
	rename("temp.bin","Patient.bin");
}
int main()
{
    struct patient p[100];
    int ch,n=0;
    FILE *fp;
    fp = fopen("Patient.bin", "rb");
    if (fp == NULL) {
        printf("File is not created.\n");
    } else {
        printf("File is successfully created.\n");
        while (fread(&p[n], sizeof(struct patient), 1, fp)) {
            n++;
        }
        fclose(fp);
    }
    printf("1. Add \n2. View \n3. Search\n4. Delete\n");
    
    printf("Enter the choice:");
    scanf("%d",&ch);
    switch(ch)
    {
    	case 1: add(p,n);
    	break;
    	
    	case 2: view(p,n);
		break;
		
		case 3: search(p,n);
		break;
		
		case 4: del(p,n);
		break;
		
		default: printf("Invalid input");
	}
	return 0;
}
