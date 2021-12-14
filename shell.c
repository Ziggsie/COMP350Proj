/*  Dabana Intenque, Kefron Grant, and Briana Santos*/
void main(){
    char buffer[13312];
    char input[80];
    char dir[512];
    char filename[20];
    char copyFrom[20];
    char copyTo[20];
    int entry;
    int letter;
    char map[512];
    int sectorsRead;
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
            syscall(3, input, buffer, &sectorsRead);
            syscall(2, dir, 2);
            syscall(2); //get from Dabana
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
        } else {
            syscall(0, "BAD COMMAND\r\n");
        }
    }
}
