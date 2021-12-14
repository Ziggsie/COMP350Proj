/*  Dabana Intenque, Kefron Grant, and Briana Santos*/
void main(){
    char buffer[13312];
    char input[80];
    while(1){
        syscall(0, "shell>");    
        syscall(1, input);
        if (input[0] == 't' && input[1] == 'y' && input[2] == 'p' && input[3] == 'e'){
            syscall(3, input + 5, buffer);
            if (buffer[0] == '\0'){
                syscall(0, "could not locate file\r\n");
            } else  {
                syscall(0, buffer);
                buffer[0] = '\0';
            }
        } else if (input[0] == 'e' && input[1] == 'x' && input[2] == 'e' && input[3] == 'c'){
            syscall(4, input+5);
        } else {
            syscall(0, "BAD COMMAND\r\n");
        }
    }
}
