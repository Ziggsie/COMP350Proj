void printString(char*);
void readString(char*);
void readSector(char*, int);
void main(){
	//printString("Hello World");
	//char line[80];
	//printString("Enter a line: ");
	//readString(line);
	//printString(line);
	//char buffer[512];      //If these work, then readSector and printString work
	//readSector(buffer, 30);      //If these work, then readSector and printString work
	//printString(buffer);      //If these work, then readSector and printString work
    //makeInterrupt21();
    //interrupt(0x21,0,0,0,0);
    char line[80];      //If these work, interrupt 0x16, 0x21, and printString/printChar work
	makeInterrupt21();      //If these work, interrupt 0x16, 0x21, and printString/printChar work
    interrupt(0x21, 0, "Enter a line: ", 0,0);      //If these work, interrupt 0x16, 0x21, and printString/printChar work
    interrupt(0x21, 1, line, 0,0);      //If these work, interrupt 0x16, 0x21, and printString/printChar work
    interrupt(0x21, 0,line, 0,0);      //If these work, interrupt 0x16, 0x21, and printString/printChar work
	while(1){ //DONT LEAVE KERNEL
    //interrupt(0x21,1,line,0,0);
	//interrupt(0x21,0,line,0,0);
    //char line[80];
    //printString("Enter a line: ");
	//readString(line);
	//printString(line);
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
    }
}
