 #include <stdio.h>
#include <stdlib.h>
#include <string.h>


//khai bao cac truct
typedef struct{
	char id[20];
	char title[100];
	char author[50];
	float price;
	char category[50];
} Book;

typedef struct{
	char memberId[20];
	char name[50];
	char phone[50];
} Member;


//khai bao nguyen mau ham

//day la ham quan li sach
int readBook(Book books[]);
void writeBook(Book books[],int count);
void displayBook(Book books[],int count);
int decentBook(Book book, Book books[], int count);
void addBook(Book books[], int *count);
void editBook(Book books[], int count);
void deleteBook(Book books[], int *count);
void sortBook(Book books[], int count);
void searchBook(Book books[],int count);

//day la ham quan li khach hang
int readMem(Member members[]);
void writeMem(Member members[],int flag);
void displayMember(Member members[],int flag);
int decentMember(Member member, Member members[],int flag);
void addMember(Member members[],int *flag);
void editMember(Member members[], int flag);
void searchMember(Member members[],int flag);
//main
int main(){
	int choose = 0;
	Book books[100];
	int count = readBook(books);
	
	Member members[100];
	int flag = readMem(members);
	//quan li sach
	do {
        printf("             MENU\n");
        printf("=================================\n");
        printf("1. Quan ly sach\n");
        printf("2. Quan ly khach hang\n");
        printf("3. Thoat\n");
        printf("=================================\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choose);
        
        switch (choose) {
            case 1: {
                int bookChoice;
                do {
                    printf("===== QUAN LY SACH =====\n");
                    printf("1. Hien thi danh sach sach\n");
                    printf("2. Them sach\n");
                    printf("3. Sua thong tin sach\n");
                    printf("4. Xoa sach\n");
                    printf("5. Sap xep sach theo gia tien\n");
                    printf("6. Tim kiem sach theo ten\n");
                    printf("7. Thoat\n");
                    
                    printf("Nhap lua chon cua ban: ");
                    scanf("%d", &bookChoice);
                    
                    switch (bookChoice) {
                        case 1: {
                            displayBook(books, count);
                            break;
                        }
                        case 2: {
                            addBook(books, &count);
                            break;
                        }
                        case 3: {
                        	
							
                            editBook(books, count);
                            break;
                        }
                        case 4:{
                        	deleteBook(books,&count);
							break;
						}
						case 5:{
							sortBook(books,count);
							break;
						}
						case 6:{
							searchBook(books,count);
							break;
						}
							
                        
                        
                        
                    }
                } while (bookChoice != 7);
                break;
            }
            //quan li khach hang
            case 2: {
                int memberChoose=0;
                do {
                    printf("===== QUAN LY KHACH HANG =====\n");
                    printf("1. Hien thi danh sach khach hang\n");
                    printf("2. Them khach hang\n");
                    printf("3. Sua thong tin khach hang\n");
                    printf("4. Tim kiem thong tin khach hang\n");
                    printf("7. Thoat\n");
                    printf("Moi ban nhap lua chon: ");
                    scanf("%d",&memberChoose);
                    switch(memberChoose){
                    	case 1:{
                    		displayMember(members,flag);
							break;
						}
						case 2:{
							addMember(members,&flag);
							break;
						}
						case 3:{
							editMember(members,flag);
							break;
						}
						case 4:{
							searchMember(members,flag);
							break;
						}
					}
                    
                    
                    
                } while(memberChoose!=7);
                break;
            }
            case 3:
                printf("Thoat chuong trinh.\n");
                break;
            
        }
    } while (choose != 3);
	
	return 0;
}


//trien khai cac ham


//day la ham quan li sach
int readBook(Book books[]){
	int count=0;
	FILE *file = fopen("book.bin","rb");
	if(file == NULL){
		return 0;
	}
	while(fread(&books[count],sizeof(Book),1,file)){
		count++;
		
	}
	fclose(file);
}

void writeBook(Book books[],int count){
	FILE *file = fopen("book.bin", "wb");
    if (file == NULL) {
        printf("Khong the mo file\n");
        return;
    }
    fwrite(books, sizeof(Book), count, file);
    fclose(file);
}
void displayBook(Book books[], int count){
	
	printf("| %-5s | %-30s | %-25s | %-10s | %-15s |\n", "ID", "Title", "Author", "Price", "Category");
    printf("|-------|--------------------------------|---------------------------|------------|-----------------|\n");
    for (int i=0;i<count;i++) {
        printf("| %-5s | %-30s | %-25s | %-10.f | %-15s |\n", books[i].id, books[i].title, books[i].author, books[i].price, books[i].category);
    }
}

int decentBook(Book book, Book books[], int count){
	
	if(book.id<=0||book.price<=0){
		printf("Ma hoac gia sach khong hop le, vui long nhap lai: \n");
		return 0;
	}
	if(strlen(book.title)==0||strlen(book.author)==0||strlen(book.category)==0){
		printf("Vui long nhap thong tin sach: \n");
		return 0;
	}
	for(int i=0;i<count;i++){
		if(strcmp(books[i].id,book.id)==0){
			printf("Id da ton tai, vui long nhap lai: \n");
			return 0;
		}
		if (strcmp(books[i].title, book.title) == 0) {
            printf("Ten sach da ton tai, vui long nhap lai: \n");
            return 0;
        }
	}
	
	return 1;
}


void addBook(Book books[], int *count){
	Book book;
	
	
    printf("Nhap ma sach: ");
    scanf("%s", &book.id);
    getchar();
    printf("Nhap ten sach: ");
    fgets(book.title, sizeof(book.title), stdin);
    book.title[strcspn(book.title, "\n")] = 0;
    printf("Nhap tac gia: ");
    fgets(book.author, sizeof(book.author), stdin);
    book.author[strcspn(book.author, "\n")] = 0;
    printf("Nhap gia sach: ");
    scanf("%f", &book.price);
    getchar();
    printf("Nhap the loai sach: ");
    fgets(book.category, sizeof(book.category), stdin);
    book.category[strcspn(book.category, "\n")] = 0;

	if (decentBook(book, books, *count)) {
        books[*count] = book;
        (*count)++;
        writeBook(books, *count);
        printf("Them sach thanh cong\n");
    } else {
        printf("Du lieu sach khong hop le. Vui long thu lai\n");
    }
}



void editBook(Book books[], int count){
	char idsr[50];
	char newTitle[50];
	char newAuthor[50];
	float newPrice;
	char newCategory[50];
	int ck=0;
	
	printf("Hay nhap id ban muon sua: ");
	scanf("%s",&idsr);
	
	
	
    
	for(int i=0;i<count;i++){
		if(strcmp(books[i].id, idsr) == 0){
			printf("| %-5s | %-30s | %-25s | %-10.f | %-15s |\n", books[i].id, books[i].title, books[i].author, books[i].price, books[i].category);
			printf("Nhap ten sach moi: ");
			getchar();
			fgets(newTitle,sizeof(newTitle),stdin);
			newTitle[strcspn(newTitle, "\n")] = 0;
			if(strlen(newTitle)==0){
				printf("Vui long nhap thong tin\n");
				return;
			}else{
				ck++;
				//strcpy(books[i].title,newTitle);
				//writeBook(books,count);
			}
			
			
			printf("Nhap tac gia moi: ");
			fgets(newAuthor,sizeof(newAuthor),stdin);
			newAuthor[strcspn(newAuthor, "\n")] = 0;
			if(strlen(newAuthor)==0){
				printf("Vui long nhap thong tin\n");
				return 0;
			}else{
				ck++;
				//strcpy(books[i].author,newAuthor);
				//writeBook(books,count);
			}
			
			
			printf("Nhap gia sach moi: ");
			scanf("%f",&newPrice);
			getchar();
			if(newPrice<=0){
				printf("Vui long nhap thong tin\n");
				return 0;
			}else{
				ck++;
				//books[i].price=newPrice;
				//writeBook(books,count);
			}
			
			printf("Nhap the loai sach moi: ");
			fgets(newCategory,sizeof(newCategory),stdin);
			newCategory[strcspn(newCategory, "\n")] = 0;
			if(strlen(newCategory)==0){
				printf("Vui long nhap thong tin\n");
				return 0;
			}else{
				ck++;
				//strcpy(books[i].category,newCategory);
			}
			if(ck==4){
				printf("Sua thong tin sach thanh cong");
				strcpy(books[i].title,newTitle);
				strcpy(books[i].author,newAuthor);
				books[i].price=newPrice;
				strcpy(books[i].category,newCategory);
				writeBook(books,count);
				
				
			}
			
			
			
			
			return;
			
		}
	}
	printf("Khong tim thay id\n");
	
}
void deleteBook(Book books[], int *count){
	char iddel[50];
	int choose=0;
	printf("Nhap id sach can xoa: ");
	scanf("%s",&iddel);
	printf("Ban co chac chan muon xoa quyen sach nay khoi thu vien?\n");
	printf("1. Co\n");
	printf("2. Khong\n");
	printf("Nhap lua chon cua ban: ");	
	scanf("%d",&choose);
	
	switch(choose){
		case 1: {
			for(int i=0;i<*count;i++){
				if(strcmp(books[i].id, iddel) == 0){
					for(int j=i;j<*count-1;j++){
						books[j]=books[j+1];
			}
			(*count)--;
			writeBook(books,*count);
			printf("Xoa sach thanh cong\n");
			return;
		}
	}
	printf("Id khong ton tai\n");
	
			break;
		}
		case 2: {
			
			break;
		}
	}
		
		

}
void sortBook(Book books[], int count){
	int choose=0;
	
		printf("1. Sap xep tang dan\n");
		printf("2. Sap xep giam dan\n");
		
		printf("Moi ban nhap lua chon: ");
		scanf("%d",&choose);
		switch(choose){
			case 1:{
				for (int i=0;i<count-1;i++) {
                    for (int j=i+1;j<count;j++) {
                        if (books[i].price > books[j].price) {
                            Book temp = books[i];
                            books[i] = books[j];
                            books[j] = temp;
                        }
                    }
                }
                printf("Sap xep thanh cong\n");
                displayBook(books,count);
                writeBook(books,count);
				break;
			}
			case 2:{
				for (int i=0;i<count-1;i++) {
                    for (int j=i+1;j<count;j++) {
                        if (books[i].price < books[j].price) {
                            Book temp = books[i];
                            books[i] = books[j];
                            books[j] = temp;
                        }
                    }
                }
                printf("Sap xep thanh cong\n");
                displayBook(books,count);
                writeBook(books,count);
				break;
			}
			
				
		}
	}
void searchBook(Book books[], int count){
	char namesrc[50];
	char nameTitlecheck[50];
	
	printf("Nhap ten sach muon tim kiem: ");
	getchar();
	fgets(namesrc,sizeof(namesrc),stdin);
	namesrc[strcspn(namesrc,"\n")]=0;
	
	for(int i=0;namesrc[i];i++){
		namesrc[i]=tolower(namesrc[i]);
	}
	
	
	for(int i=0;i<count;i++){
		//char nameTitlecheck[50];
		strcpy(nameTitlecheck,books[i].title);
		//printf("| %-5s | %-30s | %-25s | %-10s | %-15s |\n", "ID", "Title", "Author", "Price", "Category");
    	//printf("|-------|--------------------------------|---------------------------|------------|-----------------|\n");
		for(int j=0;nameTitlecheck[j];j++){
			nameTitlecheck[j] = tolower(nameTitlecheck[j]);
		}
			//printf("| %-5s | %-30s | %-25s | %-10s | %-15s |\n", "ID", "Title", "Author", "Price", "Category");
    		//printf("|-------|--------------------------------|---------------------------|------------|-----------------|\n");
		if(strstr(nameTitlecheck,namesrc)!=NULL){
			//printf("| %-5s | %-30s | %-25s | %-10s | %-15s |\n", "ID", "Title", "Author", "Price", "Category");
    		printf("|-------|--------------------------------|---------------------------|------------|-----------------|\n");
			printf("| %-5s | %-30s | %-25s | %-10.f | %-15s |\n", books[i].id, books[i].title, books[i].author, books[i].price, books[i].category);
		}else{
			printf("Khong tim thay sach\n");
		}
	}
}


//day la ham quan li khach hang
int readMem(Member members[]){
	int flag=0;
	FILE *file = fopen("member.bin","rb");
	if(file==NULL){
		return 0;
	}
	while(fread(&members[flag],sizeof(Member),1,file)){
		flag++;
	}
	fclose(file);
	
}
void writeMem(Member members[],int flag){
	FILE *file = fopen("member.bin","wb");
	if(file == NULL){
		printf("Khong the mo file\n");
		return;
	}
	fwrite(members,sizeof(Member),flag,file);
	fclose(file);
}
void displayMember(Member members[], int flag){
	printf("| %-5s | %-30s | %-25s |\n", "ID", "Name", "Phone");
    printf("|-------|--------------------------------|---------------------------|\n");
    for (int i=0;i<flag;i++) {
        printf("| %-5s | %-30s | %-25s |\n", members[i].memberId, members[i].name, members[i].phone);
    }
}
int decentMember(Member member, Member members[],int flag){
	
	if(member.memberId<=0||member.phone<=0){
		printf("Id hoac so dien thoai khong hop le");
	}
		//printf("check 1 %s",member.memberId);
	if(strlen(member.name)<=0){
		printf("Vui long nhap thong tin cua khach hang");
		return 0;
	}
		//printf("check 2 %d",flag);
	for(int i=0;i<flag;i++){
		if(members[i].memberId==member.memberId){
			printf("Id da ton tai, vui long nhap lai: \n");
			
		}
		
	}
	return 1;
}
void addMember(Member members[], int *flag) {
    Member member;
    
    printf("Nhap ma khach hang: ");
    scanf("%s", &member.memberId);
    getchar();
    
    printf("Nhap ten khach hang: ");
    fgets(member.name, sizeof(member.name), stdin);
    member.name[strcspn(member.name, "\n")] = 0;
    
    printf("Nhap so dien thoai: ");
    //scanf("%f",&member.phone);
    //getchar();
    fgets(member.phone, sizeof(member.phone), stdin);
    member.phone[strcspn(member.phone, "\n")] = 0;

    if (decentMember(member,members, *flag)) {
        members[*flag] = member;
        (*flag)++;
        writeMem(members, *flag);
        printf("Them khach hang thanh cong\n");
    } else {
        printf("Du lieu khong hop le. Vui long thu lai.\n");
    }
    
    
}

void editMember(Member members[],int flag){
	char idSrcmem[20];
	char newName[50];
	char newPhone[50];
	int ok=0;
	
	printf("Nhap id khach hang: ");
	scanf("%s",&idSrcmem);
	
	for(int i=0;i<flag;i++){
		if(strcmp(members[i].memberId,idSrcmem)==0){
			printf("| %-15s | %-50s | %-15s |\n", "Member ID", "Name", "Phone");
            printf("|-----------------|----------------------------------------------------|-----------------|\n");
            printf("| %-15s | %-50s | %-15s |\n", members[i].memberId, members[i].name, members[i].phone);
            
            printf("Nhap ten moi: ");
            getchar();
            fgets(newName,sizeof(newName),stdin);
            newName[strcspn(newName, "\n")] = 0;
            if(strlen(newName)==0){
            	printf("Vui long nhap thong tin\n");
            	return 0;
            	
			}else{
				ok++;
			}

            
            printf("Nhap so dien thoai moi: ");
            fgets(newPhone,sizeof(newPhone),stdin);
            newPhone[strcspn(newPhone, "\n")] = 0;
            if(strlen(newPhone)==0){
            	printf("Vui long nhap thong tin\n");
            	return 0;
            	
			}else{
				ok++;
				
			}
			if(ok==2){
				printf("Cap nhap thong tin thanh cong\n");
				strcpy(members[i].name,newName);
				strcpy(members[i].phone,newPhone);
				writeMem(members,flag);
			}
            
            //writeMem(members,flag);
            //printf("Cap nhap thong tin thanh cong\n");
            return;
		}
	}
	printf("Khong tim thay id khach hang\n");
}
searchMember(Member members[],int flag){
	char memberSrc[50];
	char memberCheck[50];
	int check=0;
	
	printf("Nhap ten khach hang can tim: ");
	getchar();
	fgets(memberSrc,sizeof(memberSrc),stdin);
	memberSrc[strcspn(memberSrc,"\n")]=0;
	
	for(int i=0;memberSrc[i];i++){
		memberSrc[i]=tolower(memberSrc[i]);
	}
	
	for(int i=0;i<flag;i++){
		strcpy(memberCheck,members[i].name);
		for(int j=0;memberCheck[j];j++){
			memberCheck[j]=tolower(memberCheck[j]);
			
		}
		if(strstr(memberCheck,memberSrc)!=NULL){
			//printf("| %-5s | %-30s | %-25s |\n", "ID", "Name", "Phone");
    		printf("|-------|--------------------------------|---------------------------|\n"); 		
        	printf("| %-5s | %-30s | %-25s |\n", members[i].memberId, members[i].name, members[i].phone);		
	}else{
		printf("Khong tim thay khach hang\n");
	}
	
	
}
}








