/*  Dabana Intenque, Kefron Grant, and Briana Santos*/
void printChar(char c);
void printString(char*);
void readString(char*);
void readSector(char*, int);
void handleInterrupt21(int ax, int bx, int cx, int dx);
void readFile (char* buffer, char* filename, int* sectorsreadptr);
void executeProgram(char* name);
void terminate();

void main(){
	//char buffer[13312];   /*this is the maximum size of a file*/
	//int sectorsRead;
	makeInterrupt21(); 
	//interrupt(0x21, 3, "messag", buffer, &sectorsRead);   /*read the file into buffer*/ 
	//if (sectorsRead>0)
    //    //interrupt(0x21, 0, "printing\r\n", 0, 0);
	//	interrupt(0x21, 0, buffer, 0, 0);   /*print out the file*/ 
	//else
	//	interrupt(0x21, 0, "messag not found\r\n", 0, 0);  /*no sectors read? then print an error*/
    interrupt(0x21,4,"shell",0,0);
	while(1){ //DONT LEAVE KERNEL
	}
}
void printChar(char c){
	interrupt(0x10, 0xe*256+c,0,0,0);
}
void printString(char* chars){
	int i = 0;
	while(chars[i] != '\0'){
		printChar(chars[i]); //interrupt print
		i++;
	}
}
void readString(char* line){
    //interrupt(0x21,0,"Enter a line: ",0,0);
	int c = interrupt(0x16,0,0,0,0);
    int i = 0;
    //printString("Enter a line: ");

	while(c != 0xd){
		if(c == 0x8){
			if(i > 0){
				i--;
				printChar(c);
				printChar(' ');
				printChar(c);
			}
        } else {
        line[i] = c;
		printChar(c); 
		i++;
        }
    c = interrupt(0x16,0,0,0,0);
	}
    printChar(0x0);
    printChar(0xd);
    printChar(0xa);
}
void readSector(char* buffer, int sector){
	interrupt(0x13, 2*256+1, buffer, 0*256+sector+1, 0*256+0x80);
}
void handleInterrupt21(int ax, int bx, int cx, int dx){
    //printString("Interrupting cow has mooed today\n");
    if (ax == 0){
        printString(bx);
    } else if (ax == 1) {
        readString(bx);
    } else if (ax == 2) {
        readSector(bx, cx);
    } else if (ax == 3) {
        readFile(bx, cx, dx);    
    } else if (ax == 4) {
        executeProgram(bx);
    } else if (ax == 5) {
        terminate();
    }
    
}
void readFile (char* filename, char* buffer, int* sectorsreadptr){  //int* sectorsreadptr
    //find the file
    
    char dir[512];
    int entry;
    int letter;
    int foundfile;
    int s;
    int sector;
    readSector(dir, 2);
    for (entry = 0; entry < 512; entry+=32){
        foundfile = 1;
        for (letter = 0; letter < 6; letter++){
            if (filename[letter] != dir[letter+entry]){
                foundfile = 0;
                break;
            }
        }
        if(foundfile == 1){
            break;
        }
    }
    if (foundfile == 0){
            *sectorsreadptr = 0;
            return;
        }
    for (s = 6; s<26; s++){
        sector = dir[entry+s];
        if (sector == 0){
            break;
        }
        readSector(buffer, sector);
        buffer += 512;
        *sectorsreadptr=*sectorsreadptr+1;
    } 
}
void executeProgram(char* name){
    char buffer[13312];
    int seg = 0x2000;
    int i;
    readFile(name, buffer);
    while(i<13312){
    putInMemory(seg, i, buffer[i]);
    i++;
    }
    launchProgram(seg);
}
void terminate(){
    char shellname[6];
    while(1){
    shellname[0] = 's';
    shellname[1] = 'h';
    shellname[2] = 'e';
    shellname[3] = 'l';
    shellname[4] = 'l';
    shellname[5] = '\0';
    }
    executeProgram(shellname);
}
