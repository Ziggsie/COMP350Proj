/*  Dabana Intenque, Kefron Grant, and Briana Santos*/
void main(){
    char buffer[13312];
    char input[80];
    char dir[512];
    char filename[20];
    char copyFrom[20];
    char copyTo[20];
    char line[80];
    int entry;
    int letter;
    char map[512];
    int sectorsRead;
    int k;
    int j=1;
    int count=0;
    while(1){
        syscall(0, "shell>");    
        syscall(1, input);
        if (input[0] == 't' && input[1] == 'y' && input[2] == 'p' && input[3] == 'e'){
            syscall(3, input + 5, buffer);
            if (buffer[0] == '\0'){
                syscall(0, "could not locate file\r\n");
            } else  {
                syscall(0, buffer);
                syscall(0, "\n\r");
                buffer[0] = '\0';
            }
        } else if (input[0] == 'e' && input[1] == 'x' && input[2] == 'e' && input[3] == 'c'){
            syscall(4, input+5);
            syscall(5);
        } else if (input[0] == 'd' && input[1] == 'i' && input[2] == 'r') {
            //derived from readFile, not in wokring order though
            syscall(2, dir, 2);
            for (entry = 0; entry < 512; entry+=32){
                if (dir[entry] == '\0'){
                    return;
                } else {
                    for (letter = 0; letter < 6; letter++){
                        if (filename[letter] =! '\0'){ //(filename[letter] =! '\0')
                            filename[letter] = dir[entry+letter];
                        } else {
                            break;
                        }
                    }
                    syscall(0, filename);
                    syscall(0, "\r\n");
                }
            }
        } else if (input[0] == 'd' && input[1] == 'e' && input[2] == 'l'){
            syscall(3,input, buffer, &sectorsRead);
          syscall(2, dir, 2);
          syscall(2,map,1);
          if(sectorsRead){
            syscall(0,"File was deleded");
         }
         for(k=0; k<512; k=k+32){
           if(dir[k]!=0){
                    if(input[0]==dir[k] && input[1]==dir[k+1] && input[2]== dir[k+2] && input[3]== dir[k+3] && input[4] ==dir[k+4] && input[5]==dir[k+5]){
                    dir[k] ='\0';
                    syscall(0, &dir[k]);
                    syscall(6, dir,2);
                  for(count = 0; j!='\0'; count++){

                  j=dir[k+6+count];

                  map[j]='\0';

                }
                syscall(6, map,1);
           }


           }
         }
        } else if (input[0] == 'c' && input[1] == 'o' && input[2] == 'p' && input[3] == 'y'){
            int marker = 5;
            int i = 0;
            while (input[marker] != ' '){
                copyFrom[i] = input[marker];
                i++;
                marker++;
            }
            i = 0;
            marker++;
            while (input[marker] != '\0'){
                copyTo[i] = input[marker];
                i++;
                marker++;
            }
            syscall(3, copyFrom, buffer, sectorsRead);
            if (buffer[0] == '\0'){
                syscall(0, "could not locate file to copy\r\n");
            } else  {
                syscall(8, copyTo, sectorsRead);
            }
        } else if (input[0] == 'c' && input[1] == 'r' && input[2] == 'e' && input[3] == 'a' && input[4] == 't' && input[5] == 'e') {
            //syscall(1, input + 7, newFile);
            syscall(1, buffer);
            while (buffer[0] =! "\r\n"){
                //until we have an empty line it collects input lines. How do we get it to detect empty line?
                syscall(1, buffer);
                //while(line != 0xd){
                //    line[i] = c;
		        //    printChar(c); 
		        //    i++;
                //    }
            }
            syscall(8, buffer, input + 7, 1);
            
        } else {
            syscall(0, "BAD COMMAND\r\n");
        }
    }
}
